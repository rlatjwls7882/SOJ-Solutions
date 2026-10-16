#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("fma")
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define x first
#define y second
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
#define compress(x) sort(all(x)), x.erase(unique(all(x)), x.end())

typedef long long ll;
typedef long double ld;
typedef __int128 i128;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> T sq(T x) { return x*x; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ld PI = acosl(-1);
const ld EPS = 1e-10;

mt19937 rd((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd_int(0, 0); // rnd_int(rd)
uniform_real_distribution<double> rnd_real(0, 1); // rnd_real(rd)

vi StableMarriage(const vector<vi>&men,const vector<vi>&women){
    int n=sz(men);vector<vi>rank(n,vi(n));vi a(n,-1),b(n,-1),ptr(n);queue<int>q;
    for(int v=0;v<n;v++)for(int i=0;i<n;i++)rank[v][women[v][i]]=i;
    for(int u=0;u<n;u++)q.push(u);
    while(!q.empty()){
        int u=q.front();q.pop();int v=men[u][ptr[u]++];
        if(b[v]<0||rank[v][u]<rank[v][b[v]]){
            if(b[v]>=0)q.push(b[v]);
            a[u]=v;b[v]=u;
        }else q.push(u);
    }return a;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;cin>>q;
    while(q--){
        int n;cin>>n;
        vector<vi> a(n,vi(n)),b(n,vi(n));
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>a[i][j];
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>b[i][j];
        vi ret=StableMarriage(a,b);
        for(auto e:ret)cout<<e<<' ';
        cout<<'\n';
    }
}
