#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>> v(n);
    for(auto &[l, r]:v) cin >> l >> r;
    sort(v.begin(), v.end());

    int l=v[0].first, r=v[0].second, sum=0;
    for(int i=1;i<n;i++) {
        auto [a, b]=v[i];
        if(r<a) {
            sum+=r-l;
            l=a;
            r=b;
        } else {
            r=max(r, b);
        }
    }
    sum+=r-l;
    cout << sum;
}
