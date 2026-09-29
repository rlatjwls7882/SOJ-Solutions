#include<bits/stdc++.h>
using namespace std;

int a[200'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i=0;i<n;i++) cin >> a[i];
    sort(a, a+n);

    long long l=a[k-1], r=a[n-1];
    for(int i=k+1;i<n;i++) l+=a[i];
    for(int i=1;i<n-k;i++) r+=a[i];
    cout << min(l, r);
}
