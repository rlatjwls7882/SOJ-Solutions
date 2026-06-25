#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
};

ll ccw(point a, point b, point c) {
    point v1 = {b.x-a.x, b.y-a.y};
    point v2 = {c.x-a.x, c.y-a.y};
    return v1.x*v2.y-v2.x*v1.y;
}

bool isInside(vector<point> &hull, point p) {
    if(ccw(hull[0], hull[1], p)<=0) return false;
    if(ccw(hull[0], hull[hull.size()-1], p)>=0) return false;
    int l=1, r=hull.size()-1;
    while(l+1<r) {
        int m = l+r>>1;
        if(ccw(hull[0], hull[m], p)>0) l=m;
        else r=m;
    }
    return ccw(hull[l], hull[r], p)>0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<point> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    while(q--) {
        int x, y; cin >> x >> y;
        cout << (isInside(v, {x, y}) ? "Yes\n" : "No\n");
    }
}
