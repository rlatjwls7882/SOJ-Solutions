#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll M=3'037'000'493, P=1'343'457'632;
ll h1[1'000'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string t; cin >> t;
    int l, q; cin >> l >> q;

    ll b=1;
    unordered_set<ll> li;
    for(int i=0;i<l;i++) b=b*P%M;
    for(int i=1;i<=t.length();i++) h1[i]=(h1[i-1]*P+t[i-1])%M;
    for(int i=l;i<=t.length();i++) li.insert((h1[i]-h1[i-l]*b%M+M)%M);

    while(q--) {
        string p; cin >> p;
        ll h=0;
        for(char ch:p) h=(h*P+ch)%M;
        cout << (li.count(h) ? "Yes\n" : "No\n");
    }
}
