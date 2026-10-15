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

struct EERTREE {
    struct Node {int len=0,link=0,occ=0,pos=-1;array<int,26>next{};};
    vector<Node> tree{{-1},{0}};
    string s="$";
    int last=1;bool built=false;
    EERTREE(int n=0){tree.reserve(n+2);s.reserve(n+1);}
    int count(){return sz(tree)-2;}
    string get(int v){return s.substr(tree[v].pos-tree[v].len+1,tree[v].len);}
    int getLink(int v){
        int i=sz(s)-1;
        while(s[i-1-tree[v].len]!=s[i])v=tree[v].link;
        return v;
    }
    int add(char ch){
        s+=ch;int c=ch-'a',cur=getLink(last);
        if(!tree[cur].next[c]){
            int now=sz(tree);tree.push_back({tree[cur].len+2});
            tree[now].pos=sz(s)-1;
            tree[now].link=tree[now].len==1?1:tree[getLink(tree[cur].link)].next[c];
            tree[cur].next[c]=now;
        }
        last=tree[cur].next[c];
        tree[last].occ++;
        return last;
    }
    void add(const string&str){for(char c:str)add(c);}
    void build(){
        if(built)return;built=true;
        for(int i=sz(tree)-1;i>=2;i--)tree[tree[i].link].occ+=tree[i].occ;
    }
    ll countAll(){
        ll res=0;
        for(int i=2;i<sz(tree);i++)res+=tree[i].occ;
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;string s;cin>>n>>s;
    EERTREE eertree(n);
    eertree.add(s);
    eertree.build();
    cout << eertree.count()<<' '<<eertree.countAll();
}
