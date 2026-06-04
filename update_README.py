import os
import re
import sys
import time
from pathlib import Path
from urllib.parse import quote

import requests

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(iterable, **_):
        return iterable


README_PATH = Path("README.md")
SOLUTION_ROOT = Path("src")

SOJ_BASE_URL = os.getenv("SOJ_BASE_URL", "https://soj.services").rstrip("/")
SOJ_API_BASE = os.getenv("SOJ_API_BASE", f"{SOJ_BASE_URL}/api").rstrip("/")

OK_MARK = "✔️"
NO_MARK = "❌"

CONNECT_TIMEOUT = 10
READ_TIMEOUT = 30
REQUEST_RETRIES = 5
REQUEST_BACKOFF_SECONDS = 2
PAGE_SIZE = 500

# README.md가 이미 있다면 SOJ 서버의 일시적인 장애 때문에 workflow 전체를
# 실패시키지 않는다. 엄격하게 실패 처리하려면 환경 변수에 FAIL_ON_API_ERROR=true를 설정한다.
FAIL_ON_API_ERROR = os.getenv("FAIL_ON_API_ERROR", "false").lower() in {
    "1",
    "true",
    "yes",
}

CONTRIBUTORS = [
    "rlatjwls7882",
]

SESSION = requests.Session()
SESSION.headers.update({"User-Agent": "soj-solutions-readme-updater"})


class SojApiError(RuntimeError):
    pass


class SojApiUnavailableError(SojApiError):
    pass


def request_json(path, params=None):
    url = f"{SOJ_API_BASE}{path}"

    last_error = None
    for attempt in range(1, REQUEST_RETRIES + 1):
        try:
            response = SESSION.get(
                url,
                params=params,
                timeout=(CONNECT_TIMEOUT, READ_TIMEOUT),
            )
            response.raise_for_status()
            return response.json()
        except requests.HTTPError as error:
            status = error.response.status_code if error.response is not None else None

            # 잘못된 URL이나 권한 문제는 재시도해도 해결되지 않는다.
            if status is not None and 400 <= status < 500 and status != 429:
                raise SojApiError(f"SOJ API returned HTTP {status}: {url}") from error

            last_error = error
        except (requests.ConnectionError, requests.Timeout, ValueError) as error:
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


def fetch_problems():
    problems = []
    page = 0

    while True:
        data = request_json("/problems", {"page": page, "size": PAGE_SIZE})
        problems.extend(extract_items(data, "problems"))

        if not has_next_page(data, page):
            break

        page += 1

    return sorted(problems, key=lambda problem: int(problem.get("id", 0)))


def fetch_languages():
    data = request_json("/languages")
    languages = extract_items(data, "languages")

    if not languages:
        raise SojApiError("SOJ language API returned empty language list")

    return [normalize_language(language) for language in languages]


def extract_items(data, key):
    if isinstance(data, list):
        return data

    if isinstance(data, dict):
        items = data.get(key, [])
        return items if isinstance(items, list) else []

    return []


def has_next_page(data, page):
    if not isinstance(data, dict):
        return False

    if "last" in data:
        return not data["last"]

    if "totalPages" in data:
        return page + 1 < int(data["totalPages"])

    return False


def normalize_language(language):
    name = str(language.get("name", "")).strip()
    source_file = str(language.get("sourceFile", "")).strip()
    extension = str(language.get("extension", "")).strip()

    if not extension and source_file:
        extension = Path(source_file).suffix

    if extension and not extension.startswith("."):
        extension = f".{extension}"

    return {
        "name": name,
        "displayName": display_language_name(name),
        "sourceFile": source_file,
        "extension": extension,
    }


def display_language_name(name):
    # C++20 -> C++, Java 21 -> Java, Python 3 -> Python
    return re.sub(r"\s*\d+(?:\.\d+)*$", "", str(name).strip()).strip()


def visible_languages(languages):
    return [
        language
        for language in languages
        if language["name"]
        and language["displayName"]
        and language["sourceFile"]
        and language["extension"]
    ]


def solution_candidates(problem_id, language):
    extension = language["extension"]
    source_name = Path(language["sourceFile"]).name

    names = [
        source_name,
        f"Main{extension}",
        f"main{extension}",
    ]

    seen = set()
    for name in names:
        if not name or name in seen:
            continue

        seen.add(name)
        yield SOLUTION_ROOT / str(problem_id) / name


def find_solution_path(problem_id, language):
    for path in solution_candidates(problem_id, language):
        if path.is_file():
            return path

    return None


def solution_cell(problem_id, language):
    path = find_solution_path(problem_id, language)

    if path is None:
        return NO_MARK

    return f"[{OK_MARK}](./{md_link(path)})"


def problem_url(problem_id):
    return f"{SOJ_BASE_URL}/problems/{problem_id}"


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


def make_contributors_section():
    if not CONTRIBUTORS:
        return ""

    cells = []
    for username in CONTRIBUTORS:
        cells.append(f"""    <td align="center">
      <a href="https://github.com/{username}">
        <img src="https://github.com/{username}.png" width="100px;" alt="{username}"/>
        <br />
        <sub><b>{username}</b></sub>
      </a>
    </td>""")

    rows = []
    for i in range(0, len(cells), 6):
        rows.append("  <tr>\n" + "\n".join(cells[i:i + 6]) + "\n  </tr>")

    return """## 기여자

<table>
""" + "\n".join(rows) + """
</table>
"""


def get_header():
    return "\n".join([
        "# SOJ Solutions",
        "",
        "[Seojin Online Judge](https://soj.services)의 공식 풀이 저장소입니다.",
        "",
    ])


def get_table(problems, languages):
    headers = ["번호", "문제", "난이도"] + [
        md_escape(language["displayName"])
        for language in languages
    ]
    aligns = [":---:", ":---", ":---:"] + [":---:"] * len(languages)

    lines = [
        "## 풀이 목록",
        "",
        make_row(headers),
        make_row(aligns),
    ]

    for problem in tqdm(problems, desc="Generating README"):
        problem_id = problem.get("id")

        row = [
            f"[{problem_id}]({problem_url(problem_id)})",
            md_escape(problem.get("title")),
            md_escape(problem.get("difficulty")) or "-",
        ]

        row.extend(solution_cell(problem_id, language) for language in languages)
        lines.append(make_row(row))

    return "\n".join(lines) + "\n"


def write_readme(problems, languages):
    README_PATH.write_text(
        get_header()
        + get_table(problems, languages)
        + "\n\n" + make_contributors_section(),
        encoding="utf-8",
    )


def main():
    try:
        problems = fetch_problems()
        languages = visible_languages(fetch_languages())
    except SojApiUnavailableError as error:
        if README_PATH.is_file() and not FAIL_ON_API_ERROR:
            print(f"[SOJ API] {error}", file=sys.stderr)
            print("[SOJ API] keeping the existing README.md unchanged.", file=sys.stderr)
            return

        raise

    write_readme(problems, languages)


if __name__ == "__main__":
    main()
