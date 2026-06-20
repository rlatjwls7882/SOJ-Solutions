#include<bits/stdc++.h>
using namespace std;

struct Trie {
    Trie *go[26]={};
    bool finish=false;
    Trie *fail;
    void insert(const string& s) {
        Trie *cur=this;
        for(char ch:s) {
            if(!cur->go[ch-'a']) cur->go[ch-'a']=new Trie;
            cur = cur->go[ch-'a'];
        }
        cur->finish=true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Trie *root=new Trie;
    int n; cin >> n;
    while(n--) {
        string p; cin >> p;
        root->insert(p);
    }

    queue<Trie*> q; q.push(root);
    while(!q.empty()) {
        Trie *cur = q.front(); q.pop();
        for(int i=0;i<26;i++) {
            if(!cur->go[i]) continue;
            Trie *next = cur->go[i];
            if(cur==root) {
                next->fail=root;
            } else {
                Trie *dest=cur->fail;
                while(dest!=root && !dest->go[i]) dest=dest->fail;
                if(dest->go[i]) dest=dest->go[i];
                next->fail=dest;
            }
            if(next->fail->finish) next->finish=true;
            q.push(next);
        }
    }

    int Q; cin >> Q;
    while(Q--) {
        string t; cin >> t;
        Trie *cur=root;
        for(char ch:t) {
            while(cur!=root && !cur->go[ch-'a']) cur=cur->fail;
            if(cur->go[ch-'a']) cur=cur->go[ch-'a'];
            if(cur->finish) break;
        }
        cout << (cur->finish ? "Yes\n" : "No\n");
    }
}
