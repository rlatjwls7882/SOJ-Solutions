#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b; cin >> a >> b;
    cout << max(a.length(), b.length()) << '\n' << (a.length()==b.length());
}
