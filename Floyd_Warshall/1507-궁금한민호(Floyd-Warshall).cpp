/*
로직 자체가 떠오르질 않았다.

입력값은 어떤 경로에서 플로이드 알고리즘을 사용해서 모든 경로를 다 탐색하고 나온 결과라는걸 알 수 있다.
이러한 최솟값을 가지는 경로를 최소한의 경로만으로 구성하려면 플로이드 알고리즘을 다시 한 번 생각해보면 된다.

플로이드-와샬 알고리즘은 정점간 거쳐가는 모든 간선을 확인한다는 특성이 있다.
문제에서 모든 정점간 경로가 있다는 것은 i--->j로 가는데 i--->k--->j경로가 존재한다는 점이다.
따라서 만약에 dist[i][j]가 dist[i][k] + dist[k][j] (k는 임의의 정점)과 같다면 i->j는 k를 통해서 갈 수 있기 때문에 굳이 있을 필요가 없는 정점이다.

하지만 예외 케이스도 있다. 문제에서 갈 수 없는경우는 -1을 출력하라고 명시되어 있는데 이게 뜻하는것은 dist[i][j] > dist[i][k] + dist[k][j]일때를 뜻한다.
dist[i][j]는 이미 i->j 까지 가는 최단경로라고 결정되어있는데 k를 경유해서 더 빠르게 갈 수 있는 경로가 있다라는건 말이 안된다. 따라서 이럴땐 -1를 출력해주자.
*/
#include<iostream>

using namespace std;

int N, dist[21][21];
bool del[21][21];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)cin >> dist[i][j];
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == k || j == k)continue;
				if (dist[i][j] == dist[i][k] + dist[k][j])del[i][j] = true;
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					cout << -1;
					return 0;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!del[i][j])ans += dist[i][j];
		}
	}

    //위에서 i->j, j->i 경로를 두번씩 더해줬다.
	cout << ans / 2;
	return 0;
}