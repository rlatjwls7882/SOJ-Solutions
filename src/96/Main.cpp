#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) cout << 'F'; cout << '\n';
    if(n>=2) for(int i=0;i<n;i++) cout << '.'; cout << '\n';
    for(int i=2;i<n;i++) {
        for(int j=0;j<n;j++) cout << 'M'; 
        cout << '\n';
    }
}
