/*
오답이유
MST를 구성하던 도중 Union을 해줄때 parent[edge[i].node2] = edge[i].node1이라고함.
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

struct Edge {
	int node1, node2;
	double cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

struct Pos {
	double x, y;
};

int N, parent[101];
Edge edge[5000];
Pos pos[101];


double getDist(Pos pos1, Pos pos2) { return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)); }

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	double x, y;
	for (int i = 0; i < N; i++) cin >> pos[i].x >> pos[i].y;

	int idx = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			edge[idx++] = { i,j, getDist(pos[i], pos[j]) };
		}
	}

	memset(parent, -1, sizeof(parent));
	sort(edge, edge + idx);

	double ans = 0;
	int cnt = 0;
	for (int i = 0; i < idx; i++) {
		int pa = find(edge[i].node1);
		int pb = find(edge[i].node2);

		if (pa != pb) {
			parent[pb] = pa;
			ans += edge[i].cost;
			++cnt;
			if (cnt == N - 1)break;
		}
	}

	cout << ans;
	return 0;
}