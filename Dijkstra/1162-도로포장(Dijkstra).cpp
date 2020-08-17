/*
도로를 포장할 수 있는지 없는지 큐에 추가해주면서 다익스트라 알고리즘을 돌리면 된다.

while(큐가 비어있을때까지){
    if(cnt > 0)포장해서 가는방법
    그냥 포장하지 않고 가는방법
}
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

struct Edge {
	int node;
	long long cost;
	int cnt;

	bool operator < (const Edge &ipt) const {
		return cost > ipt.cost;
	}
};

int N, M, K;
vector<Edge> adj[10001];
long long dist[10001][21];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	int a, b;
	long long w;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		adj[a].push_back({ b,w });
		adj[b].push_back({ a,w });
	}

	memset(dist, 0x3f, sizeof(dist));
	priority_queue<Edge> pq;
	pq.push({ 1, 0, K });
	dist[1][K] = 0;

	while (!pq.empty()) {
		int node = pq.top().node, cnt = pq.top().cnt;
		long long cost = pq.top().cost;
		pq.pop();

		if (dist[node][cnt] < cost)continue;

		for (auto next : adj[node]) {
			if (cnt && dist[next.node][cnt - 1] > cost) {
				dist[next.node][cnt - 1] = cost;
				pq.push({ next.node, dist[next.node][cnt - 1], cnt - 1 });
			}
			if (dist[next.node][cnt] > dist[node][cnt] + next.cost) {
				dist[next.node][cnt] = dist[node][cnt] + next.cost;
				pq.push({ next.node, dist[next.node][cnt], cnt});
			}
		}

	}
	
    //처음에 ans를 10000*1000000 +1로 초기화해서 틀렸다. (long long)10000*1000000+1로 형변환을 해주어야 정확한 값이 들어간다
	//long long ans = (long long)10000*1000000 +1;
	long long ans = 1e18;
	for (int i = 0; i <= K; i++)ans = min(ans, dist[N][i]);
	cout << ans;
	return 0;
}