/*
LCA를 O(logN)의 시간복잡도로 구현하는 방법

깊이의 차이를 O(N)만큼 뛰는게 아니라 2^i만큼뛰어 O(logN)번만에 뛰는방식이다
parent[i][j] : i 노드의 2^j번째 부모노드
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

int N, M, parent[100005][20], depth[100005];
vector<int> adj[100005];

void dfs(int idx, int node) {
	depth[node] = idx;

	for (int next : adj[node]) {
		if (parent[next][0] != -1)continue;
		parent[next][0] = node;
		dfs(idx + 1, next);
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
	
	memset(parent, -1, sizeof(parent));

	parent[1][0] = 1;
	dfs(0, 1);

	//memoization
    //j의 2^i+1 번째 부모 == (j의 2^i번째부모)의 2^i번째 부모
    //j--------2^i번째부모---------2^i번째부모 == j의 2^i+1부모
    //bottop-up방식으로 i+1을 구하기 위해 임의의수에서 i번째는 이미 구해져있음
	for (int i = 0; i < 19; i++) {
		for (int j = 1; j <= N; j++) {
			parent[j][i + 1] = parent[parent[j][i]][i];
		}
	}

	cin >> M;
	while(M--){
		cin >> a >> b;
		if (depth[a] != depth[b]) {
			if (depth[a] < depth[b])swap(a, b);
			int diff = depth[a] - depth[b];

			int idx = 0;
            //2제곱수로 건너뛰어준다.
			while (diff) {
				if (diff % 2)a = parent[a][idx];
				diff >>= 1;
				++idx;
			}
		}

		if (a != b) {
			for (int i = 19; i >= 0; i--) {
                //-1이 된다는것은 범위밖이라는 뜻
				if (parent[a][i] != -1 && (parent[a][i] != parent[b][i])) {
					a = parent[a][i];
					b = parent[b][i];
				}
			}

			// a와 b의 부모가 같아졌으니 그 부모를 출력해야함.
			a = parent[a][0];
		}
		cout << a << "\n";
	}
	

	return 0;
}