#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<string> v;
    while(true) {
        string s; cin >> s;
        if(cin.fail())break;
        v.push_back(s);
    }
    for(auto e:v)cout<<e<<'\n';
    sort(v.begin(),v.end());
    for(auto e:v)cout<<e<<' ';
}
