/*
문제 조건에 테두리 부분은 무조건 벽 즉'#'이라는 말이 없었다.
처음엔 bfs부분에 범위가 넘어가는 부분을 체크하지 않아서 런타임오류가 났음
*/

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

#define INF 987654321

using namespace std;

struct Info {
   int ypos, xpos;
};

Info node[10];
int N, M, adj[10][10], num, ans;
char map[55][55];

int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[55][55], visited[10];

void dfs(int idx, int prev, int dist) {
   if (idx >= num - 1) {
      int flag = true;
      for (int i = 1; i < num - 1; i++)if (!visited[i])flag = false;

      if (flag) {
         dist += adj[prev][num - 1];
         ans = ans > dist ? dist : ans;
      }
      return;
   }

   for (int i = 1; i < num; i++) {
      if (visited[i])continue;
      visited[i] = true;
      dfs(idx + 1, i, dist + adj[prev][i]);
      visited[i] = false;
      dfs(idx + 1, prev, dist);
   }
}

int bfs(int s, int t) {
   queue<Info> q;
   q.push(node[s]);
   check[node[s].ypos][node[s].xpos] = true;
   int dist = 1;
   bool flag = false;

   while (!q.empty()) {
      int size = q.size();

      for (int i = 0; i < size; i++) {
         int ypos = q.front().ypos, xpos = q.front().xpos;
         q.pop();

         for (int k = 0; k < 4; k++) {
            int ny = ypos + dy[k], nx = xpos + dx[k];
            if (ny < 0 || nx < 0 || ny >= M || nx >= N)continue;
            if (check[ny][nx] || map[ny][nx] == '#')continue;
            if (ny == node[t].ypos && nx == node[t].xpos) {
               flag = true;
               break;
            }
            check[ny][nx] = true;
            q.push({ ny, nx });
         }

         if (flag) {
            return dist;
         }
      }
      ++dist;
   }
   if (!flag)return 0;
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> M;

   num = 1;
   ans = INF;

   int Eypos, Expos;
   for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
         cin >> map[i][j];
         if (map[i][j] == 'S')node[0] = { i,j };
         else if (map[i][j] == 'X')node[num++] = { i,j };
         else if (map[i][j] == 'E') {
            Eypos = i, Expos = j;
         }
      }
   }
   node[num++] = { Eypos, Expos };

   for (int i = 0; i < num; i++) {
      for (int j = i + 1; j < num; j++) {
         memset(check, false, sizeof(check));
         adj[i][j] = adj[j][i] = bfs(i, j);
      }
   }

   if (num == 2)cout << adj[0][1];
   else {
      dfs(1, 0, 0);
      cout << ans;
   }


   return 0;
}