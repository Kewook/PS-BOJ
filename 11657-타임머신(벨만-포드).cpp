/*
(1) ----> (2) ----> (3) ......---->(500) ----> (1)
에서 cost가 모두 -10000일때 
첫번째 반복에서 dist는 다음과 같이 수정이 된다.
0 -10000 -20000 -30000 ....... -500000
dist는 계속 더해지다가 int표현범위인 -21억을 넘어간다.
따라서 dist가 양수로 변하게 되고 N번째 루프에서 걸리지 않고 그대로 출력을 한다.

결론 : dist를 long long으로 선언해야한다.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Info {
	int node, cost;
};

const int INF = 501*10000;

int N, M;
long long dist[505];
vector<Info> adj[505];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	int A, B, C;
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		adj[A].push_back({ B, C });
	}

	for (int i = 1; i <= N; i++)dist[i] = INF;

	dist[1] = 0;
	bool flag = false;
	
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N; j++) {
			for (Info info : adj[j]) {
				int next = info.node, cost = info.cost;
				if (dist[j] != INF && dist[next] > dist[j] + cost) {
					dist[next] = dist[j] + cost;
					if (i == N - 1) {
						flag = true;
						break;
					}
				}
			}
		}
	}
	
	if (flag) {
		cout << -1;
		return 0;
	}
	
	for (int i = 2; i <= N; i++) {
		if (dist[i] == INF)cout << -1 << "\n";
		else cout << dist[i] << "\n";
	}

	return 0;
}