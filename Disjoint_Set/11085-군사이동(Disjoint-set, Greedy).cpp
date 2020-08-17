/*
문제이해가 잘 되지 않았다. B ---> C로 가는 경로중에서 최소값이 최대가 되게 하려면 그리디적인 방법이 필요하다.
그리디적인 방법을 이용하고 disjoint-set을 이용해서 B와 C가 같은 그룹일시 return하면 된다.
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt){
		return cost > ipt.cost;
	}
};

int N, E, B, C, parent[1001];
vector<Edge> edge;

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> E >> B >> C;

	int u, v, cost;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> cost;
		edge.push_back({ u, v, cost });
	}

	sort(edge.begin(), edge.end());
	for (int i = 0; i < N; i++)parent[i] = i;
	
	int mincost;
	for (Edge e : edge) {
		int node1 = e.node1, node2 = e.node2;
		node1 = find(node1);
		node2 = find(node2);

		if (node1 != node2) parent[node2] = parent[node1];
		if (find(B) == find(C)) {
			mincost = e.cost;
			break;
		}
	}
	
	cout << mincost;
	return 0;
}