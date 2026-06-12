#include<bits/stdc++.h>
using namespace std;

const int MAX = 100'001;

int n, m, k, a[MAX], b[MAX], level[MAX];
vector<vector<int>> conn(MAX);

void bfs() {
    queue<int> q;
    for(int i=1;i<=n;i++) {
        if(a[i]==-1) {
            level[i]=0;
            q.push(i);
        } else {
            level[i]=-1;
        }
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(b[next]!=-1 && level[b[next]]==-1) {
                level[b[next]]=level[cur]+1;
                q.push(b[next]);
            }
        }
    }
}

bool dfs(int cur) {
    for(int next:conn[cur]) {
        if(b[next]==-1 || level[b[next]]==level[cur]+1 && dfs(b[next])) {
            b[next]=cur;
            a[cur]=next;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    while(k--) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
    }

    memset(a, -1, sizeof a);
    memset(b, -1, sizeof b);
    int res=0;
    while(true) {
        bfs();
        int flow=0;
        for(int i=1;i<=n;i++) flow+=a[i]==-1 && dfs(i);
        if(!flow) break;
        res+=flow;
    }
    cout << res;
}
