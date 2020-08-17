/*
처음에는 도시 번호를 부여해서 adj배열을 만들려고함
메모리 제한이 16MB인데 도시 번호는 10000번도 나온다
*/
#include<iostream>

using namespace std;

int N, M, K;
int hori[101][101], vert[101][101];
long long dp[101][101];

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> M >> K;

   for (int i = 0; i < K; i++) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;

      if (a == c) {
         if (b < d)vert[a][b] = 1;
         else vert[c][d] = 1;
      }
      if (b == d) {
         if (a < c)hori[a][b] = 1;
         else hori[c][d] = 1;
      }

   }
   
   dp[0][0] = 1;
   
   for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= M; j++) {
         if (i - 1 >= 0 && !hori[i - 1][j])dp[i][j] += dp[i - 1][j];
         if (j - 1 >= 0 && !vert[i][j - 1])dp[i][j] += dp[i][j - 1];
      }
   }

   cout << dp[N][M];
   return 0;
}