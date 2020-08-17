/*
11438-LCA2 문제에서
root ~ node까지의 cost 누적합을 구하여 거리를 계산해준다.
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

struct Edge {
	int node, cost;
};

int N, M, depth[400001], parent[100001][21], psum[400001];
vector<Edge> adj[400001];

void sol(int node, int cnt, int cost) {
	depth[node] = cnt;
	psum[node] = cost;
	
	for (Edge next : adj[node]) {
		if (parent[next.node][0] != -1)continue;
		parent[next.node][0] = node;
		sol(next.node, cnt + 1, cost + next.cost);
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
    
	int a, b, c;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}

	memset(parent, -1, sizeof(parent));
	parent[1][0] = 1;
	sol(1, 0, 0);

	for (int i = 0; i < 20; i++) {
		for (int j = 1; j <= N; j++) {
			parent[j][i + 1] = parent[parent[j][i]][i];
		}
	}
    
	cin >> M;
	while (M--) {
		cin >> a >> b;
		int ca = a, cb = b;

		if (depth[a] < depth[b])swap(a, b);
		int diff = depth[a] - depth[b];
		
		int idx = 0;
		while (diff) {
			if (diff % 2)a = parent[a][idx];
			idx++;
			diff >>= 1;
		}

		if (a != b) {
			for (int i = 20; i >= 0; i--) {
				if (parent[a][i] != -1 && parent[a][i] != parent[b][i]) {
					a = parent[a][i];
					b = parent[b][i];
				}
			}
			a = parent[a][0];
		}
		cout << psum[ca] - psum[a] + psum[cb] - psum[a] << "\n";
	}
	
	return 0;
}