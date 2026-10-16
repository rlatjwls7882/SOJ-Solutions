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

struct Hungarian{
    int n,m;vector<vll>a;vll R,C,sl;vi mt,pre,vis;
    Hungarian(const vector<vll>&a):n(sz(a)-1),m(sz(a[0])-1),a(a),R(n+1),C(m+1),sl(m+1),mt(m+1),pre(m+1),vis(m+1){}
    ll res(){
        fill(all(R),0);fill(all(C),0);fill(all(mt),0);
        for(int i=1;i<=n;i++){
            mt[0]=i;fill(all(sl),LLONG_MAX);fill(all(vis),0);
            int j=0;
            do{
                vis[j]=1;int u=mt[j],nj=0;ll d=LLONG_MAX;
                for(int v=1;v<=m;v++)if(!vis[v]){
                    ll x=a[u][v]-R[u]-C[v];
                    if(x<sl[v])sl[v]=x,pre[v]=j;
                    if(sl[v]<d)d=sl[v],nj=v;
                }
                for(int v=0;v<=m;v++)if(vis[v])R[mt[v]]+=d,C[v]-=d;else sl[v]-=d;
                j=nj;
            }while(mt[j]);
            do{int p=pre[j];mt[j]=mt[p];j=p;}while(j);
        }
        return -C[0];
    }
    vi matching(){vi r(n+1);for(int j=1;j<=m;j++)if(mt[j])r[mt[j]]=j;return r;}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<vll>a(n+1,vll(n+1));
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
    Hungarian h(a);
    cout<<h.res();
}
