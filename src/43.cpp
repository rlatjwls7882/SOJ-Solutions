#include<bits/stdc++.h>
using namespace std;

int a[1001], b[1001], vis[1001];
vector<vector<int>> conn(1001);

bool dfs(int cur) {
    vis[cur]=true;
    for(int next:conn[cur]) {
        if(!b[next] || !vis[b[next]] && dfs(b[next])) {
            a[cur]=next;
            b[next]=cur;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    while(k--) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
    }

    int cnt=0;
    for(int i=1;i<=n;i++) {
        memset(vis, 0, sizeof vis);
        cnt+=dfs(i);
    }
    cout << cnt;
}
