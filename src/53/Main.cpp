#include<bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* go[26] = {};
    int cnt=0;

    void insert(const string &s) {
        Trie *cur=this;
        for(char ch:s) {
            if(!cur->go[ch-'a']) cur->go[ch-'a'] = new Trie;
            cur = cur->go[ch-'a'];
            cur->cnt++;
        }
    }
    int res(const string &s) {
        Trie *cur=this;
        for(char ch:s) {
            if(!cur->go[ch-'a']) return 0;
            cur = cur->go[ch-'a'];
        }
        return cur->cnt;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Trie *root = new Trie;
    int q; cin >> q;
    while(q--) {
        int op; string s; cin >> op >> s;
        if(op==1) root->insert(s);
        else cout << root->res(s) << '\n';
    }
}
