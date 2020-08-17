/*
1219-오민식의고민 과 매우 유사한문제
다만 경로를 출력하는게 다른 문제
*/
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int node, cost;
};

const int INF = 100 * 1000 + 1;
int N, M, path[101];
long long dist[101];
vector<Edge> adj[101];
bool cycle[101], check[101];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int u, v, w;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> w;
		adj[u].push_back({ v,-w });
	}
	
	for (int i = 1; i <= N; i++)dist[i] = INF;
	
	dist[1] = 0;
	for (int loop = 1; loop <= N; loop++) {
		bool flag = false;
		for (int i = 1; i <= N; i++) {
			for (Edge next : adj[i]) {
				if (dist[i] != INF && dist[next.node] > dist[i] + next.cost) {
					dist[next.node] = dist[i] + next.cost;
					path[next.node] = i;
					flag = true;
					if (loop == N)cycle[i] = true;
				}
			}
		}
		if (!flag)break;
	}

	
	queue<int> q;
	for (int i = 1; i <= N; i++)if (cycle[i])q.push(i);

	bool isCycle = false;
	while (!q.empty()) {
		int node = q.front();
		check[node] = true;
		q.pop();
		

		if (node == N) {
			isCycle = true;
			break;
		}
		
		for (Edge next : adj[node]) {
			if (check[next.node])continue;
			q.push(next.node);
		}
	}

	if (dist[N] == INF || isCycle)cout << -1;
	else {
		vector<int> ans;
		int node = N;
		
		while (node) {
			ans.push_back(node);
			node = path[node];
		}
		for (int i = ans.size() - 1; i >= 0; i--)cout << ans[i] << " ";
	}
	return 0;
}