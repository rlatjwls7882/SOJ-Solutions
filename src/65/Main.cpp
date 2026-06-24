#include<bits/stdc++.h>
using namespace std;

const int MAX = 200'001;

int SZ=1, arr[MAX*4];
int subTreeCnt[MAX];
vector<vector<int>> conn(MAX), child(MAX);
int nodeCnt, nodeNum[MAX], groupCnt, groupNum[MAX], head[MAX], par[MAX], depth[MAX];

void dfs1(int cur=0) {
    subTreeCnt[cur]=1;
    for(int nxt:conn[cur]) {
        if(!subTreeCnt[nxt]) {
            dfs1(nxt);
            subTreeCnt[cur]+=subTreeCnt[nxt];
            child[cur].push_back(nxt);
            if(subTreeCnt[child[cur].front()]<subTreeCnt[child[cur].back()]) swap(child[cur].front(), child[cur].back());
        }
    }
}

void dfs2(int cur=0, int dep=0) {
    int u=nodeNum[cur]=nodeCnt++;
    depth[u]=dep;
    groupNum[u]=groupCnt;
    if(head[groupCnt]==-1) head[groupCnt]=u;
    if(child[cur].empty()) {
        groupCnt++;
        return;
    }
    for(int nxt:child[cur]) {
        dfs2(nxt, dep+1);
        par[nodeNum[nxt]]=u;
    }
}

void construct(int n) {
    vector<int> v(n);
    for(int i=0;i<n;i++) cin >> v[i];
    for(int i=1;i<n;i++) {
        int u, v; cin >> u >> v;
        conn[u-1].push_back(v-1);
        conn[v-1].push_back(u-1);
    }
    dfs1();
    memset(head, -1, sizeof head);
    dfs2();
    while(SZ<=n) SZ<<=1;
    for(int i=0;i<n;i++) arr[SZ+nodeNum[i]]=v[i];
    for(int i=SZ-1;i;i--) arr[i]=max(arr[i*2], arr[i*2+1]);
}

void update(int i, int val) {
    i=nodeNum[i-1]+SZ;
    arr[i]=val;
    while(i>1) {
        i>>=1;
        arr[i]=max(arr[i*2], arr[i*2+1]);
    }
}

int maxRange(int L, int R, int nodeNum=1, int nodeL=0, int nodeR=SZ-1) {
    if(R<nodeL || nodeR<L) return INT_MIN;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum];
    int mid = nodeL+nodeR>>1;
    return max(maxRange(L, R, nodeNum*2, nodeL, mid), maxRange(L, R, nodeNum*2+1, mid+1, nodeR));
}

int query(int u, int v) {
    int ret=INT_MIN;
    u=nodeNum[u-1];
    v=nodeNum[v-1];
    while(groupNum[u]!=groupNum[v]) {
        int uHead=head[groupNum[u]], vHead=head[groupNum[v]];
        if(depth[uHead]>depth[vHead]) {
            ret=max(ret, maxRange(uHead, u));
            u=par[uHead];
        } else {
            ret=max(ret, maxRange(vHead, v));
            v=par[vHead];
        }
    }
    return max(ret, maxRange(min(u, v), max(u, v)));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    construct(n);
    while(q--) {
        int a, b, c; cin >> a >> b >> c;
        if(a==1) update(b, c);
        else cout << query(b, c) << '\n';
    }
}
