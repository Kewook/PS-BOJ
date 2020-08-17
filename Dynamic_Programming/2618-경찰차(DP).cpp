#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

struct Info {
   int ypos, xpos;
};

int N, W;
int dp[1001][1001], hist[1001];
Info info1[1001], info2[1001];

int getDist(Info i1, Info i2) {
   return abs(i1.ypos - i2.ypos) + abs(i1.xpos - i2.xpos);
}

//dp[c1][c2]는 1번 차가 c1번 사건까지 처리하고 2번차가 c2번 사건까지 처리했을때 거리합의 최소값임.
//max(c1, c2) + 1은 둘중 하나가 사건을 해결하고 그 다음으로 넘어가기 위함.
int sol(int c1, int c2) {
   if (c1 == W || c2 == W)return 0;
   
   if (dp[c1][c2] != -1)return dp[c1][c2];

   int ret1 = sol(max(c1, c2) + 1, c2) + getDist(info1[c1], info1[max(c1, c2) + 1]);
   int ret2 = sol(c1, max(c1, c2) + 1) + getDist(info2[c2], info2[max(c1, c2) + 1]);

   return dp[c1][c2] = min(ret1, ret2);
}

//똑같이 dp배열을 모두 갱신시켜줬기 때문에 처음부터 돌아보면서 어떤 차가 맡았는지 알아봐준다.
void getAns(int c1, int c2, int idx) {
   if (c1 == W || c2 == W)return;

   int dist1 = dp[max(c1, c2) + 1][c2] + getDist(info1[c1], info1[max(c1, c2) + 1]);
   int dist2 = dp[c1][max(c1, c2) + 1] + getDist(info2[c2], info2[max(c1, c2) + 1]);
   
   if (dist1 < dist2) {
      hist[idx] = 1;
      getAns(max(c1, c2) + 1, c2, idx + 1);
   }
   else {
      hist[idx] = 2;
      getAns(c1, max(c1, c2) + 1, idx + 1);
   }
}
int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);
   
   cin >> N >> W;
   info1[0] = { 1,1 }, info2[0] = { N,N };

   memset(dp, -1, sizeof(dp));

   // 사건 0번은 각각 경찰차 1, 2의 시작위치임
   for (int i = 1; i <= W; i++) {
      cin >> info1[i].ypos >> info1[i].xpos;
      info2[i] = info1[i];
   }
   
   cout << sol(0, 0) << "\n";

   getAns(0, 0, 0);
   for (int i = 0; i < W; i++) {
      cout << hist[i] << "\n";
   }

   return 0;
}