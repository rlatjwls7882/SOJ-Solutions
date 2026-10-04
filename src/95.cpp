#include<bits/stdc++.h>
using namespace std;

string want = "EASY";

bool chk(string s) {
    bool easy=false, hard=false;
    for(int i=0;i<(int)s.length()-3;i++) {
        string cur = s.substr(i, 4);
        if(cur=="EASY") easy=true;
        else if(cur=="HARD") hard=true;
    }
    return easy && !hard;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    for(int i=0;i<(int)s.length()-3;i++) {
        string cur = s.substr(i, 4);
        if(cur=="HARD") break;
        else if(cur=="EASY") {
            cout << "Yes";
            return 0;
        }
    }
    for(int i=0;i<4;i++) {
        string left = want.substr(0, i);
        string right = want.substr(i, 4-i);

        int firstIdx=s.length()-1, lastIdx=0;
        for(int i=0;i<s.length();i++) {
            if(s.substr(i, left.size())==left) firstIdx=min(firstIdx, i);
            if(s.substr(i, right.size())==right) lastIdx=max(lastIdx, i);
        }
        if(firstIdx>=lastIdx) continue;

        string cur = s.substr(0, firstIdx+left.size()) + s.substr(lastIdx, s.length()-lastIdx);
        if(chk(cur)) {
            cout << "Yes";
            return 0;
        }
        // cout << left << ' ' << right << ' ';
        // cout << s.substr(0, firstIdx+left.size()) << ' ' << s.substr(lastIdx, s.length()-lastIdx) << ' ';
        // cout << cur << '\n';
    }
    cout << "No";
}

/**
solution:
case1 : ????? EASY
case2 : E ????? ASY
case3 : EA ???? SY
case4 : EAS ???? Y
case5 : EASY ??????
case6 : HARD EASY HARD

*/
