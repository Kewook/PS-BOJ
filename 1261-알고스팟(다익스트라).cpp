/*
현재시점에서 인접한 방이 1이라면 비용이 1
단방향으로 구성해주어야한다.

틀린이유 1. node개수가 10000이지만 1000으로 잘못입력
틀린이유 2. (i,j)를 1번부터 시작하는 node 번호로 바꾸기 위해서 i*M+j+1이라고 해줘야함.
*/
#include<iostream>
#include<queue>
#include<vector>
#include<string>

using namespace std;

struct Info {
	int node, cost;
	
	bool operator < (const Info &ipt)const {
		return cost > ipt.cost;
	}
};

const int INF = 10000;

int N, M, map[101][101], dist[10001];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
vector<Info> adj[10001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> M >> N;

	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		for (int j = 0; j < M; j++) {
			map[i][j] = str[j] - '0';
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k], nx = j + dx[k];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;

				if (map[ny][nx])adj[i*M + j + 1].push_back({ ny*M + nx + 1, 1 });
				else adj[i*M + j + 1].push_back({ ny*M + nx + 1, 0 });
			}
		}
	}

	for (int i = 2; i <= N * M; i++)dist[i] = INF;

	priority_queue<Info> pq;
	pq.push({ 1,0 });
	dist[1] = 0;

	while (!pq.empty()) {
		int node = pq.top().node, cost = pq.top().cost;
		pq.pop();

		if (dist[node] < cost)continue;
		
		for (Info &iter : adj[node]) {
			int next = iter.node, ncost = iter.cost;
			if (dist[next] > dist[node] + ncost) {
				dist[next] = dist[node] + ncost;
				pq.push({ next, dist[next] });
			}
		}
	}

	cout << dist[N*M];
	return 0;
}