#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 2001;

int s, t;
ll f[MAX][MAX], c[MAX][MAX];
int level[MAX], work[MAX];
vector<vector<int>> conn(MAX);

bool bfs() {
    queue<int> q; q.push(s);
    memset(level, -1, sizeof level);
    level[s]=0;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(c[cur][next]-f[cur][next] && level[next]==-1) {
                level[next]=level[cur]+1;
                q.push(next);
            }
        }
    }
    return level[t]!=-1;
}

ll dfs(int cur, ll curFlow) {
    if(cur==t) return curFlow;
    for(int &i=work[cur];i<conn[cur].size();i++) {
        int next=conn[cur][i];
        if(level[next]==level[cur]+1 && c[cur][next]-f[cur][next]) {
            ll flow = dfs(next, min(curFlow, c[cur][next]-f[cur][next]));
            if(flow) {
                f[cur][next]+=flow;
                f[next][cur]-=flow;
                return flow;
            }
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m >> s >> t;
    while(m--) {
        ll u, v, w; cin >> u >> v >> w;
        conn[u].push_back(v);
        conn[v].push_back(u);
        c[u][v]+=w;
    }

    ll res=0;
    while(bfs()) {
        memset(work, 0, sizeof work);
        while(ll ret=dfs(s, LINF)) {
            res+=ret;
        }
    }
    cout << res;
}
