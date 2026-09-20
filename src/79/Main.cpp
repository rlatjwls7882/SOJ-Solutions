#include<bits/stdc++.h>
using namespace std;

int a[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    cout<<a[n-1]+a[n-2];
}
