#include<bits/stdc++.h>
using namespace std;

typedef long double ld;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ld a, b, c; cin >> a >> b >> c;
    if(a<b) swap(a, b);
    if(a<c) swap(a, c);
    if(b<c) swap(b, c);

    cout << setprecision(7) << fixed;
    if(a*a>=b*b+c*c) {
        cout << b*c/2;
    } else {
        ld s = (a+b+c)/2;
        cout << sqrt(s*(s-a)*(s-b)*(s-c));
    }
}