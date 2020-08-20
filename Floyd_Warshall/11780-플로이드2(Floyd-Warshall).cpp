/*
플로이드-와샬 기본문제 + 경로추적
*/
#include<iostream>

using namespace std;

const int INF = 10000001;
int N, M, cache[101][101], root[101][101];

//i와 j 사이에 있는 우회정점을 찾는것 중위순회와 비슷하다.
void findRoot(int i, int j) {
	if (root[i][j] != 0) {
		findRoot(i, root[i][j]);
		cout << root[i][j] << " ";
		findRoot(root[i][j], j);
	}
}

//i와 j 사이에 있는 우회정점의 수를 찾는것
int findCnt(int i, int j) {
	if (root[i][j] != 0) return 1 + findCnt(i, root[i][j]) + findCnt(root[i][j], j);
	else return 0;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) cache[i][j] = i == j ? 0 : INF;
	}

	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
        //여러개의 간선의 입력이 있을수 있다.
		cache[a][b] = cache[a][b] > c ? c : cache[a][b];
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (cache[i][j] > cache[i][k] + cache[k][j]) {
					cache[i][j] = cache[i][k] + cache[k][j];
					root[i][j] = k;
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) cout << cache[i][j] << " ";
		cout << "\n";
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j)cout << 0 << "\n";
			else {
                //기본으로 i, j 두개 있음
				cout << 2 + findCnt(i, j) << " ";
                //경로출력
				cout << i << " ";
				findRoot(i, j);
				cout << j << "\n";
			}
		}
	}
	return 0;
}