#include<bits/stdc++.h>
using namespace std;

int a[200'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];

    int x=0,l=0,r=n-1,i=0;
    while(l<=r){
        if(a[l]<a[r])x=max(x,a[l++]-i);
        else x=max(x,a[r--]-i);
        i++;
    }
    cout<<x;
}
