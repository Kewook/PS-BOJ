/*
cache[i] : i번째까지 클릭했을때 화면에 나올수 있는 A의 총합
시간초과 포인트를 잡고 DP로 접근한것은 좋았으나 점화식을 세우지 못했다.
-> 문제의 흐름을 잘 파악하는 것도 중요한것 같다.


이 문제의 포인트는 어느 지점부터 버퍼에 있는 값을 붙여넣기 한 값이 최대값이 된다.

아래 표의 값과 1번버튼만 누른 결과비교를 통해 아무리 V버튼을 눌러도 6번째까지는 무조건 1번 버튼만 누른것이 최대값임을 알수 있다.
   1 2 3 4 5 6
1 |  
4 |          A
4 |        A C
4 |      A C V
4 |    A C V V
4 |  A C V V V
4 |A C V V V V

그냥 1번버튼만 눌렀을 경우와 3번의 버튼조작으로 버퍼에 새로운 값을 더한것을 비교하려면 다음과 같아야한다.

cache[i] = max(cache[i], cache[i - offset] + cache[i - offset] * (offset - 2));
cache[i-offset] : 2, 3번의 버튼조작으로 버퍼에 복사되는 값.
cache[i-offset] * (offset - 2) : 버퍼에 복사된 값을 4번버튼을 연속적으로 누른것.(offset - 2번 4번 버튼을 누른것이기 때문에 offset은 3부터 시작한다.) 
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N;
long long cache[101];


int main(void) {
   ios::sync_with_stdio(NULL);
   cin.tie(NULL); cout.tie(NULL);
   
   cin >> N;
   
   for (int i = 1; i <= N; i++)cache[i] = i;

   for (int i = 7; i <= N; i++) {
      for (int offset = 3; offset < i; offset++) {
         cache[i] = max(cache[i], cache[i - offset] + cache[i - offset] * (offset - 2));
      }
   }

   cout << cache[N];
   return 0;
}