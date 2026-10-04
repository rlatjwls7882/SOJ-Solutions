import json
import os
import re
import sys
import time
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode
from urllib.request import Request, urlopen


README_PATH = Path("README.md")
SOLUTION_ROOT = Path("src")

SOJ_BASE_URL = os.getenv("SOJ_BASE_URL", "https://soj.services").rstrip("/")
SOJ_API_BASE = os.getenv("SOJ_API_BASE", f"{SOJ_BASE_URL}/api").rstrip("/")

REQUEST_TIMEOUT = 30
REQUEST_RETRIES = 5
REQUEST_BACKOFF_SECONDS = 2
PAGE_SIZE = 500

FAIL_ON_API_ERROR = os.getenv("FAIL_ON_API_ERROR", "false").lower() in {
    "1",
    "true",
    "yes",
}

SOLUTION_RE = re.compile(r"^(?P<problem_id>\d+)(?P<extension>\.[^.]+)$")

LANGUAGE_NAMES = {
    ".c": "C",
    ".cpp": "C++",
    ".java": "Java",
    ".py": "Python",
    ".rs": "Rust",
    ".kt": "Kotlin",
    ".go": "Go",
    ".cs": "C#",
    ".js": "JavaScript",
    ".ts": "TypeScript",
}

LANGUAGE_ORDER = {
    ".c": 0,
    ".cpp": 1,
    ".java": 2,
    ".py": 3,
    ".rs": 4,
}


class SojApiError(RuntimeError):
    pass


class SojApiUnavailableError(SojApiError):
    pass


def request_json(path, params=None):
    url = f"{SOJ_API_BASE}{path}"
    if params:
        url += "?" + urlencode(params)

    request = Request(
        url,
        headers={
            "Accept": "application/json",
            "User-Agent": "soj-solutions-readme-updater",
        },
    )

    last_error = None

    for attempt in range(1, REQUEST_RETRIES + 1):
        try:
            with urlopen(request, timeout=REQUEST_TIMEOUT) as response:
                return json.load(response)
        except HTTPError as error:
            if 400 <= error.code < 500 and error.code != 429:
                raise SojApiError(
                    f"SOJ API returned HTTP {error.code}: {url}"
                ) from error
            last_error = error
        except (URLError, TimeoutError, json.JSONDecodeError, OSError) as error:
            last_error = error

        print(
            f"[SOJ API] request failed ({attempt}/{REQUEST_RETRIES}): "
            f"{type(last_error).__name__}: {last_error}",
            file=sys.stderr,
        )

        if attempt < REQUEST_RETRIES:
            delay = REQUEST_BACKOFF_SECONDS * attempt
            print(f"[SOJ API] retrying in {delay}s...", file=sys.stderr)
            time.sleep(delay)

    raise SojApiUnavailableError(f"SOJ API is unavailable: {url}") from last_error


def extract_items(data, key):
    if isinstance(data, list):
        return data

    if not isinstance(data, dict):
        return []

    for candidate in (key, "content", "items"):
        items = data.get(candidate)
        if isinstance(items, list):
            return items

    return []


def has_next_page(data, page):
    if not isinstance(data, dict):
        return False

    if isinstance(data.get("last"), bool):
        return not data["last"]

    total_pages = data.get("totalPages", data.get("total_pages"))
    if total_pages is not None:
        return page + 1 < int(total_pages)

    return False


def problem_id(problem):
    try:
        return int(problem.get("id"))
    except (TypeError, ValueError):
        return 10**18


def fetch_problems():
    problems = []
    page = 0

    while True:
        data = request_json("/problems", {"page": page, "size": PAGE_SIZE})
        problems.extend(extract_items(data, "problems"))

        if not has_next_page(data, page):
            break

        page += 1

    problems = [problem for problem in problems if problem_id(problem) != 10**18]

    if not problems:
        raise SojApiError("SOJ problem API returned an empty problem list")

    return sorted(problems, key=problem_id)


