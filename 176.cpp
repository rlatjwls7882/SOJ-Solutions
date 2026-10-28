#include<bits/stdc++.h>
using namespace std;

int a[200'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);

    int res=INT_MAX;
    for(int i=0;i<n;i++)res=min(res,a[i]+n-1-i);
    cout<<res;
}
