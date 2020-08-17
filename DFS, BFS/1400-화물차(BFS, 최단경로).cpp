/*
메모리 초과

ex)
4 7
#A#####
....#.#
####0##
#
####B..
0 - 10 2

- 한경로가 신호등을 지나가고 다른 경로에서 막혀있을경우 가정
- 조금만 기다려서 더 빠르게 갈수 있는데도 불구하고 다른경로가 지나가면 check == true가 되어서 못지나간다고 생각함
- 하지만 어찌됏건 교차로에 들어가면 모든 방향으로 갈 수 있으니 막혀있는 경로말고 돌아서 간 경로도 빠른 방향으로 갈 수 있다.
- 따라서 교차로의 check배열도 true로 바꿔줘야함
*/

#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Light {
   int status, time;
};

struct Pos {
   int ypos, xpos;
};

const int INF = 987654321;

char map[21][21];
int info[10][2], N, M;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[21][21];
Light light[10];

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   while (true) {
      cin >> N >> M;
      if (N == 0 && M == 0)break;


      int lsize = 0;
      queue<Pos> q;
      memset(check, false, sizeof(check));

      for (int i = 0; i < N; i++) {
         for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'A')q.push({ i,j }), check[i][j] = true;
            else if (map[i][j] >= '0' && map[i][j] <= '9')light[map[i][j] - '0'] = { i,j }, lsize++;
         }
      }
      
      for (int i = 0; i < lsize; i++) {
         char stat;
         int num, ai, bi;
         cin >> num >> stat >> ai >> bi;
         info[num][0] = ai, info[num][1] = bi;
         if (stat == '|')light[num].time = bi, light[num].status = 1;
         else light[num].time = ai, light[num].status = 0;
      }

      int ans = INF;
      int dist = 0;

      while (!q.empty()) {
         int qsize = q.size();
         ++dist;
         
         for (int i = 0; i < qsize; i++) {
            int ypos = q.front().ypos, xpos = q.front().xpos;
            q.pop();

            for (int k = 0; k < 4; k++) {
               int ny = ypos + dy[k], nx = xpos + dx[k];
               if (map[ny][nx] == 'B') ans = ans > (dist) ? (dist) : ans;
               if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
               if (check[ny][nx] || map[ny][nx] == '.')continue;
               if (map[ny][nx] >= '0' && map[ny][nx] <= '9') {
                  if (light[map[ny][nx] - '0'].status == 0) {
                     if (ypos == ny) {
                        q.push({ ny, nx });
                        check[ny][nx] = true;
                     }
                     else q.push({ ypos, xpos });
                  }
                  else if (light[map[ny][nx] - '0'].status == 1) {
                     if (xpos == nx) {
                        q.push({ ny, nx });
                        check[ny][nx] = true;
                     }
                     else q.push({ ypos, xpos });
                  }
               }
               else {
                  q.push({ ny, nx });
                  check[ny][nx] = true;
               }
            }

         }

         //신호 변경
         for (int k = 0; k < lsize; k++) {
            --light[k].time;
            if (light[k].time == 0) {
               int stat = light[k].status;
               stat = (stat + 1) % 2;
               light[k].time = info[k][stat];
               light[k].status = stat;
            }
         }
      }
      if (ans == INF)cout << "impossible\n";
      else cout << ans << "\n";

   }
   return 0;
}