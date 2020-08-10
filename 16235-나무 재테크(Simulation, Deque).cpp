/*
시간초과에 유의해야함. 처음에는 tree를 셀별로 관리하지 않고 그냥 vector<Tree> tree로 관리하였다.
이렇게 관리를 하면 가을에 나무가 추가됐을경우에 문제가 발생한다. tree에 1000가지 나무가 있다고 했을때 추가되는 나무 때문에 1000가지가 더 되는 나무가 모두 sort가 이루어져야한다.
따라서 셀별로 관리를 해준다면 추가가되는 나무들 사이에서만 정렬상태를 유지해준다면 시간을 많이 줄일 수 있다.
이를 구현하기 위해 덱을 사용했다.

+ 2번째 오답이유 : (r, c)는 ypos, xpos를 나타내는데 이를 ()로 표기하자고 문제에 명시되어있다. 따라서 (x, y)라는 표기는 x가 ypos가 되어야하고 y가 xpos가 되어야한다.
(문제를 내 직관에 끼워맞춰보지 말자)
*/
#include<iostream>
#include<vector>
#include<deque>

using namespace std;

struct Tree {
   int ypos, xpos, age;
};


int A[11][11], farm[11][11], N, M, K;
deque<int> tree[11][11];
int dy[] = { -1,-1,-1,0,1,1,1,0 };
int dx[] = { -1,0,1,1,1,0,-1,-1 };

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> M >> K;
   for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
         cin >> A[i][j];
         farm[i][j] = 5;
      }
   }

   for (int i = 0; i < M; i++) {
      int x, y, a;
      cin >> x >> y >> a;
      tree[x][y].push_back(a);
   }

   while (K > 0) {
      //봄
      vector<Tree> dead;
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= N; j++) {
            int size = tree[i][j].size();
            for (int k = 0; k < size; k++) {
               int age = tree[i][j].front();
               tree[i][j].pop_front();

               if (farm[i][j] >= age) {
                  farm[i][j] -= age;
                  tree[i][j].push_back(age + 1);
               }
               else dead.push_back({ i, j, age });
            }
         }
      }

      //여름
      for (int i = 0; i < dead.size(); i++) {
         farm[dead[i].ypos][dead[i].xpos] += (dead[i].age / 2);
      }
      
      vector<Tree> breed;
      //가을
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= N; j++) {
            int size = tree[i][j].size();
            for (int k = 0; k < size; k++) {
               int age = tree[i][j].front();
               tree[i][j].pop_front();
               if (!(age % 5))breed.push_back({ i, j, age });
               tree[i][j].push_back(age);
            }
         }
      }
      for (int i = 0; i < breed.size(); i++) {
         int ypos = breed[i].ypos, xpos = breed[i].xpos;
         for (int k = 0; k < 8; k++) {
            int ny = ypos + dy[k], nx = xpos + dx[k];
            if (ny < 1 || nx < 1 || ny > N || nx  > N)continue;
            tree[ny][nx].push_front(1);
         }
      }

      //겨울
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= N; j++) {
            farm[i][j] += A[i][j];
         }
      }
      K--;
   }

   int ans = 0;
   for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
         ans += tree[i][j].size();
      }
   }

   cout << ans;

   return 0;
}