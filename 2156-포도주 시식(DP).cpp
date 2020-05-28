/*
오답 1 : dp[1]과 dp[2]를 초기화 했는데 이 둘을 고려 안해줌 반례 : 3 1000 1000 1
오답 2 : 계단오르기 문제와 유사하지만 차이점은 마지막 케이스를 마셔야하는지 안마셔도 되는지 차이점임. 안마셔도 되므로 그 점을 유의해서 풀어준다.
*/
#include<iostream>

using namespace std;

int dp[10001], ar[10001];

int max(int a, int b) { return a > b ? a : b; }

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   int n, ans = 0;
   cin >> n;

   for (int i = 1; i <= n; i++) {
      cin >> ar[i];
   }
   
   dp[1] = ar[1]; dp[2] = ar[1] + ar[2];

   ans = max(dp[1], dp[2]);

   for (int i = 3; i <= n; i++) {
      dp[i] = max(dp[i - 2] + ar[i], max(dp[i - 3] + ar[i - 1] + ar[i], dp[i - 1]));
      ans = ans < dp[i] ? dp[i] : ans;
   }

   cout << ans;

   return 0;
}