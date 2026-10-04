#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LINF=0x3f3f3f3f3f3f3f3f;

struct element {
    ll u, w;
    bool operator<(const element& e) const {
        return w > e.w;
    }
};

ll dist[100'001];
vector<vector<element>> conn(100'001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s; cin >> n >> m >> s;
    while(m--) {
        int u, v, w; cin >> u >> v >> w;
        conn[u].push_back({v, w});
        conn[v].push_back({u, w});
    }

    fill(dist, dist+n+1, LINF);
    priority_queue<element> pq; pq.push({s, 0});
    while(!pq.empty()) {
        auto [cur, cost] = pq.top(); pq.pop();
        if(dist[cur]<=cost) continue;
        dist[cur]=cost;
        for(auto [nxt, w]:conn[cur]) {
            if(dist[nxt]>cost+w) {
                pq.push({nxt, cost+w});
            }
        }
    }
    for(int i=1;i<=n;i++) cout << (dist[i]==LINF ? -1 : dist[i]) << "\n";
}
