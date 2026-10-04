#include<bits/stdc++.h>
using namespace std;

int cnt[101];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;

    int i=0;
    while(n--) {
        int a; cin >> a;
        if(++cnt[a]>cnt[i] || cnt[a]==cnt[i]&&a<i)i=a;
    }
    cout<<i;
}
