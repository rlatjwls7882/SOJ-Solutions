#include<bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* go[26] = {};
    int cnt=0;

    void insert(const char* ch) {
        cnt++;
        if(!*ch) return;
        if(!go[*ch-'a']) go[*ch-'a'] = new Trie;
        go[*ch-'a']->insert(ch+1);
    }

    int res(const char* ch) {
        if(!*ch) return cnt;
        if(go[*ch-'a']) return go[*ch-'a']->res(ch+1);
        return 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Trie *root = new Trie;
    int q; cin >> q;
    while(q--) {
        int op; string s; cin >> op >> s;
        if(op==1) root->insert(&s[0]);
        else cout << root->res(&s[0]) << '\n';
    }
}
