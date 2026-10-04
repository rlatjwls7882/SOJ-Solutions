#include<bits/stdc++.h>
using namespace std;

int inD[100'001];
vector<vector<int>> conn(100'001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v);
        inD[v]++;
    }

    queue<int> q;
    for(int i=1;i<=n;i++) {
        if(!inD[i]) q.push(i);
    }
    vector<int> res;
    while(!q.empty()) {
        int cur=q.front(); q.pop();
        res.push_back(cur);
        for(int next:conn[cur]) {
            if(--inD[next]==0) q.push(next);
        }
    }
    if(res.size()!=n) cout << "CYCLE";
    else for(auto e:res) cout << e << ' ';
}
