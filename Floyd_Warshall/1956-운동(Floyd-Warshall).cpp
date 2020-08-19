/*
플로이드 와샬 알고리즘을 사용하면 모든 정점에서부터 모든 정점의 최단거리가 구해진다.
cache[i][j] : i~j의 최단경로

보통 플로이드 와샬 문제를 풀 때 input값이 같은 정점의 간선이 주어지지 않기때문에 cache[i][i]는 0으로 초기화하게 된다.
cache[i][j] = min(cache[i][j], cache[i][k] + cache[k][i])에서 i,j가 2고 k가 3인 상황에서 2 <---> 3 양방향 간선이 있는 예를보자
보통은 같은 정점의 cache를 0으로 초기화 하기 때문에 2-3 사이에 양방향 간선이 있음에도 불과하고 거리가 갱신되지 않는다.

하지만 이 문제에서는 출발지 i에서 출발해 i로 돌아오는 최단 사이클을 요구하고 있다.
cache[i][i]도 똑같이 INF값으로 초기화하고 플로이드 와샬 알고리즘을 수행했을 시 최단 사이클의 비용을 구할 수 있다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int INF = 400 * 10000;
int V, E, cache[401][401];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	int a, b, c;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		cache[a][b] = c;
	}

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			if (cache[i][j])continue;
			else cache[i][j] = INF;
		}
	}
	
	for (int k = 1; k <= V; k++) {
		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {
				cache[i][j] = min(cache[i][j], cache[i][k] + cache[k][j]);
			}
		}
	}

	int ans = INF;
	for (int i = 1; i <= V; i++)ans = min(ans, cache[i][i]);

	if (ans == INF)cout << -1;
	else cout << ans;

	return 0;
}