/*
처음에는 1~2 2~3 3~4까지의 각각 최단거리를 더해주면 풀릴것이라 생각함.
하지만 다른 땅을 밟을 수 도 있고 우회하는 것을 생각하면 이렇게 풀면 오답.
따라서 원래 DFS처럼 풀어야한다.

다른 땅을 밟아도 되기때문에 check배열을 4차원 배열로 관리를 해준다.
hist[ypos][xpos][dst][mode]란 ypos, xpos땅을 밟은 mode상태의 말이 목적지가 dst일때 체크를 해줬는지에 대한 여부이다.
*/
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Info {
   int ypos, xpos, dst, mode;
};

// 0 : 나이트
// 1 : 비숍
// 2 : 룩

queue<Info> q;

int N, map[10][10];
bool hist[10][10][101][3];
int dy[3][8] = {
   {-1,-2,-2,-1,1,2,2,1},
   {-1,-1,1,1},
   {1,-1,0,0}
};
int dx[3][8] = {
   {2,1,-1,-2,-2,-1,1,2},
   {1,-1,-1,1},
   {0,0,1,-1}
};


int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N;
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         cin >> map[i][j];
         if (map[i][j] == 1) {
            for (int k = 0; k < 3; k++) {
               q.push({ i,j,2,k });
               hist[i][j][2][k] = true;
            }
         }
      }
   }

   int dist = 0;

   while (!q.empty()) {
      int qsize = q.size();

      for (int Q = 0; Q < qsize; Q++) {
         int ypos = q.front().ypos, xpos = q.front().xpos;
         int dst = q.front().dst, mode = q.front().mode;
         q.pop();

         if (dst == N * N + 1) {
            cout << dist;
            return 0;
         }
         //말 변경
         for (int i = 0; i < 3; i++) {
            if (i == mode)continue;
            if (hist[ypos][xpos][dst][i])continue;
            q.push({ ypos,xpos, dst, i });
            hist[ypos][xpos][dst][i] = true;
         }

         //나이트 이동
         if (mode == 0) {
            for (int i = 0; i < 8; i++) {
               int ny = ypos + dy[mode][i], nx = xpos + dx[mode][i];
               if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
               if (hist[ny][nx][dst][mode])continue;

               if (map[ny][nx] == dst) q.push({ ny, nx, dst + 1, mode });
               else q.push({ ny, nx, dst, mode });
               hist[ny][nx][dst][mode] = true;
            }
         }

         //비숍 이동
         else if (mode == 1) {
            for (int i = 0; i < 4; i++) {
               for (int offset = 1;; offset++) {
                  int ny = ypos + dy[mode][i] * offset, nx = xpos + dx[mode][i] * offset;
                  if (ny < 0 || nx < 0 || ny >= N || nx >= N)break;
                  if (hist[ny][nx][dst][mode])continue;

                  if (map[ny][nx] == dst) q.push({ ny, nx, dst + 1, mode });
                  else q.push({ ny, nx, dst, mode });
                  hist[ny][nx][dst][mode] = true;
               }
            }
         }

         //룩 이동
         else if (mode == 2) {
            for (int i = 0; i < 4; i++) {
               for (int offset = 1;; offset++) {
                  int ny = ypos + dy[mode][i] * offset, nx = xpos + dx[mode][i] * offset;
                  if (ny < 0 || nx < 0 || ny >= N || nx >= N)break;
                  if (hist[ny][nx][dst][mode])continue;

                  if (map[ny][nx] == dst) q.push({ ny, nx, dst + 1, mode });
                  else q.push({ ny, nx, dst, mode });
                  hist[ny][nx][dst][mode] = true;
               }
            }
         }
      }
      ++dist;
   }

   return 0;
}