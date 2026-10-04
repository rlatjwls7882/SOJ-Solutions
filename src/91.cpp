#include<bits/stdc++.h>
using namespace std;

int a[200'000], mx[2];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];

    vector<pair<int,int>> v;
    for(int i=0;i<n;i++) v.push_back({a[i],i});
    sort(v.begin(),v.end());

    int res=0;
    for(auto [x,i]:v) {
        if(a[(i+1)%n]>x) mx[0]=max(mx[0],a[(i+1)%n]);
        if(a[(i+n-1)%n]>x) mx[1]=max(mx[1],a[(i+n-1)%n]);
        res=max(res,min(mx[0],mx[1])-x);
    }
    cout << res;
}
