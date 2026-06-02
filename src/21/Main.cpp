#include<bits/stdc++.h>
using namespace std;

int par[1'000'001], sz[1'000'001];

int find(int x) {
    if(par[x]==x) return x;
    return par[x]=find(par[x]);
}

void merge(int a, int b) {
    a=find(a);
    b=find(b);
    if(a==b) return;
    if(a<b) {
        par[b]=a;
        sz[a]+=sz[b];
    } else {
        par[a]=b;
        sz[b]+=sz[a];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++) {
        par[i]=i;
        sz[i]=1;
    }

    while(q--) {
        string s; int a, b; cin >> s;
        if(s=="merge") {
            cin >> a >> b;
            merge(a, b);
        } else if(s=="same") {
            cin >> a >> b;
            cout << (find(a)==find(b)) << '\n';
        } else {
            cin >> a;
            cout << sz[find(a)] << '\n';
        }
    }
}
