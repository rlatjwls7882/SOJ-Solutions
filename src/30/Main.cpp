#include<bits/stdc++.h>
using namespace std;

int arr[1002][1002];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int h, w, n; cin >> h >> w >> n;
    while(n--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        arr[y1][x1]++;
        arr[y2+1][x1]--;
        arr[y1][x2+1]--;
        arr[y2+1][x2+1]++;
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
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}
