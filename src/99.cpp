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

// op: '^' XOR, '|' OR, '&' AND. FWHT 길이 2^k·중간값 T 범위
// 정수 XOR 역변환은 각 성분이 길이로 나누어떨어져야 함
// mult: 빈 입력은 {}, 아니면 max(|a|,|b|) 이상의 최소 2^k 길이. 중간값 i128·결과 ll 범위
// XOR: |a[i]|,|b[i]|<=1e6, 각 길이<=2^20이면 결과 ll 범위. OR/AND는 별도 확인
template<class T> void FWHT(vector<T>&a,bool inv=false,char op='^'){
    int n=sz(a);
    for(int len=1;len<n;len<<=1) for(int i=0;i<n;i+=len<<1) for(int j=0;j<len;j++){
        T u=a[i+j],v=a[i+j+len];
        if(op=='|')a[i+j+len]=inv?v-u:v+u;
        else if(op=='&')a[i+j]=inv?u-v:u+v;
        else a[i+j]=u+v,a[i+j+len]=u-v;
    }
    if(inv&&op=='^')for(T&x:a)x/=n;
}
vll mult(const vll&_a,const vll&_b,char op='^'){
    if(_a.empty()||_b.empty())return {};
    int n=1;while(n<max(sz(_a),sz(_b)))n<<=1;
    vector<i128>a(n),b(n);
    for(int i=0;i<sz(_a);i++)a[i]=_a[i];
    for(int i=0;i<sz(_b);i++)b[i]=_b[i];
    FWHT(a,false,op);FWHT(b,false,op);
    for(int i=0;i<n;i++)a[i]*=b[i];
    FWHT(a,true,op);
    vll res(n);for(int i=0;i<n;i++)res[i]=(ll)a[i];
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int k;cin>>k;
    vll a(1<<k),b(1<<k);
    for(int i=0;i<(1<<k);i++)cin>>a[i];
    for(int i=0;i<(1<<k);i++)cin>>b[i];
    auto ret=mult(a,b);
    for(auto e:ret)cout<<e<<' ';
}
