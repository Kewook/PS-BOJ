/*
시간초과 매우매우 많이 났던 문제

dfs탐색할때 dfs(idx , cnt + 1)이라고 보내줘서 오류가 났다. 예를들어 1번 2번 가로선까지 탐색이 끝나고 1번 6번까지 진행을 했을때 dfs(i, cnt + 1)에서 i대신 idx를 보내주면 2번 가로선부터 6번가로선까지 탐색을 할때
세로선(열)을 모두 계속 탐색해주어야 하기때문에 시간초과가 난다.
*/
#include<iostream>

using namespace std;

int N, H, M, ans;
bool check[32][12];

bool simulate() {
   for (int i = 1; i <= N; i++) {
      int pos = i;
      for (int j = 1; j <= H; j++) {
         if (check[j][pos - 1])pos--;
         else if (check[j][pos])pos++;
      }
      if (i != pos)return false;
   }
   return true;
}

void dfs(int idx, int cnt) {
   if (cnt > 3)return;
   if (simulate()) {
      ans = ans > cnt ? cnt : ans;
      return;
   }


   for (int i = idx; i <= H; i++) {
      for (int j = 1; j < N; j++) {
         if (check[i][j])continue;
         if (check[i][j - 1] || check[i][j + 1])continue;

         check[i][j] = true;
         dfs(i, cnt + 1);
         check[i][j] = false;
      }
   }
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> M >> H;
   ans = 987654321;

   for (int i = 0; i < M; i++) {
      int a, b;
      cin >> a >> b;
      check[a][b] = true;
   }

   dfs(1, 0);

   if (ans == 987654321)cout << -1;
   else cout << ans;

   return 0;
}