#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Edge {
	int node1, node2;

	bool operator <(const Edge &ipt) const{
		if (node1 == ipt.node1)return node2 < ipt.node2;
		else return node1 < ipt.node1;
	}
};

int V, E, num, ans, order[100001];
vector<int> adj[100001];
vector<Edge> cut;

int dfs(int parent, int cur) {
	int ret = order[cur] = ++num;
	
	for (int next : adj[cur]) {
		if (next == parent)continue;
		if (order[next]) {
			ret = min(ret, order[next]);
			continue;
		}
		int prev = dfs(cur, next);
		ret = min(ret, prev);
		
        //cur node에서 "부모로 가는 간선 제외하고" 연결된 모든 간선을 통해 자식을 갔을 때 더 빠르게 갈 수 없으면 단절선이다.
        //부등호가 없음에 주의 : 단절점과 같은 예시로 만약 사이클이 있는경우 2-3-4-2 2번 노드 기준으로 검사를 한다면 4번이 2번이랑 연결되어있어 3과 4는 2를 return하게 된다.
        //등호가 있으면 단절선이라고 판단할텐데 이 선은 단절선이 아니다.
		if (prev > order[cur])cut.push_back({ min(next, cur), max(next, cur) });
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	int u, v;
	for (int i = 0; i < E; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 1; i <= V; i++)if (!order[i])dfs(0, i);
	
	sort(cut.begin(), cut.end());
	cout << cut.size() << "\n";
	for (auto e : cut) cout << e.node1 << " " << e.node2 << "\n";

	return 0;
}