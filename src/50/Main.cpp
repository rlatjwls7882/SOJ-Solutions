#include<bits/stdc++.h>
using namespace std;

int table[1'000'001];

void makeTable(string s) {
    int idx=0;
    for(int i=1;i<s.length();i++) {
        while(idx && s[idx]!=s[i]) idx=table[idx-1];
        if(s[idx]==s[i]) table[i]=++idx;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string t, p; cin >> t >> p;
    makeTable(p);

    int idx=0;
    vector<int> res;
    for(int i=0;i<t.length();i++) {
        while(idx && p[idx]!=t[i]) idx=table[idx-1];
        if(p[idx]==t[i]) {
            if(++idx==p.length()) {
                res.push_back(i-idx+2);
                idx=table[idx-1];
            }
        }
    }
    cout << res.size() << '\n';
    for(auto e:res) cout << e << ' ';
}
