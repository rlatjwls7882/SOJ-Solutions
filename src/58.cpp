#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
    bool operator<(const point p) const {
        if(x!=p.x) return x<p.x;
        return y<p.y;
    }
};

struct line {
    point p1, p2;
};

ll ccw(point a, point b, point c) {
    point v1 = {b.x-a.x, b.y-a.y};
    point v2 = {c.x-a.x, c.y-a.y};
    ll ret=v1.x*v2.y-v2.x*v1.y;
    return ret>0 ? 1 : ret<0 ? -1 : 0;
}

bool isIntersect(line l1, line l2) {
    point a=l1.p1, b=l1.p2, c=l2.p1, d=l2.p2;
    ll ac = ccw(a, b, c);
    ll ad = ccw(a, b, d);
    ll ca = ccw(c, d, a);
    ll cb = ccw(c, d, b);
    if(ac*ad==0 && ca*cb==0) {
        if(b<a) swap(a, b);
        if(d<c) swap(c, d);
        return !(b<c || d<a);
    }
    return ac*ad<=0 && ca*cb<=0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    while(q--) {
        line a, b; cin >> a.p1.x >> a.p1.y >> a.p2.x >> a.p2.y >> b.p1.x >> b.p1.y >> b.p2.x >> b.p2.y;
        cout << (isIntersect(a, b) ? "Yes\n" : "No\n");
    }
}
