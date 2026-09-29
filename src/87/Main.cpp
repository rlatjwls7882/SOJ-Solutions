#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> conn(200'001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n-1;i++) {
        int u, v; cin >> u >> v;
        conn[u].push_back(v);
        conn[v].push_back(u);
    }

    int leaf=0;
    for(int i=1;i<=n;i++) leaf+=(conn[i].size()==1);

    for(int i=1;i<=n;i++) {
        int res=leaf - (conn[i].size()==1);
        for(int next:conn[i]) {
            res -= (conn[next].size()==1);
            res += (conn[next].size()==2);
        }
        cout << res << '\n';
    }
}
