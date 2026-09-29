#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    int cnt=0;
    for(int i=0;i<n;i++) {
        string s; cin >> s;
        if(s=="sejong") cnt++;
    }
    cout << (cnt>=n-2 ? "Yes" : "No");
}
