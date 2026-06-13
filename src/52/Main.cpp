#include<bits/stdc++.h>
using namespace std;

int n;
long long c[17][17], dp[17][1<<17];

long long dfs(int cur, int vis) {
    if(vis+1==1<<n) return dp[cur][vis]=c[cur][0];
    if(dp[cur][vis]!=-1) return dp[cur][vis];
    dp[cur][vis]=LONG_LONG_MAX;
    for(int i=0;i<n;i++) {
        if(!(vis&(1<<i))) {
            dp[cur][vis] = min(dp[cur][vis], dfs(i, vis|(1<<i))+c[cur][i]);
        }
    }
    return dp[cur][vis];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> c[i][j];
    memset(dp, -1, sizeof dp);
    cout << dfs(0, 1);
}
