#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;

    ordered_set<int> S;
    while(q--) {
        string s; cin >> s;
        if(s=="insert") {
            int x; cin >> x;
            S.insert(x);
        } else if(s=="erase") {
            int x; cin >> x;
            S.erase(x);
        } else if(s=="order_of_key") {
            int x; cin >> x;
            cout << S.order_of_key(x) << '\n';
        } else if(s=="find_by_order") {
            int i; cin >> i;
            cout << *S.find_by_order(i-1) << '\n';
        } else {
            cout << S.size() << '\n';
        }
    }
}
