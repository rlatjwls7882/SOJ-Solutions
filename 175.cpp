#include<bits/stdc++.h>
using namespace std;

int a[200'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;

    int mx=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        mx=max(mx,a[i]);
    }

    int mn=INT_MAX;
    for(int i=0;i<n;i++)mn=min(mn,a[i]+a[(i+1)%n]);
    cout<<max(mx,mn);
}
