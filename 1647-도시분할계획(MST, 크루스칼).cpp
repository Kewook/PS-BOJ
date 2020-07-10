/*
크루스칼 알고리즘을 사용하여 MST를 구성하면 된다.

마을을 두가지로 분류하는 MST를 두가지로 구분해야한다.
 ==>  최대가중치를 가지고 있는 집중에 하나를 다른 마을로 분류하면 된다.
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

int N, M, parent[100001];
Edge edge[1000001];

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
	
	cin >> N >> M;
	
	for (int i = 0; i < M; i++) cin >> edge[i].node1 >> edge[i].node2 >> edge[i].cost;

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
			if (cnt == N - 2)break;			
		}
	}
	cout << ans;
	
	
	return 0;
}