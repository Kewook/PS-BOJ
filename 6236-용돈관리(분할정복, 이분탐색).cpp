/*
이분탐색이다 처음에는 withdraw를 주는 방식으로 생각했는데 그런게 아니라
문제를 읽어보면 정확히 M번만 통장에서 돈을 빼야한다. 따라서 M이하의 수가 나오지 않게 하려면
연속된 날의 지출의 합이 얼마 이하여야하고 또한 이 연속된 날들의 집합들이 M개가 되어야 한다.
#include<iostream>

int main() {
   int n, m, ar[100000];
   scanf("%d %d", &n, &m);

   for (int i = 0; i < n; i++)scanf("%d", &ar[i]);

   int l = 0, h = 10000;

   while (l + 1 < h) {
      int mid = (l + h) / 2;

      int cnt = 1;
      int withdraw = mid;
      bool flag = false;

      for (int i = 0; i < n; i++) {
         if (ar[i] > mid) {
            mid = ar[i] - 1;
            flag = true;
            break;
         }
         if (withdraw < ar[i]) {
            withdraw = mid;
            cnt++;
         }
         else withdraw -= ar[i];
      }

      if (flag) l = mid;
      else if (cnt <= m) h = mid;
      else l = mid;
   }
   printf("%d",h);

   return 0;
}
*/
/*
2번째 제출
여기서 가장 크게 실수했던점은 일단 cnt를 0으로 바꾸고 풀었다가 계속 정답이 나오지 않아 1로 바꾸고 풀어 정답이 나와서 제출을 하였는데 오답
따라서 무엇이 문제인지 질문검색을 해봤다. 기본적으로 문제에 대한 이해가 완벽히 되지 않았다. n개의 날짜 모두 필요한 지출이 최대값인 10000원이라면
M이 1일경우 한번에 인출해야하는 금액은 n*10000이 된다 따라서 h의 인덱스가 잘못됨.
#include<iostream>

int main() {
   int n, m, ar[100000];
   scanf("%d %d", &n, &m);

   for (int i = 0; i < n; i++)scanf("%d", &ar[i]);

   int l = 0, h = 10000;

   while (l + 1 < h) {
      int mid = (l + h) / 2;

      int cnt = 1;
      int sum = 0;
      bool flag = false;

      for (int i = 0; i < n; i++) {
         if (ar[i] > mid) {
            mid = ar[i] - 1;
            flag = true;
            break;
         }

         if (sum + ar[i] > mid) {
            sum = ar[i];
            cnt++;
         }
         else sum += ar[i];
      }

      if (flag) l = mid;
      else if (cnt <= m) h = mid;
      else l = mid;
   }
   printf("%d", h);

   return 0;
}
 */
#include<iostream>

int main() {
   int n, m, ar[100000];
   scanf("%d %d", &n, &m);

   for (int i = 0; i < n; i++)scanf("%d", &ar[i]);

   int l = 0, h = 1000000000;

   while (l + 1 < h) {
      int mid = (l + h) / 2;

      int cnt = 1;
      int sum = 0;
      bool flag = false;

      for (int i = 0; i < n; i++) {
         if (ar[i] > mid) {
            mid = ar[i] - 1;
            flag = true;
            break;
         }

         if (sum + ar[i] > mid) {
            sum = ar[i];
            cnt++;
         }
         else sum += ar[i];
      }

      if (flag) l = mid;
      else if (cnt <= m) h = mid;
      else l = mid;
   }
   printf("%d", h);

   return 0;
}