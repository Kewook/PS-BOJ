/*
슈퍼컴퓨터에서부터 나머지 컴퓨터까지 거리를 모두 구해주고 그 최소시간의 경로를 trace 한다.
각 컴퓨터가 최소한의 시간을 가지게끔 모두 연결되어야 하니 최단경로에 관여한 모든 경로를 출력해준다.
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int node, cost;
	
	bool operator < (const Edge &ipt) const {
		return cost > ipt.cost;
	}
};

int N, M, dist[1001], trace[1001];
vector<Edge> adj[1001];
bool check[1001], checkE[1001][1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	
	memset(dist, 0x3f, sizeof dist);
	priority_queue<Edge> pq;
	pq.push({ 1,0 });
	dist[1] = 0;

	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		pq.pop();
		
		if (check[node])continue;
		check[node] = true;
		
		for (Edge next : adj[node]) {
			if (dist[next.node] > cost + next.cost) {
				dist[next.node] = cost + next.cost;
				pq.push({ next.node, cost + next.cost });
				trace[next.node] = node;
			}
		}
	}
	
	vector<pair<int, int>> ans;
	for (int i = 2; i <= N; i++) {
		int node = i;
		while (node != 1) {
			int prev = trace[node];
			if (!(checkE[prev][node] || checkE[node][prev])) {
				checkE[prev][node] = checkE[node][prev] = true;
				ans.push_back({ node, prev });
			}
			node = prev;
		}
	}

	cout << ans.size() << "\n";
	for (auto p : ans)cout << p.first << " " << p.second << "\n";

	return 0;
}