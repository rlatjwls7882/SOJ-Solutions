#include<bits/stdc++.h>
using namespace std;

int n, m, arr[8];
bool vis[8];

void back(int depth=0) {
    if(depth==m) {
        for(int i=0;i<m;i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i=0;i<n;i++) {
        if(!vis[i]) {
            vis[i]=true;
            arr[depth]=i+1;
            back(depth+1);
            vis[i]=false;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    back();
}
