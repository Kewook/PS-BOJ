/*
kanpsack문제 표본
==제발 버벅거리지좀 말자.
*/

//top-down
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int dp[101][100005];
int cost[101], value[101];
int N, K;

int sol(int idx, int weight) {
   if (idx > N)return 0;

   int &ret = dp[idx][weight];
   
   if (ret != -1)return ret;

   if (cost[idx] > weight)return sol(idx + 1, weight);
   else return ret = max(sol(idx + 1, weight), sol(idx + 1, weight - cost[idx]) + value[idx]);
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> K;
   
   for (int i = 1; i <= N; i++) {
      cin >> cost[i] >> value[i];
   }
   
   memset(dp, -1, sizeof(dp));
   cout << sol(1, K);

   return 0;
}

//bottom-up
#include<iostream>
#include<algorithm>

using namespace std;

int dp[100005];

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   int N, K;
   cin >> N >> K;

   for (int i = 1; i <= N; i++) {
      int cost, value;
      cin >> cost >> value;
      for (int j = K; j >= cost; j--) {
         dp[j] = max(dp[j], dp[j - cost] + value);
      }
   }
      
   cout << dp[K];

   return 0;
}