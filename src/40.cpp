#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LINF=0x3f3f3f3f3f3f3f3f;

ll dist[401][401];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;

    fill(dist[0], dist[401], LINF);
    for(int i=1;i<=n;i++) dist[i][i]=0;
    while(m--) {
        ll u, v, w; cin >> u >> v >> w;
        dist[u][v]=min(dist[u][v], w);
    }

    for(int m=1;m<=n;m++) {
        for(int s=1;s<=n;s++) {
            for(int e=1;e<=n;e++) {
                dist[s][e] = min(dist[s][e], dist[s][m]+dist[m][e]);
            }
        }
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(dist[i][j]==LINF) cout << "INF ";
            else cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
}
