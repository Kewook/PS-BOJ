#include<iostream>

using namespace std;

//dp[0] = 4부터 2씩 늘어갈때 새로 생기는 모양을 처리해주기 위함.
int N, dp[31] = { 1,0,3 };

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);
   
   cin >> N;

   if (!(N % 2)) {
      for (int i = 4; i <= N; i+=2) {
         //i-2인경우에는 2에서 나오는 모양 세개를 더 붙일수 있다.
         dp[i] = dp[i - 2] * 3;
         for (int j = 4; i - j >= 0; j+=2) {
            //크기차이가 4가 나는것부터 시작한다.
            //ex) i가 10이라 할때 0~6까지를 고려한다
            //0일때는 10에서 새로생겨는 경우 2가지
            //2일때는 8에서 새로 생겼던 모양 2가지에 2를 붙인것
            //4일때는 6에서 새로 생겼던 모양 2가지에 4를 붙인것
            //6일때는 4에서 새로 생겼던 모양 2가지에 6을 붙인것
            dp[i] += dp[i - j] * 2;
         }
      }
   }
   cout << dp[N];
   
   return 0;
}