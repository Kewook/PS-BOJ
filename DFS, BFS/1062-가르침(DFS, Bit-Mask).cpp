/*
틀린이유 : a, t, i, c, n은 무조건 포함해야 하는데 포함시키지 않는 경우도 고려했다.(시간도 줄여줌)
시간초과 이유 : 몇개의 단어를 가르칠수 있는지 판별할때 맨앞의 anta와 맨뒤의 tica를 제거한다.
*/

#include<iostream>
#include<string>

using namespace std;

string word[55];
bool check[26];
int N, K, ans;

void dfs(int cnt, int idx) {
   if (cnt == K) {
      int count = 0;
      for (int i = 0; i < N; i++) {
         bool flag = true;
         for (int j = 0; j < word[i].length(); j++) {
            if (!check[word[i][j] - 'a']) {
               flag = false;
               break;
            }
         }
         if (flag)count++;
      }
      ans = ans < count ? count : ans;
      return;
   }

   for (int i = idx; i < 26; i++) {
      if (check[i])continue;
      check[i] = true;
      dfs(cnt + 1, i);
      check[i] = false;
   }
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);
   
   cin >> N >> K;

   if (K < 5) {
      cout << 0;
      return 0;
   }

   for (int i = 0; i < N; i++) {
      string str;
      cin >> str;
      
      int cnt = 0;
      word[i].resize(str.length() - 8);
      for (int j = 4; j < str.length() - 4; j++) {
         word[i][cnt++] = str[j];
      }
   }

   ans = 0;
   check[0] = check['n' - 'a'] = check['t' - 'a'] = check['i' - 'a'] = check['c' - 'a'] = true;
   
   dfs(5, 0);
   
   cout << ans;
   return 0;
}

/////////비트마스크를 사용한 방법
#include<iostream>
#include<string>

using namespace std;

//10000010000100000101
const int idx = 0x82105;

int word[55];
int N, K, ans;

void dfs(int cnt,int check, int idx) {
   if (cnt == K) {
      int count = 0;

      for (int i = 0; i < N; i++) {
         if ((word[i] & check) == word[i])count++;
      }

      ans = ans < count ? count : ans;
      return;
   }

   for (int i = idx; i < 26; i++) {
      if (check & (1 << i))continue;
      dfs(cnt + 1, check | (1 << i), i);
   }
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> K;

   string str;
   for (int i = 0; i < N; i++) {
      cin >> str;
      
      for (char c : str) {
         word[i] |= 1 << c - 'a';
      }
   }

   ans = 0;
   dfs(5, idx, 0);

   cout << ans;
   return 0;
}