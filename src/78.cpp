#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b; cin >> a >> b;
    int c, d; cin >> c >> d;

    cout << a.substr(0, c);
    for(auto e:b) {
        if(d && 'a'<=e&&e<='z') cout << char(e-32);
        else if(d && 'A'<=e&&e<='Z') cout << char(e+32);
        else cout << e;
    }
    cout << a.substr(c,a.length()-c);
}
