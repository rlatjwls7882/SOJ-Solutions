#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y, p=0, q=0;
    bool operator<(const point b) const {
        if(p*b.q!=b.p*q) return p*b.q>b.p*q;
        if(y!=b.y) return y<b.y;
        return x<b.x;
    }
};

ll ccw(point a, point b, point c) {
    point v1 = {b.x-a.x, b.y-a.y};
    point v2 = {c.x-a.x, c.y-a.y};
    return v1.x*v2.y-v2.x*v1.y;
}

vector<point> graham_scan(vector<point> v) {
    sort(v.begin(), v.end());
    for(int i=1;i<v.size();i++) {
        v[i].p=v[i].x-v[0].x;
        v[i].q=v[i].y-v[0].y;
    }
    sort(v.begin(), v.end());

    vector<point> stk;
    for(auto e:v) {
        while(stk.size()>=2 && ccw(stk[stk.size()-2], stk.back(), e)<=0) stk.pop_back();
        stk.push_back(e);
    }
    return stk;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<point> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    cout << graham_scan(v).size();
}