def scan_solutions():
    if not SOLUTION_ROOT.is_dir():
        raise RuntimeError(f"solution directory does not exist: {SOLUTION_ROOT}")

    solutions = {}
    invalid_entries = []

    for path in SOLUTION_ROOT.iterdir():
        if path.name.startswith("."):
            continue

        if not path.is_file():
            invalid_entries.append(path.as_posix())
            continue

        match = SOLUTION_RE.fullmatch(path.name)
        if match is None:
            invalid_entries.append(path.as_posix())
            continue

        pid = int(match.group("problem_id"))
        extension = match.group("extension").lower()
        solutions.setdefault(pid, {})[extension] = path

    if invalid_entries:
        entries = "\n".join(f"  - {entry}" for entry in sorted(invalid_entries))
        raise RuntimeError(
            "src must contain only flat '<problem_id>.<extension>' files:\n"
            + entries
        )

    return solutions


def language_name(extension):
    return LANGUAGE_NAMES.get(extension, extension.removeprefix(".").upper())


def language_sort_key(extension):
    return (
        LANGUAGE_ORDER.get(extension, 100),
        language_name(extension).lower(),
        extension,
    )


def used_languages(solutions):
    extensions = {
        extension
        for problem_solutions in solutions.values()
        for extension in problem_solutions
    }
    return sorted(extensions, key=language_sort_key)


def problem_url(pid):
    return f"{SOJ_BASE_URL}/problems/{pid}"


def md_link(path):
    return quote(path.as_posix(), safe="/._-()")


def md_escape(value):
    return (
        str(value if value is not None else "")
        .replace("|", "\\|")
        .replace("\n", " ")
        .strip()
    )


def make_row(values):
    return "| " + " | ".join(values) + " |"


def solution_cell(pid, extension, solutions):
    path = solutions.get(pid, {}).get(extension)
    if path is None:
        return "❌"

    return f"[✔️](./{md_link(path)})"


def get_header():
    return "# SOJ Solutions\n\n"


def get_table(problems, languages, solutions):
    headers = ["번호", "문제", "난이도"] + [
        language_name(extension) for extension in languages
    ]
    aligns = [":---:", ":---", ":---:"] + [":---:"] * len(languages)

    lines = [
        "## 풀이 목록",
        "",
        make_row(headers),
        make_row(aligns),
    ]

    problem_ids = set()

    for problem in problems:
        pid = problem_id(problem)
        problem_ids.add(pid)

        row = [
            f"[{pid}]({problem_url(pid)})",
            md_escape(problem.get("title")),
            md_escape(problem.get("difficulty")) or "-",
        ]
        row.extend(
            solution_cell(pid, extension, solutions)
            for extension in languages
        )
        lines.append(make_row(row))

    unknown_ids = sorted(set(solutions) - problem_ids)
    if unknown_ids:
        print(
            "[README] source files exist for problem IDs not returned by SOJ API: "
            + ", ".join(map(str, unknown_ids)),
            file=sys.stderr,
        )

    return "\n".join(lines) + "\n"


def build_readme(problems, solutions):
    languages = used_languages(solutions)
    return get_header() + get_table(problems, languages, solutions)


def write_readme(content):
    current = None
    if README_PATH.is_file():
        current = README_PATH.read_text(encoding="utf-8-sig")

    if current == content:
        print("[README] README.md is already up to date.")
        return False

    README_PATH.write_text(content, encoding="utf-8", newline="\n")
    print("[README] README.md updated.")
    return True


def main():
    solutions = scan_solutions()

    try:
        problems = fetch_problems()
    except SojApiUnavailableError as error:
        if README_PATH.is_file() and not FAIL_ON_API_ERROR:
            print(f"[SOJ API] {error}", file=sys.stderr)
            print("[SOJ API] keeping the existing README.md unchanged.", file=sys.stderr)
            return

        raise

    write_readme(build_readme(problems, solutions))


if __name__ == "__main__":
    main()
