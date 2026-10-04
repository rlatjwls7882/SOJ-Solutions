#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
};

ll ccw(point a, point b, point c) {
    point v1 = {b.x-a.x, b.y-a.y};
    point v2 = {c.x-a.x, c.y-a.y};
    ll ret=v1.x*v2.y-v2.x*v1.y;
    return ret>0 ? 1 : ret<0 ? -1 : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    while(q--) {
        point a, b, c; cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        cout << ccw(a, b, c) << '\n';
    }
}
