/*
시간초과 났음. 1500이라는 크기가 check배열을 계속 초기화하게 해야 되기때문에 굉장히 오버헤드가 크다.
처음에는 얼음이 있는 자리를 BFS로 돌며 몇이 뒤에 녹을지 미리 다 전처리 한뒤에 day를 아주 큰 수로 주어 이분탐색으로 탐색속도를 줄이려고 함.
그래도 시간초과 

해결방안
1. check배열을 자꾸 초기화 하지 않아도 된다 -> 백조한마리를 가지고 돌릴때 지나온자리는 어차피 다음에도 계속 갈수 있으니까 초기화 하지 않고 관리
   -> 다만 여기서 문제가 발생하는점이 내일 녹는 점을 체크를 해주어야 하는데 이 과정에서 내일 녹는 얼음들을 nextQ에 저장하고 q에 들어있는 좌표 탐색후 옮겨준다.

2. waterQ를 하나 관리해주어 백조가 지나간 구간이 아닌 다른 물이 있는 구간도 탐색해주어야 한다. 이때 녹은부분은 다시 넣어주기 위해 size를 고정한뒤에 줄여준다.
*/
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

struct Pos {
   int ypos, xpos;
};

int R, C;
char map[1505][1505];
bool check[1505][1505];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
vector<Pos> swan;
queue<Pos> q, waterQ;

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);
   
   cin >> R >> C;

   for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
         cin >> map[i][j];
         if (map[i][j] == 'L')swan.push_back({ i,j });
         if (map[i][j] != 'X')waterQ.push({ i,j });
      }
   }
   

   int day = 0;
   while (true) {
        //다음에 녹을 얼음의 좌표를 미리 저장하는 큐
        //날이 지날때마다 초기화 해줘야하므로 지역변수로 관리
      queue<Pos> nextQ;
      
      q.push(swan[0]);
      check[swan[0].ypos][swan[0].xpos] = true;

      while (!q.empty()) {
         int ypos = q.front().ypos, xpos = q.front().xpos;
         q.pop();

         for (int k = 0; k < 4; k++) {
            int ny = ypos + dy[k], nx = xpos + dx[k];
            if (ny < 0 || nx < 0 || ny >= R || nx >= C || check[ny][nx])continue;

            check[ny][nx] = true;
            if (ny == swan[1].ypos && nx == swan[1].xpos) {
               cout << day;
               return 0;
            }
            if (map[ny][nx] == 'X')nextQ.push({ ny, nx });
            else q.push({ ny , nx });
         }
      }
      //옮겨줌.
      q = nextQ;

      //백조가 있는 구간 말고도 다른 물 구간의 인접한 얼음이 녹는다.
      int size = waterQ.size();
      while (size--) {
         int ypos = waterQ.front().ypos, xpos = waterQ.front().xpos;
         waterQ.pop();

         for (int k = 0; k < 4; k++) {
            int ny = ypos + dy[k], nx = xpos + dx[k];
            if (ny < 0 || nx < 0 || ny >= R || nx >= C)continue;
            if (map[ny][nx] == 'X') {
               map[ny][nx] = '.';
               waterQ.push({ ny , nx });
            }
         }
      }
      ++day;
   }
   
   cout << day;

   return 0;
}