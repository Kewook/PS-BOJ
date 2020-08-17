/*
단순한 다익스트라 문제지만 두 정점간 비용이 유일하다는 조건이 없다.
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 100000001;

struct Info {
	int node, cost;

	bool operator < (const Info &ipt) const {
		return cost > ipt.cost;
	}
};

int V, E, from, to, dist[1001], adj[1001][1001];
bool check[1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;
	
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			adj[i][j] = i == j ? 0 : INF;
		}
	}

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a][b] = adj[a][b] > c ? c : adj[a][b];
	}
	
	cin >> from >> to;

	for (int i = 1; i <= V; i++)dist[i] = INF;
	dist[from] = 0;

	priority_queue<Info> pq;
	pq.push({ from, 0 });

	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		if (check[node]) {
			pq.pop();
			continue;
		}
		pq.pop();
		if (check[node])break;
		check[node] = true;
		
		for (int i = 1; i <= V; i++) {
			if (i == node || adj[node][i] == INF)continue;
			if (dist[i] > dist[node] + adj[node][i]) {
				dist[i] = dist[node] + adj[node][i];
				pq.push({ i, dist[i] });
			}
		}
	}

	cout << dist[to];
	return 0;
}