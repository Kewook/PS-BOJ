/*
위상정렬을 수행하는 도중에 도착노드 W의 indegree가 0이 되면 종료하면 된다.

처음에 간과했던 부분은 queue를 Edge 구조체로 선언해서 cost를 더해가며 W의 최소시간만 비교해줬다.
=> W로 가기까지의 모든 노드의 최소시간을 알고있어야 한다

따라서 dist[]를 통해서 AC를 받을 수 있었다.
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

struct Edge{
	int node, cost;
};

int N, K, W, time[1001], indegree[1001], dist[1001];
vector<int> adj[1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		cin >> N >> K;

		for (int i = 1; i <= N; i++)adj[i].clear();
		memset(indegree, 0, sizeof(indegree));

		for (int i = 1; i <= N; i++)cin >> time[i];

		int a, b;
		for (int i = 0; i < K; i++) {
			cin >> a >> b;
			adj[a].push_back(b);
			indegree[b]++;
		}
		cin >> W;

		queue<int> q;
		for (int i = 1; i <= N; i++) {
			if (!indegree[i])q.push(i);
			dist[i] = time[i];
		}

		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node == W)break;

			for (int next : adj[node]) {
				if (--indegree[next] == 0)q.push(next);
				if (dist[next] < dist[node] + time[next])dist[next] = dist[node] + time[next];
			}
		}
		cout << dist[W] << "\n";
	}
	return 0;
}