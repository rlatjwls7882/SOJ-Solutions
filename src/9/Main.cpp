#include<bits/stdc++.h>
using namespace std;

int cnt[128];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; string s; cin >> n >> s;
    for(auto e:s) cnt[e]++;
    if(cnt['A'] && cnt['G'] && cnt['F'] && cnt['E'] && cnt['D']) {
        for(int i=0;i+7<n;i++) {
            if(s[i]!='.' && s[i+1]!='.' && s[i+2]=='.' && s[i+3]!='.' && s[i+4]!='.' && s[i+5]=='.' && s[i+6]!='.' && s[i+7]=='.') {
                cout << "Yes";
                return 0;
            }
        }
    }
    cout << "No";
}