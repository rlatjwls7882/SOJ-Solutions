#include<bits/stdc++.h>
using namespace std;

bool vis[100'001];
vector<vector<int>> conn(100'001);

void dfs(int cur) {
    vis[cur]=true;
    cout << cur << ' ';
    for(int next:conn[cur]) {
        if(!vis[next]) {
            dfs(next);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, s; cin >> n >> m >> s;
    while(m--) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    for(int i=1;i<=n;i++) sort(conn[i].begin(), conn[i].end());
    dfs(s);
}
