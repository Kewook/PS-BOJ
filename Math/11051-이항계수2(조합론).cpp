#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int cache[1001][1001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int Max = max(N, M);

	for (int i = 0; i <= Max; i++) cache[i][0] = cache[i][i] = 1;
	for (int i = 0; i <= Max; i++) {
		for (int j = 1; j < i; j++) {
			cache[i][j] = (cache[i - 1][j - 1] + cache[i - 1][j]) % 10007;
		}
	}

	cout << cache[N][M];
	return 0;
}