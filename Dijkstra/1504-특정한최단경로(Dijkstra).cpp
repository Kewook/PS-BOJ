/*
1 ----> v1 -----> v2 -----> V( == N)
1 ----> v2 -----> v1 -----> V( == N)
이 경우만 체크해주면 된다.

따라서 위의 경우에서 나올 수 있는 출발점이 세가지인 경우만 체크해주면 된다.
1. 1에서 출발하는경우
2. v1에서 출발하는경우
3. v2에서 출발하는경우
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int INF = 799 * 1000 + 1;

struct Info {
	int node, cost;

	bool operator < (const Info &ipt) const {
		return cost > ipt.cost;
	}
};


int V, E, v1, v2;
vector<Info> adj[801];

vector<int> dijkstra(int s) {
	vector<int> dist;
	dist.resize(801);

	for (int i = 1; i <= V; i++)dist[i] = INF;
	
	priority_queue<Info> pq;
	pq.push({ s, 0 });
	dist[s] = 0;

	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		pq.pop();

		if (dist[node] < cost)continue;
		
		for (Info &info : adj[node]) {
			int next = info.node, ncost = info.cost;
			if (dist[next] > dist[node] + ncost) {
				dist[next] = dist[node] + ncost;
				pq.push({ next, dist[next] });
			}
		}
	}

	return dist;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	
	cin >> v1 >> v2;
	
	vector<int> s1 = dijkstra(1);
	vector<int> sv1 = dijkstra(v1);
	vector<int> sv2 = dijkstra(v2);

	int ans = min((s1[v1] + sv1[v2] + sv2[V]), (s1[v2] + sv2[v1] + sv1[V]));
	if (ans >= INF)cout << -1;
	else cout << ans;
	
	return 0;
}