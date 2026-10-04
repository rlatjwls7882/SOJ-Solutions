#include<bits/stdc++.h>
using namespace std;

const int MAX = 20001;

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

int neg(int x) { return x%2 ? x+1 : x-1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b; cin >> a >> b;
        a = a<0 ? -2*a : 2*a-1;
        b = b<0 ? -2*b : 2*b-1;
        conn[neg(a)].push_back(b);
        conn[neg(b)].push_back(a);
    }
    for(int i=1;i<=2*n;i++) if(!vis[i]) dfs(i);

    for(int i=1;i<=2*n;i+=2) {
        if(par[i]==par[i+1]) return !(cout << "No");
    }
    cout << "Yes";
}
