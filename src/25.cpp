#include<bits/stdc++.h>
using namespace std;

int a[100'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x; cin >> n >> x;
    for(int i=0;i<n;i++) cin >> a[i];

    int cnt=0, l=0, r=n-1;
    while(l<r) {
        if(a[l]+a[r]==x) l++, r--, cnt++;
        else if(a[l]+a[r]<x) l++;
        else r--;
    }
    cout << cnt;
}
