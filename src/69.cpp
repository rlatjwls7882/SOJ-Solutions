#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    deque<pair<int, long long>> deq;
    for(int i=0;i<n;i++) {
        while(!deq.empty() && i-deq.front().first>k) deq.pop_front();
        long long a; cin >> a;
        if(!deq.empty()) a+=deq.front().second;
        while(!deq.empty() && deq.back().second>a) deq.pop_back();
        deq.push_back({i, a});
    }
    cout << deq.back().second;
}
