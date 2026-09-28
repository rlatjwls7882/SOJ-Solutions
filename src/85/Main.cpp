#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a,b;getline(cin,a); cin>>b;

    int cnt=0, idx=0;
    while(idx<a.length()) {
        idx=a.find(b,idx);
        if(idx==string::npos)break;
        cnt++;
        idx+=b.length();
    }
    cout<<cnt;
}
