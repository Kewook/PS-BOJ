/*
갱신이 될때 이전노드를 모두 저장해서 trace 할 수 있다.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

struct Edge {
	int node, cost;
	
	bool operator < (const Edge &ipt)const {
		return cost > ipt.cost;
	}
};

const int INF = 0x3f3f3f3f;
int N, M, dist[201], root[201];
bool check[201];
vector<Edge> adj[201];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}

	for (int s = 1; s <= N; s++) {
		memset(check, false, sizeof check);
		memset(dist, 0x3f, sizeof dist);
		priority_queue<Edge> pq;
		pq.push({ s, 0 });
		dist[s] = 0;
		
		while (!pq.empty()) {
			int node = pq.top().node, cost = pq.top().cost;
			pq.pop();

			if (check[node])continue;
			check[node] = true;

			for (Edge next : adj[node]) {
				if (dist[next.node] > cost + next.cost) {
					dist[next.node] = cost + next.cost;
					pq.push({ next.node, dist[next.node] });
					root[next.node] = node;
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			if (i == s)cout << "- ";
			else if (s == root[i])cout << i << " ";
			else {
                //s->i로 갈때 가장 먼저 들려야할 노드를 알아야 하니 root[cur]이 s일때까지 진행한다.
				int cur = i;
				while (root[cur] != s)cur = root[cur];
				cout << cur << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}