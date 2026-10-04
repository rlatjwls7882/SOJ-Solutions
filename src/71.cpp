#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sq, a[200'001], cnt[200'000];

struct query {
    int l, r, idx;
    bool operator<(const query q) const {
        if(l/sq!=q.l/sq) return l/sq<q.l/sq;
        return r/sq<q.r/sq;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    sq=sqrt(n);

    vector<int> comp;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        comp.push_back(a[i]);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(comp.begin(), comp.end(), a[i])-comp.begin();

    vector<query> queries(q);
    for(int i=0;i<q;i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx=i;
    }
    sort(queries.begin(), queries.end());

    ll cur=0, cl=1, cr=0;
    vector<ll> res(q);
    for(auto [l, r, i]:queries) {
        while(cl>l) cur+=cnt[a[--cl]]++;
        while(cr<r) cur+=cnt[a[++cr]]++;
        while(cl<l) cur-=--cnt[a[cl++]];
        while(cr>r) cur-=--cnt[a[cr--]];
        res[i]=cur;
    }
    for(auto e:res) cout << e << '\n';
}
