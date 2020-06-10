#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct Info {
	int node, cost;

	bool operator < (const Info &ipt)const {
		return cost > ipt.cost;
	}
};

const int INF = 999 * 100 + 1;

int N, M, X, student[1001];
vector<Info> adj[1001];

void dijkstra(int s, int e) {
	int dist[1001];
	for (int i = 1; i <= N; i++)dist[i] = INF;
	
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
	
	if (s == X) for (int i = 1; i <= N; i++) student[i] += dist[i];
	else student[s] += dist[e];
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M >> X;
	
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
	}
	
	for (int i = 1; i <= N; i++) dijkstra(i, X);
	
	int maxSt = student[1];
	for (int i = 2; i <= N; i++)maxSt = maxSt < student[i] ? student[i] : maxSt;
	
	cout << maxSt;
	return 0;
}