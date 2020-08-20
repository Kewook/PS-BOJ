/*
오르막길을 내려갈 순 없다. 따라서 그냥 오르막을 cost = 1로 생각해주고 kruskal 알고리즘을 사용하면 된다.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt)const {
		return cost < ipt.cost;
	}
};

int N, M, parent[1001];
vector<Edge> edge;

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

int kruskal(int s, int dir) {
	memset(parent, -1, sizeof parent);
	parent[1] = 0;

	int cost = edge[0].cost, cnt = 0;
	while(true) {
		Edge e = edge[s];
		int pa = find(e.node1);
		int pb = find(e.node2);
		if (pa != pb) {
			parent[pb] = pa;
			cost += e.cost;
			if (++cnt == N - 1)break;
		}
		s += dir;
	}
	return cost;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int a, b, c;
	for (int i = 0; i < M + 1; i++) {
		cin >> a >> b >> c;
		edge.push_back({ a,b,(c + 1) % 2 });
	}
	sort(edge.begin() + 1, edge.end());
	
	int minCost = kruskal(1, 1);
	int maxCost = kruskal(edge.size() - 1, -1);
	
	cout << maxCost * maxCost - minCost * minCost;
	return 0;
}