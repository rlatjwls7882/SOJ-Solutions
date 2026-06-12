#include<bits/stdc++.h>
using namespace std;

const int MAX = 10001;

stack<int> stk;
int idx, vis[MAX], par[MAX];
vector<vector<int>> conn(MAX), SCCs;

int dfs(int cur) {
    int rem = par[cur] = ++idx;
    stk.push(cur);
    for(int next:conn[cur]) {
        if(!par[next]) rem=min(rem, dfs(next));
        else if(!vis[next]) rem=min(rem, par[next]);
    }
    if(rem==par[cur]) {
        SCCs.push_back(vector<int>());
        while(true) {
            int top = stk.top(); stk.pop();
            SCCs.back().push_back(top);
            vis[top]=true;
            par[top]=rem;
            if(top==cur) break;
        }
    }
    return rem;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);

    cout << SCCs.size() << '\n';
    for(auto &scc:SCCs) {
        sort(scc.begin(), scc.end());
        for(auto e:scc) cout << e << ' ';
        cout << "-1\n";
    }
}
