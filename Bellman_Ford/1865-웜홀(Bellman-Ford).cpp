/*
이 문제에는 약간의 오해의 소지가 많아보인다.

벨만포드 알고리즘은 한개의 출발점에 대해서 모든 각 노드의 최단경로를 찾는 알고리즘이다.
음의 가중치가 있어도 알고리즘을 수행할 수 있다는 조건하에 dist를 갱신해줄때 dist[next] > dist[j] + cost;를 이용해서 갱신을 해주게 되는데
만약 j노드가 단절이 되어있는경우(돌아서 INF에서 갱신이 되지 않아있는 상태)에는 next로 이어져있는 간선이 있어도 갈수 없는 상황이기 때문에 dist를 갱신해주면 안된다.
따라서 dist[j] != INF일때만 갱신을 해준다.

하지만 이 문제는 임의의 정점 (1~N) 출발점 중에서 다시 출발점으로 돌아왔을때 사이클이 생기는지에 대해 판단하고 있다.
그렇기 때문에 dist와 INF를 비교하는 조건을 제거하면 AC를 받을 수 있는데
이 이유는 어느 출발점에서는 갱신이 되지만 어느 출발점에서는 갱신이 안되는 상황이 생기기 때문에 모든 정점에 대해 사이클이 있는지 없는지를 판단할수 없다.
마지막 N번째 반복에서 dist가 수정이 되는지만 확인하면 사이클을 판단할 수 있게 된다.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

#define INF 50000000

using namespace std;

struct Edge {
	int node, cost;
};

int N, M, W;
long long dist[501];
vector<Edge> adj[501];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	while (T--) {
		//init
		for (int i = 0; i < 501; i++)adj[i].clear();
		memset(dist, -1, sizeof(dist));
		
		cin >> N >> M >> W;
		
		int s, e, t;
		for (int i = 0; i < M; i++) {
			cin >> s >> e >> t;
			adj[s].push_back({ e,t });
			adj[e].push_back({ s,t });
		}

		for (int i = 0; i < W; i++) {
			cin >> s >> e >> t;
			adj[s].push_back({ e, -t });
		}

		dist[1] = 0;
		
		bool flag = true;
		for (int i = 0; i < N; i++) {
			for (int j = 1; j <= N; j++) {
				
				for (auto next : adj[j]) {
					if (dist[next.node] > dist[j] + next.cost) {
						dist[next.node] = dist[j] + next.cost;
						if (i == N - 1) {
							flag = false;
							break;
						}
					}
				}
			}
		}

		if (flag)cout << "NO\n";
		else cout << "YES\n";
	}

	return 0;
}