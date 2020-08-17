/*
단방향 그래프이며 정점간 방향이 같은 간선은 유일하다는 점을 주목.

1~N(X제외) -> X로 가는 최단경로 + X-> (1~N)으로 가는 최단경로를 더해주면 된다.
따라서 인접행렬과 dist를 두가지로 구성하여 다익스트라 알고리즘을 두번 수행해주면 된다.
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Info {
	int node, cost;

	bool operator < (const Info &ipt)const {
		return cost > ipt.cost;
	}
};

const int INF = 999 * 100 + 1;

int N, M, X, student[1001], dist[2][1001];
vector<Info> adj[2][1001];

void dijkstra(int mode) {	
	priority_queue<Info> pq;
	pq.push({ X, 0 });
	
	dist[mode][X] = 0;
	
	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		pq.pop();

		if (dist[mode][node] < cost)continue;
		
		for (Info &info : adj[mode][node]) {
			int next = info.node, ncost = info.cost;
			if (dist[mode][next] > dist[mode][node] + ncost) {
				dist[mode][next] = dist[mode][node] + ncost;
				pq.push({ next, dist[mode][next] });
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M >> X;
	
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[0][a].push_back({ b,c });
		adj[1][b].push_back({ a,c });
	}

	for (int i = 1; i <= N; i++)dist[0][i] = dist[1][i] = INF;

	dijkstra(0);
	dijkstra(1);
	
	int ans = dist[0][1] + dist[1][1];
	for (int i = 2; i <= N; i++)ans = ans < dist[0][i] + dist[1][i] ? dist[0][i] + dist[1][i] : ans;

	cout << ans;
	return 0;
}