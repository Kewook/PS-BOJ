/*
위상정렬 예제

N번의 루프를 돌때 꺼내는값을 저장해야한다.
-> 만약 사이클이 생길 경우엔 0만 출력해야되기 때문.
*/
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

int N, M, indegree[1001];
vector<int> adj[1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int prev, node, K;
		cin >> K;
		if (K == 0)continue;

		cin >> prev;
		for (int i = 1; i < K; i++) {
			cin >> node;
			adj[prev].push_back(node);
			indegree[node]++;
			prev = node;
		}
	}

	queue<int> q;
	for (int i = 1; i <= N; i++)if (!indegree[i])q.push(i);
	
	int ans[1001];
	for (int i = 0; i < N; i++) {
		if (q.empty()) {
			cout << 0;
			return 0;
		}
		int node = q.front();
		q.pop();
		ans[i] = node;

		for (int next : adj[node]) {
			indegree[next]--;
			if (!indegree[next])q.push(next);
		}
	}

	for (int i = 0; i < N; i++)cout << ans[i] << "\n";


	return 0;
}