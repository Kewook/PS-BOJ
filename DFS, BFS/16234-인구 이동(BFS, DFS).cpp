/*
오류 1. 처음에는 check[][]를 boolean 변수로 두어 L <= gap <= R일경우에 모두 true로 해주어 bfs를 돌려주었다
하지만 이렇게 하면 구역이 모두 하나로 합쳐진다.
반례
4 1 9
96 93 74 30
60 90 65 96
5 27 17 98
10 41 46 20
correct: 1

5 1 5
88 27 34 84 9
40 91 11 30 81
2 88 65 26 75
75 66 16 14 28
89 10 5 30 75
correct: 1

따라서 idx를 두어 구역을 번호로 나누어주었다. 그 후 idx에 맞게 bfs를 돌려주었다.
*/
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>

using namespace std;

struct Pair {
   int ypos, xpos;
};

int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
int ar[55][55], N, L, R, ans;
int check[55][55];

bool dfs(int ypos, int xpos, int idx) {
   bool flag = false;

   for (int i = 0; i < 4; i++) {
      int ny = ypos + dy[i], nx = xpos + dx[i];
      if (ny < 0 || nx < 0 || nx >= N || ny >= N || check[ny][nx])continue;
      int gap = abs(ar[ypos][xpos] - ar[ny][nx]);
      if (gap < L || gap > R)continue;
      flag = true;
      check[ny][nx] = idx;
      dfs(ny, nx, idx);
   }
   return flag;
}

void bfs() {
   queue<Pair> q;
   bool visited[55][55];
   memset(visited, false, sizeof(visited));

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         if (visited[i][j] || !check[i][j])continue;
         int sum = 0, idx = check[i][j];
         q.push({ i,j });
         visited[i][j] = true;
         vector<Pair> v;
         
         while (!q.empty()) {
            int ypos = q.front().ypos, xpos = q.front().xpos;
            q.pop();
            sum += ar[ypos][xpos];
            v.push_back({ ypos, xpos });

            for (int k = 0; k < 4; k++) {
               int ny = ypos + dy[k], nx = xpos + dx[k];
               if (ny < 0 || nx < 0 || nx >= N || ny >= N || visited[ny][nx] || check[ny][nx] != idx)continue;
               visited[ny][nx] = true;
               q.push({ ny, nx });
            }
         }
         for (int k = 0; k < v.size(); k++) {
            ar[v[k].ypos][v[k].xpos] = sum / v.size();
         }
      }
   }
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> L >> R;
   ans = 0;
   
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         cin >> ar[i][j];
      }
   }
   
   while (true) {
      bool flag = false;
      memset(check, 0, sizeof(check));
      
      int idx = 1;

      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {            
            if (check[i][j])continue;
            if (dfs(i, j, idx)) {
               check[i][j] = idx++;
               flag = true;
            }
         }
      }
      if (!flag)break;
      bfs();
      ++ans;
   }

   cout << ans;

   return 0;
}