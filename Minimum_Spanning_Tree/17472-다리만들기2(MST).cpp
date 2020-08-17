/*
MST를 구성하는데 모든 부모가 1번섬으로 연결될것이라고 생각해서 parent[2 ~ node]이 1이 아니면 -1을 출력하는 식으로 진행함.
하지만 MST를 구성할 때 1번노드를 포함한 edge가 100이라하고 2~node까지를 포함한 edge들이 100보다 작으면 최상위 노드는 1이 아니게 된다.

따라서 Union부분에서 Uinon해줄때 index가 작은 노드가 부모가 되게끔 설정을 해준다.
->
if (x != y) {
      if (x < y)parent[y] = x;
      else parent[x] = y;
}
그리고 1번노드부터 find()함수를 통해 각각 최상위 노드를 직접 바라보게 만들어주어 MST가 구성되었을때 모든 노드의 parent는 1번 노드를 바라보게 만든다.
여기서 중요한점은 나는 보통 유니온파인드를 구성할때 parent배열을 초기화 할때 시간을 조금 줄이기 위해 memset으로 parent를 -1로 초기화 한다.
하지만 위 방법으로 MST를 구성하려면 parent는 각각 자기자신을 바라보게 해야한다.
->
for (int i = 0; i < node; i++)parent[i] = i;



그리고 구조체 operator, sort에서 cmp함수 좀 잘좀 하자.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>

#define INF 987654321

using namespace std;

struct Pair {
   int ypos, xpos;
};

struct Info {
   int node1, node2, cost;

   bool operator < (const Info &info) const {
      return cost < info.cost;
   }
};


vector<Pair> land[10];
Info dist[10];

int N, M, node, edge;
int ar[11][11], parent[11];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[11][11];


void findLand(int y, int x) {
   queue<Pair> q;
   q.push({ y,x });
   check[y][x] = true;

   while (!q.empty()) {
      int ypos = q.front().ypos, xpos = q.front().xpos;
      land[node].push_back({ ypos,xpos });
      q.pop();

      for (int i = 0; i < 4; i++) {
         int ny = ypos + dy[i], nx = xpos + dx[i];
         if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
         if (check[ny][nx] || !ar[ny][nx])continue;
         check[ny][nx] = true;
         q.push({ ny, nx });
      }
   }
   ++node;
}

int calcDist(int l1, int l2) {
   int distance = INF;
   for (Pair p1 : land[l1]) {
      for (Pair p2 : land[l2]) {
         int p1y = p1.ypos, p1x = p1.xpos, p2y = p2.ypos, p2x = p2.xpos;

         int temp = -1;
         if (p1y == p2y) {
            temp = 0;
            if (p1x > p2x)swap(p1x, p2x);
            for (int k = p1x + 1; k < p2x; k++) {
               if (ar[p1y][k]) {
                  temp = -1;
                  break;
               }
               temp++;
            }
         }
         else if (p1x == p2x) {
            temp = 0;
            if (p1y > p2y)swap(p1y, p2y);
            for (int k = p1y + 1; k < p2y; k++) {
               if (ar[k][p1x]) {
                  temp = -1;
                  break;
               }
               temp++;
            }
         }
         if (temp == -1 || temp == 1)continue;
         distance = distance > temp ? temp : distance;
      }
   }
   return distance;
}

int find(int x) {
   if (parent[x] == x)return x;
   else return parent[x] = find(parent[x]);
}

void Union(int x, int y) {
   x = find(x);
   y = find(y);
   if (x != y) {
      if (x < y)parent[y] = x;
      else parent[x] = y;
   }
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> N >> M;

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
         cin >> ar[i][j];
      }
   }

   node = 0;
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
         if (ar[i][j] && !check[i][j])findLand(i, j);
      }
   }

   edge = 0;
   for (int i = 0; i < node; i++) {
      for (int j = i + 1; j < node; j++) {
         int cost = calcDist(i, j);
         if (cost != INF && cost != 1) {
            dist[edge++] = { i, j, cost };
         }
      }
   }

   if (node - 1 > edge) {
      cout << -1;
      return 0;
   }

   for (int i = 0; i < node; i++)parent[i] = i;
   sort(dist, dist + edge);

   int ans = 0;
   int cnt = 0;
   for (int i = 0; i < edge; i++) {
      int a = dist[i].node1, b = dist[i].node2, cost = dist[i].cost;
      int pa = find(a);
      int pb = find(b);

      if (pa != pb) {
         Union(a, b);
         ans += cost;
         ++cnt;
         if (cnt == node)break;
      }
   }

   for (int i = 1; i < node; i++) find(i);
   for (int i = 1; i < node; i++) {
      if (parent[i]) {
         cout << -1;
         return 0;
      }
   }

   cout << ans;

   return 0;
}