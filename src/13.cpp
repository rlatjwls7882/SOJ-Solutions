#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Hashing {
    const ll P = 917, M = 998244353;
    vector<ll> h, p;
    Hashing(const string &s) : h(s.size()+1), p(s.size()+1) {
        int n=s.size();
        p[0]=1;
        for(int i=1;i<=n;i++) h[i]=(h[i-1]*P+s[i-1])%M;
        for(int i=1;i<=n;i++) p[i]=p[i-1]*P%M;
    }
    ll get(int s, int e) {
        return ((h[e]-h[s-1]*p[e-s+1])%M+M)%M;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        Hashing h(s);

        vector<pair<ll, ll>> v;
        for(int i=1;i<s.length();i++) {
            ll a = h.get(1, i);
            ll b = h.get(i+1, s.length());
            if(a>b) swap(a, b);
            v.push_back({a, b});
        }
        int res=v.size();
        for(int i=0;i<v.size()/2;i++) res-=v[i]==v[v.size()-1-i];
        cout << res << '\n';
    }
}