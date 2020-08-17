/*
모든정점 중, 임의의 정점에서 모든 정점으로 가는 경로를 확인해야하고 갈수 없는지 있는지도 판단해야 한다. 게다가 N이 100이니 O(N^3)의 시간복잡도인 플로이드-와샬을 사용하면 된다.

단방향 그래프를 구성하고 플로이드 알고리즘을 사용하면 되는데 경로의 유무만 판단하면 되므로 처음에 입력한 간선 말고도 cache[i][k] && cache[k][j]인 i->j로 갈때 k를 통한 우회도로가 있는지만 확인하면 된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, M, cache[101][101];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cache[a][b] = 1;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (cache[i][k] && cache[k][j])cache[i][j] = 1;
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		int cnt = 0;
		for (int j = 1; j <= N; j++) {
			if (!cache[i][j] && !cache[j][i])++cnt;
		}
		cout << cnt - 1<< "\n";
	}

	return 0;
}