/*
MST 기본예제
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

int V, E, parent[10001];
vector<Edge> edge;

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	int a, b, c;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		edge.push_back({ a, b, c });
	}
	
	memset(parent, -1, sizeof(parent));
	sort(edge.begin(), edge.end());

	int cost = 0, cnt = 0;
	for (auto e : edge) {
		int a = e.node1, b = e.node2;
		a = find(a);
		b = find(b);

		if (a != b) {
			parent[b] = a;
			cost += e.cost;
			if (++cnt == V - 1) break;
		}
	}

	cout << cost;
	return 0;
}