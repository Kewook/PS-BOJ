/*
N의 크기가 50으로 매우 작으니 그에 비교할 수 있는 가중치를 부여 할 수 있다. (사실상 g와 g와 인접한칸, 그냥 '.'칸 지나는 3가지 경우밖에 없기 때문에)

문제에서 볼수 있다시피 최소경로를 정의하자면 g를 최대한 지나지 않는 것이고 만약 g를 지나야 한다면 그 인접한 칸을 최소한으로 지나야 한다고 한다.
따라서 g를 지나는 노드에 가중치를 최대한으로 2500을 준다.(g에 인접하지 않는 칸이나 g에 인접한 칸을 모두 지나고 우회하여 최소값이 바뀌는 경우 방지)
또한 g의 인접한 칸에는 1의 가중치를 부여하고 '.'의 칸에는 가중치 1을 부여한다.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int ypos, xpos, cost;

	bool operator < (const Edge &ipt) const {
		return cost > ipt.cost;
	}
};

const int INF = 2500 * 2500 + 1;

int N, M, sy, sx, ey, ex, dist[51][51], cost[51][51];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
char map[51][51];
bool check[51][51];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) cin >> map[i][j];
	}

    //인접행렬로 모든 노드와 간선을 만들 필요는 없다. 노드 자체에 있는 cost를 비교하면 된다.
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			dist[i][j] = INF;
			
			if (map[i][j] == 'S')sy = i, sx = j;
			else if (map[i][j] == 'F')ey = i, ex = j;
			else if (map[i][j] == 'g') {
				cost[i][j] = 2500;
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k], nx = j + dx[k];
					if (ny < 1 || nx < 1 || ny > N || nx > M)continue;
					if (map[ny][nx] == '.')cost[ny][nx] = 1;
				}
			}
		}
		
	}
	
	priority_queue<Edge> pq;
	pq.push(Edge { sy, sx, 0 });
	dist[sy][sx] = 0;

	while (!pq.empty()) {
		int ypos = pq.top().ypos, xpos = pq.top().xpos, c = pq.top().cost;
		pq.pop();

		if (check[ypos][xpos])continue;
		check[ypos][xpos] = true;

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 1 || nx < 1 || ny > N || nx > M)continue;
			if (dist[ny][nx] > c + cost[ny][nx]) {
				dist[ny][nx] = c + cost[ny][nx];
				pq.push(Edge { ny , nx, dist[ny][nx] });
			}
		}
	}
    
	cout << dist[ey][ex] / 2500 << " " << dist[ey][ex] % 2500;	
	return 0;
}