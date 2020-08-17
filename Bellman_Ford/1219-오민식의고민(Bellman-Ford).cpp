/*
처음에는 최단거리를 출력하는 문제라 생각했으나 다익스트라를 사용하기에는 수익이라는 음의 가중치때문에 다익스트라를 사용할 수 없다.
따라서 벨만포드 알고리즘을 사용해야 했으나 다른 블로그를 참조해서 풀이했다.
--> 보통 음의 돈이 존재하거나 돈을 무한하게 벌 수 있다라고 하면 벨만포드 알고리즘을 사용한다.

dist[node] : 시작점에서 node까지 왔을때 소지할 수 있는 돈의 최대값.
돈의 최대값 == 사용하는 비용의 최소값
따라서 수익을 음의가중치로 봐야한다.
하지만 최대 돈의 액수를 출력해야 하기 때문에 좀더 가독성을 높이기 위해 -INF로 dist를 초기화하고 dist를 비교할때 부등호를 반대로 풀었다.


보통 벨만 포드 알고리즘을 수행할 때, loop가 N번째 루프에 dist값이 수정이 된다면 음의 사이클이 존재한다는 것이다.
하지만 이 음의 사이클이 존재하긴 하지만 S-> E로 갈때 음의 사이클이 있는 지점을 밟지 않고 갈 수도 있는 점을 생각해보면 문제를 다른식으로 해결해야 한다.

따라서 음의 사이클이 존재할 때마다 그 정점을 저장하고 만약 그 음의 사이클이 존재하는 정점에서 출발하여 E로 갈 수 있으면 진짜 S->E로 가는 경로에 음의 사이클이 존재한다는 것이다.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const long long INF = 100000001;

struct Edge {
	int node, cost;
};

int N, M, S, E, revenue[101];
long long dist[101];
bool geeNode[101], check[101];
vector<Edge> adj[101];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> S >> E >> M;

	int a, b, cost;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> cost;
		adj[a].push_back({ b,cost });
	}

	for (int i = 0; i < N; i++) {
		cin >> revenue[i];
		dist[i] = -INF;
		//돈의 최대값이라고 보지않고 사용하는 비용의 최소값이라 생각하고 풀이하면 다음과 같다.
		//dist[i] = INF;
		//revenue *= -1;
	}

	dist[S] = revenue[S];
	for (int loop = 0; loop < N; loop++) {
        //flag : 한개도 수정된게 없으면 빠르게 끝내기 위함.
		bool flag = false;
		for (int i = 0; i < N; i++) {
			for (auto next : adj[i]) {
				if (dist[i] != -INF && dist[next.node] < dist[i] - next.cost + revenue[next.node]) {
				//if (dist[i] != INF && dist[next.node] > dist[i] + next.cost + revenue[next.node]) {
					//dist[next.node] = dist[i] + next.cost + revenue[next.node];
					dist[next.node] = dist[i] - next.cost + revenue[next.node];
					flag = true;
                    //음의사이클이 있는 노드번호를 모두 저장한다.
					if (loop == N - 1)geeNode[i] = true;
				}
			}
		}
		if (!flag)break;
	}

    //음의사이클에 관여하는 모든 노드에서 출발하여 도착노드에 도착할 수 있으면 S->E의 경로에 음의사이클이 존재한다는 것이 증명된다.
	queue<int> q;
	for (int i = 0; i < N; i++)if (geeNode[i])q.push(i);
	
	bool checkGee = false;
	while (!q.empty()) {
		int node = q.front();
		q.pop();

		if (node == E) {
			checkGee = true;
			break;
		}

		for (auto e : adj[node]) {
			if (check[e.node])continue;
			check[e.node] = true;
			q.push(e.node);
		}
	}
    
	if (dist[E] == -INF)cout << "gg";
	//if (dist[E] == INF)cout << "gg";
	else if (checkGee)cout << "Gee";
	else cout << dist[E];
	//else cout << -dist[E];

	return 0;
}