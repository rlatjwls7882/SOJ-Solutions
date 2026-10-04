#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 200'002;

int n, a[MAX], isLeader[MAX], moveGood[MAX], pIdx[MAX], sIdx[MAX], pMin[MAX][2], sMax[MAX][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    if(n==1) return !(cout << 1);

    fill(&pMin[0][0], &pMin[MAX-1][2], INF);
    for(int i=1;i<=n;i++) {
        pMin[i][0]=pMin[i-1][0];
        pMin[i][1]=pMin[i-1][1];
        pIdx[i]=pIdx[i-1];
        if(pMin[i][0]>a[i]) {
            pMin[i][1]=pMin[i][0];
            pMin[i][0]=a[i];
            pIdx[i]=i;
        } else if(pMin[i][1]>a[i]) {
            pMin[i][1]=a[i];
        }
    }

    for(int i=n;i>=1;i--) {
        sMax[i][0]=sMax[i+1][0];
        sMax[i][1]=sMax[i+1][1];
        sIdx[i]=sIdx[i+1];
        if(sMax[i][0]<a[i]) {
            sMax[i][1]=sMax[i][0];
            sMax[i][0]=a[i];
            sIdx[i]=i;
        } else if(sMax[i][1]<a[i]) {
            sMax[i][1]=a[i];
        }
    }

    // moveGood[i] : i를 최적으로 움직였을때 추가로 리더가 생기는 개수
    int cnt=0; // 안움직여도 리더인 경우
    for(int i=1;i<=n;i++) {
        if(a[i]<=pMin[i][0] || a[i]>=sMax[i][0]) {
            cnt++;
            isLeader[i]=true;
            continue;
        }
        if(pMin[i][1]>=a[i]) moveGood[pIdx[i]]++;
        if(sMax[i][1]<=a[i]) moveGood[sIdx[i]]++;
    }

    int res=0;
    for(int i=1;i<=n;i++) res = max(res, cnt+moveGood[i]+(!isLeader[i]));
    cout << res;
}
