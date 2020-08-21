/*
위상정렬예제
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int node, cost;
};

int N, indegree[501], cost[501], dist[501];
vector<int> adj[501];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	int node;
	for (int i = 1; i <= N; i++) {
		cin >> cost[i];
		
		while (cin >> node) {
			if (node == -1)break;
			adj[node].push_back(i);
			indegree[i]++;
		}		
	}

	queue<int> q;
	for (int i = 1; i <= N; i++)if (!indegree[i])q.push(i), dist[i] += cost[i];

	for (int i = 0; i < N; i++) {
		int node = q.front();
		q.pop();

		for (int next : adj[node]) {
			dist[next] = max(dist[next], dist[node] + cost[next]);
			if (!(--indegree[next]))q.push(next);
		}
	}

	for (int i = 1; i <= N; i++)cout << dist[i] << "\n";
	return 0;
}