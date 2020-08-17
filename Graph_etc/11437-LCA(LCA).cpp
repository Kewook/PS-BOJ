/*
LCA 알고리즘
O(N)의 시간복잡도를 가진 알고리즘이다.

1. 트리를 구성해준다. 뒤에 나온값이 자식이라는 보장은 없으니 둘다 추가해준다.
2. dfs로 트리를 순회하면서 depth와 부모를 저장한다.
3. depth를 기준으로 부모값이 같을때까지 LCA를 탐색하며 depth가 다를경우 더 깊은 것을 낮은것에 맞춰준뒤에 수행한다.
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

int N, M, parent[50005], depth[50005];
vector<int> adj[50005];
bool check[50005];

void dfs(int node, int idx) {
	depth[node] = idx;

	for (int next : adj[node]) {
		if (depth[next] != -1)continue;
		parent[next] = node;
		dfs(next, idx + 1);
	}
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	memset(depth, -1, sizeof(depth));
	dfs(1, 0);
	
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		if (depth[a] != depth[b]) {
			if (depth[a] < depth[b])swap(a, b);
			while (depth[a] != depth[b]) a = parent[a];
		}

		while (a != b) {
			a = parent[a];
			b = parent[b];
		}
		cout << a << "\n";
	}

	return 0;
}