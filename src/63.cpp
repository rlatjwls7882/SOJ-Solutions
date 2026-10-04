#include<bits/stdc++.h>
using namespace std;

const int MAX=200'001;

int SZ=1;
vector<vector<int>> arr(MAX*4);

int query(int L, int R, int x) {
    int ret=0;
    for(L+=SZ, R+=SZ;L<=R;L>>=1, R>>=1) {
        if(L&1) ret+=upper_bound(arr[L].begin(), arr[L].end(), x)-arr[L].begin(), L++;
        if(!(R&1)) ret+=upper_bound(arr[R].begin(), arr[R].end(), x)-arr[R].begin(), R--;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    while(SZ<n) SZ<<=1;
    for(int i=0;i<n;i++) {
        int a; cin >> a;
        arr[i+SZ].push_back(a);
    }
    for(int i=SZ-1;i>0;i--) {
        int l=0, r=0;
        while(l<arr[i*2].size() || r<arr[i*2+1].size()) {
            if(r==arr[i*2+1].size() || l<arr[i*2].size() && arr[i*2][l]<arr[i*2+1][r]) arr[i].push_back(arr[i*2][l++]);
            else arr[i].push_back(arr[i*2+1][r++]);
        }
    }

    int ans=0;
    while(q--) {
        int a, b, c; cin >> a >> b >> c;
        int l = (a^ans)%n;
        int r = (b^ans)%n;
        int x = c^ans;
        ans = query(min(l, r), max(l, r), x);
        cout << ans << '\n';
    }
}
