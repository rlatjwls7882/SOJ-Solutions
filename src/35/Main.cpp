#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long a, b, m; cin >> a >> b >> m;

    long long res=1;
    while(b--) res = res*a%m;
    cout << res;
}
