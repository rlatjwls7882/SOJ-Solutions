#include<bits/stdc++.h>
using namespace std;

int dx[]={1, 1, -1, -1};
int dy[]={1, -1, 1, -1};
int ddx[]={2, 2, 1, 1, -1, -1, -2, -2};
int ddy[]={1, -1, 2, -2, 2, -2, 1, -1};

int vis[1000][1000][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    memset(vis, -1, sizeof vis);
    queue<tuple<int, int, int>> q; q.push({0, 0, 0});
    vis[0][0][0]=0;
    while(!q.empty()) {
        auto [x, y, d]=q.front(); q.pop();
        if(x==n-1 && y==m-1) return !(cout << vis[x][y][d]);
        if(d==0) {
            for(int i=0;i<8;i++) {
                int nx=x+ddx[i];
                int ny=y+ddy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m || vis[nx][ny][1]!=-1) continue;
                vis[nx][ny][1]=vis[x][y][d]+1;
                q.push({nx, ny, 1});
            }
        } else {
            for(int i=0;i<4;i++) {
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m || vis[nx][ny][0]!=-1) continue;
                vis[nx][ny][0]=vis[x][y][d]+1;
                q.push({nx, ny, 0});
            }
        }
    }
}
