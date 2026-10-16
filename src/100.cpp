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

struct Faker {
    struct E{
        int x;ll a,b;
        bool operator<(const E&o)const{
            i128 l=(i128)(b+(a==0&&b==0))*o.a, r=(i128)(o.b+(o.a==0&&o.b==0))*a;
            return l!=r?l<r:x>o.x;
        }
    };
    int n,R;vll a,b;vi par,tail,nxt;vector<char>used;
    Faker(int n,int r):n(n),R(r),a(n+1),b(n+1),par(n+1),tail(n+1),nxt(n+1),used(n+1){iota(all(tail),0);}
    int find(int x){
        int r=x;while(used[r])r=par[r];
        while(x!=r){int p=par[x];par[x]=r;x=p;}
        return r;
    }
    ll res(){
        priority_queue<E>q; ll r=0;
        for(int i=1;i<=n;i++)r+=a[i]*b[i],i==R?void():q.push({i,a[i],b[i]});
        for(int z=1;z<n;z++)while(1){
            auto [x,ca,cb]=q.top();q.pop();
            if(used[x]||ca!=a[x]||cb!=b[x])continue;
            int p=find(par[x]);
            nxt[tail[p]]=x;tail[p]=tail[x];
            r+=b[x]*a[p];used[x]=1;par[x]=p;
            a[p]+=a[x];b[p]+=b[x];
            if(p!=R)q.push({p,a[p],b[p]});
            break;
        }
        return r;
    }
    vi trace(){vi r;for(int u=R;u;u=nxt[u])r.push_back(u);return r;}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    Faker f(n,1);
    for(int i=1;i<=n;i++)cin>>f.a[i];
    for(int i=1;i<=n;i++)cin>>f.b[i];
    for(int i=2;i<=n;i++)cin>>f.par[i];
    cout<<f.res();
}
