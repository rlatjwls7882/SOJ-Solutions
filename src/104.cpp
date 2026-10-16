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

ll hilbert(int l,int r){
    int z=__builtin_clz((unsigned)(l|r)|1u);
    if(!(z&1))swap(l,r);
    ll d=0;
    for(int s=1<<(31-z);s;s>>=1){
        int a=!!(l&s),b=!!(r&s);
        d=(d<<2)|((3*b)^a);
        int t=(l^r^((s-1)&-b))&(a-1);
        l^=t;r^=t;
    }
    return d;
}
struct query{
    int l,r,k,idx;ll ord;
    bool operator<(const query& q)const{return ord<q.ord;}
};

int a[200'001],cnt[200'001], cntt[200'001];

void add(int x){
    cntt[cnt[a[x]]]--;
    cnt[a[x]]++;
    cntt[cnt[a[x]]]++;
}

void rem(int x){
    cntt[cnt[a[x]]]--;
    cnt[a[x]]--;
    cntt[cnt[a[x]]]++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];

    vector<query>qq;
    for(int i=0;i<q;i++){
        int l,r,k;cin>>l>>r>>k;
        qq.push_back({l,r,k,i,hilbert(l,r)});
    }
    sort(all(qq));

    cnt[0]=cntt[1]=1;
    int s=0,e=0;
    vector<int> res(q);
    for(auto [l,r,k,idx,ord]:qq){
        while(e<r)add(++e);
        while(s>l)add(--s);
        while(s<l)rem(s++);
        while(e>r)rem(e--);
        res[idx]=cntt[k];
    }
    for(auto e:res)cout<<e<<'\n';
}
