#include<bits/stdc++.h>
using namespace std;

int cnt[100'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    while(n--) {
        int a; cin >> a;
        cnt[a]++;
    }

    for(int i=1;i<=100'000;i++) {
        while(cnt[i]--) {
            cout << i << ' ';
        }
    }
}