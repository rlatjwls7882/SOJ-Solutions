#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

ll f[101][101], c[101][101], w[101][101], cost[101], prv[101];
bool inQ[101];
vector<vector<int>> conn(101);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s, t; cin >> n >> m >> s >> t;
    while(m--) {
        ll u, v; cin >> u >> v >> c[u][v] >> w[u][v];
        w[v][u]=-w[u][v];
        conn[u].push_back(v);
        conn[v].push_back(u);
    }

    ll totalF=0, totalW=0;
    while(true) {
        queue<int> q; q.push(s);
        memset(prv, -1, sizeof prv);
        fill(cost, cost+n+1, LINF);
        cost[s]=0;
        while(!q.empty()) {
            int cur=q.front(); q.pop();
            inQ[cur]=false;
            for(int next:conn[cur]) {
                if(c[cur][next]-f[cur][next] && cost[next]>cost[cur]+w[cur][next]) {
                    prv[next]=cur;
                    cost[next]=cost[cur]+w[cur][next];
                    if(!inQ[next]) {
                        inQ[next]=true;
                        q.push(next);
                    }
                }
            }
        }
        if(prv[t]==-1) break;

        ll flow=LINF;
        for(int i=t;i!=s;i=prv[i]) flow=min(flow, c[prv[i]][i]-f[prv[i]][i]);
        for(int i=t;i!=s;i=prv[i]) {
            f[prv[i]][i]+=flow;
            f[i][prv[i]]-=flow;
        }
        totalF+=flow;
        totalW+=flow*cost[t];
    }
    cout << totalF << '\n' << totalW;
}
