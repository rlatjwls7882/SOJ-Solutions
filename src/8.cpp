#include<bits/stdc++.h>
using namespace std;

set<vector<int>> vis;
queue<vector<int>> q;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    q.push(a);

    int res=n;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        res = min(res, (int)cur.size());
        for(int i=0;i<cur.size();i++) {
            int sum=0;
            for(int j=i;j<cur.size();j++) {
                sum+=cur[j];
                if(sum==10) {
                    vector<int> next;
                    for(int k=0;k<cur.size();k++) {
                        if(k<i || k>j) next.push_back(cur[k]);
                    }
                    if(!vis.count(next)) {
                        q.push(next);
                        vis.insert(next);
                    }
                    break;
                }
            }
        }
    }
    cout << res;
}