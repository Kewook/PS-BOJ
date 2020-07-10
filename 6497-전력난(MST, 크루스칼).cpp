/*
크루스칼 알고리즘을 사용한 MST 문제
*/

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

int M, N, parent[200001];
Edge edge[200001];

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

void Union(int a, int b) {
	a = find(a);
	b = find(b);
	if (a != b)parent[b] = a;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	while (true) {
		cin >> N >> M;
		if (M == 0 && N == 0)break;

		int x, y, z, sum = 0;
		for (int i = 0; i < M; i++) {
			cin >> edge[i].node1 >> edge[i].node2 >> edge[i].cost;	
			sum += edge[i].cost;
		}

		sort(edge, edge + M);

		memset(parent, -1, sizeof(parent));

		int ans = 0, cnt = 0;
		for (int i = 0; i < M; i++) {
			int pa = find(edge[i].node1);
			int pb = find(edge[i].node2);
			
			if (pa != pb) {
				Union(edge[i].node1, edge[i].node2);
				ans += edge[i].cost;
				++cnt;
				if (cnt == N - 1)break;
			}
		}
		cout << sum - ans << "\n";
	}
	
	return 0;
}