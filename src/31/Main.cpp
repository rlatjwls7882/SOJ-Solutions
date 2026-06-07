#include<bits/stdc++.h>
using namespace std;

int arr[1003][1003];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int h, w, n; cin >> h >> w >> n;
    while(n--) {
        int x, y, k; cin >> x >> y >> k;
        arr[y][x]++;
        arr[y][x+1]--;
        arr[y+k][x]--;
        arr[y+k][x+k+1]++;
        arr[y+k+1][x+1]++;
        arr[y+k+1][x+k+1]--;
    }

    for(int i=1;i<=h;i++) {
        for(int j=1;j<=w;j++) {
            arr[i][j+1]+=arr[i][j];
        }
    }
    for(int j=1;j<=w;j++) {
        for(int i=1;i<=h;i++) {
            arr[i+1][j]+=arr[i][j];
        }
    }
    for(int i=1;i<=h;i++) {
        for(int j=1;j<=w;j++) {
            arr[i+1][j+1]+=arr[i][j];
        }
    }
    for(int i=1;i<=h;i++) {
        for(int j=1;j<=w;j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}
