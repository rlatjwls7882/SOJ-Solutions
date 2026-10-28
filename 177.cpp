#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[100'000],psum[100'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n,greater<int>());
    for(int i=0;i<n;i+=2)a[i]*=-1;
    sort(a,a+n);
    for(int i=0;i<n;i++){
        psum[i]=a[i];
        if(i)psum[i]+=psum[i-1];
    }

    ll sum=0;
    for(int i=1;i<n;i++)sum+=a[i]*i-psum[i-1];
    cout<<sum;
}
