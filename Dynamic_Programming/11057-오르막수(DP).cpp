/*
dp[N][digit] = 첫자리가 digit으로 시작하는 N자리 숫자의 오르막수 개수
따라서 dp[N][digit] = dp[N-1][digit] ~ dp[N-1][9]까지의 합이다.

틀린이유 1. MOD분배법칙 오류 cache[i][j] += cache[i-1][k] % mod;라 하여 오답.

유사문제 : 10844-쉬운계단수.
*/

#include<iostream>

using namespace std;

const int mod = 10007;
int cache[1001][10];

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   int N;
   
   cin >> N;

   for (int i = 0; i <= 9; i++)cache[1][i] = 1;
   
   for (int i = 2; i <= N; i++) {
      for (int j = 0; j <= 9; j++) {
         for (int k = j; k <= 9; k++) {
            cache[i][j] += cache[i - 1][k];
            cache[i][j] %= mod;
         }
      }
   }

   int ans = 0;
   for (int i = 0; i <= 9; i++) {
      ans += cache[N][i];
      ans %= mod;
   }
   
   cout << ans;

   return 0;
}