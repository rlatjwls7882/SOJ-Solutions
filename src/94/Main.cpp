#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

// 위치/값 x를 정하며 절댓값 비용을 최소화하는 DP에서 사용
// dp[i][x]=|x-a[i]|+min_{l<=x-y<=r}dp[i-1][y] 꼴
// → slide(l,r), addAbs(a[i]) 반복 후 res가 답
// addLeft(a): +=max(a-x,0), addRight(a): +=max(x-a,0), addAbs(a): +=|x-a|
struct SlopeTrick{
    priority_queue<ll>L;
    priority_queue<ll,vector<ll>,greater<>>R;
    ll dl=0, dr=0, res=0;
    ll topL(){return L.top()+dl;}
    ll topR(){return R.top()+dr;}
    void pushL(ll x){L.push(x-dl);}
    void pushR(ll x){R.push(x-dr);}
    void addLeft(ll x,int k=1){
        while(k--){
            if(!R.empty()&&topR()<x) res+=x-topR(),pushL(topR()),R.pop(),pushR(x);
            else pushL(x);
        }
    }
    void addRight(ll x,int k=1){
        while(k--){
            if(!L.empty()&&x<topL()) res+=topL()-x,pushR(topL()),L.pop(),pushL(x);
            else pushR(x);
        }
    }
    void addAbs(ll x,int k=1){addLeft(x,k); addRight(x,k);}
    void slide(ll l,ll r){dl+=l; dr+=r;}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; string s; cin >> n >> s;
    s="S"+s+"S";

    SlopeTrick st;
    int k=0;
    for(int i=0;i<s.length();i++) {
        char ch=s[i];
        if(ch=='S') {
            st.slide(0, 2);
            if(i==0 || i==s.length()-1) st.addAbs(k, n);
            else st.addAbs(k);
        } else {
            k++;
        }
    }
    if(2*(n-k+1)<k) cout << -1;
    else cout << st.res;
}
