#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    vector<string>a,b;

    cin.ignore();
    string s;getline(cin,s);
    stringstream ss(s);
    while(ss>>s)a.push_back(s);

    getline(cin,s);
    ss=stringstream(s);
    while(ss>>s)b.push_back(s);

    cout<<min(a[n],b[m])<<max(a[n],b[m]);
}
