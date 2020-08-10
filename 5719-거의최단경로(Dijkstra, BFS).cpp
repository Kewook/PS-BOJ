/*
1. 최단 경로를 찾아준다.
2. 그 최단경로를 역추적해서 root를 삭제한다.
3. 다시 최단경로를 찾아준다.

최단경로를 삭제해주어야하니 인접리스트보다는 행렬로 구성하는게 낫다.
또한 최단경로는 여러개일수 있으니 다익스트라 부분에서 부등호에 유의하자.
*/

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

struct Info {
	int node, cost;

	bool operator < (const Info &ipt) const {
		return cost > ipt.cost;
	}
};

const int INF = 499 * 10000 + 1;

int N, M, S, E;
int map[502][502], dist[502];
vector<int> trace[502];

void dijkstra() {
	priority_queue<Info> pq;
	
	pq.push({ S + 1, 0 });
	dist[S + 1] = 0;

	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		pq.pop();

		if (dist[node] < cost)continue;

		for (int next = 1; next <= N; next++) {
			//최단경로가 여러개일경우 >=로 해주어야함.
			if (map[node][next] != -1 && dist[next] >= dist[node] + map[node][next]) {
				dist[next] = dist[node] + map[node][next];
				trace[next].push_back(node);
				pq.push({ next, dist[next] });
			}
		}
	}
}

void delRoot() {
	queue<int> q;
	q.push(E + 1);

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (int prev : trace[node]) {
			if (dist[node] == dist[prev] + map[prev][node]) {
				map[prev][node] = -1;
				q.push(prev);
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	while (true) {
		cin >> N >> M;
		if (N == 0 && M == 0)break;
		
		cin >> S >> E;
		
		//init
		memset(dist, -1, sizeof(dist));
		memset(map, -1, sizeof(map));
		for (int i = 1; i <= N; i++) trace[i].clear();
		
		int U, V, C;
		for (int i = 0; i < M; i++) {
			cin >> U >> V >> C;
			map[U + 1][V + 1] = C;
		}
		
		for (int i = 1; i <= N; i++)dist[i] = INF;
		dijkstra();
		delRoot();

		for (int i = 1; i <= N; i++)dist[i] = INF;
		dijkstra();

		if (dist[E + 1] == INF)cout << -1 << "\n";
		else cout << dist[E + 1] << "\n";
	}
	
	return 0;
}