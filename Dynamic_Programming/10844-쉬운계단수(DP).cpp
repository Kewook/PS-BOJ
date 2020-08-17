/*
11057 오르막수 문제랑 매우 유사함.
*/

#include<iostream>

using namespace std;

const int mod = 1000000000;

int cache[101][10];

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   int N;
   cin >> N;

   for (int i = 1; i <= 9; i++)cache[1][i] = 1;
   
   for (int i = 2; i <= N; i++) {
      cache[i][0] = cache[i - 1][1];
      cache[i][9] = cache[i - 1][8];
      for (int j = 1; j <= 8; j++) {
         cache[i][j] = cache[i - 1][j - 1] + cache[i - 1][j + 1];
         cache[i][j] %= mod;
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