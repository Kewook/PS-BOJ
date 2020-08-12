/*
처음에는 발전소가 있는 건물들을 boolean배열로 node를 추가할때 부모가 발전소인경우 edge를 추가하지 않는 방식으로 했다 (WA).

발전소를 하나의 집합으로 묶어놓고 제출하니 AC를 받았다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

int N, M, K, parent[1001];
vector<Edge> edge;

int find(int a) {
    //부모가 -1이면 발전소다
	if (parent[a] == -1)return -1;
	else if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)parent[i] = i;
	
	int pos;
	for (int i = 0; i < K; i++)cin >> pos, parent[pos] = -1;
	
	int u, v, w;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> w;
		edge.push_back({ u,v,w });
	}

	sort(edge.begin(), edge.end());

	int cost = 0;
	for (auto e : edge) {
		int a = e.node1, b = e.node2;
		a = find(a);
		b = find(b);
        
		if (a == b)continue;
		else {
			if (a == -1)parent[b] = a;
			else parent[a] = b;
			cost += e.cost;
		}
	}

	cout << cost;
	return 0;
}