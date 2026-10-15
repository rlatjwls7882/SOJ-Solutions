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

using cpx=complex<ld>;
void FFT(vector<cpx>&a,bool inv=false){
    int n=sz(a);
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit)j^=bit,bit>>=1;
        j^=bit;
        if(i<j)swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        ld ang=(inv?-2:2)*PI/len;
        cpx w(cosl(ang),sinl(ang));
        for(int i=0;i<n;i+=len){
            cpx wp(1,0);
            for(int j=0;j<len/2;j++){
                cpx u=a[i+j],v=a[i+j+len/2]*wp;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                wp*=w;
            }
        }
    }
    if(inv)for(cpx&x:a)x/=n;
}
vll Mult(const vll&a,const vll&b){
    const ll B=1<<10;
    int n=2;
    while(n<sz(a)+sz(b))n<<=1;
    if(1LL*sz(a)*sz(b)<=4'000'000){
        vll res(n);
        for(int i=0;i<sz(a);i++)
            for(int j=0;j<sz(b);j++)res[i+j]+=a[i]*b[j];
        return res;
    }
    vector<cpx>A(n),C(n);
    for(int i=0;i<sz(a);i++)A[i]=cpx(a[i]%B,a[i]/B);
    for(int i=0;i<sz(b);i++)C[i]=cpx(b[i]%B,b[i]/B);
    FFT(A);FFT(C);
    vector<cpx>D(n);
    for(int i=0;i<n;i++){
        int j=(n-i)&(n-1);
        cpx ai=(A[i]-conj(A[j]))*cpx(0,-0.5L);
        cpx ci=(C[i]-conj(C[j]))*cpx(0,-0.5L);
        D[i]=ai*ci;
    }
    for(int i=0;i<n;i++)A[i]*=C[i];
    FFT(A,true);FFT(D,true);
    vll res(n);
    for(int i=0;i<n;i++)res[i]=(ll)((i128)llround(A[i].real())+(i128)llround(A[i].imag())*B+(i128)llround(D[i].real())*(B*B+1));
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    vll a(n),b(m);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    auto ret=Mult(a,b);
    for(int i=0;i<n+m-1;i++)cout<<ret[i]<<' ';
}
