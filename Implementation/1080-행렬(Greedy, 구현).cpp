#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>

using namespace std;

int N, M;
bool A[51][51], check[51][51];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int diff = 0;
	char c;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> c;
			A[i][j] = c - '0';
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> c;
			c -= '0';
			if (A[i][j] != c) {
				check[i][j] = 1;
				++diff;
			}
		}
	}

	if (!diff) {
		cout << 0;
		return 0;
	}

    //이 부분이 !diff 뒤에 가야한다.
    //Intput
    //1 1
    //1
    //1
    //
    //Output
    //0
	if (N < 3 || M < 3) {
		cout << -1;
		return 0;
	}
	int ans = 0;
	for (int i = 0; i <= N - 3; i++) {
		for (int j = 0; j <= M - 3; j++) {
			if (i == N - 3 && !(check[i][j] == check[i + 1][j] && check[i][j] == check[i + 2][j])) {
				cout << -1;
				return 0;
			}
			if (j == M - 3 && !(check[i][j] == check[i][j + 1] && check[i][j] == check[i][j + 2])) {
				cout << -1;
				return 0;
			}

			if (check[i][j]) {
				++ans;
				for (int y = i; y < i + 3; y++) {
					for (int x = j; x < j + 3; x++) {
						check[y][x] = !check[y][x];
					}
				}
			}
		}
	}

	for (int i = N - 1; i > N - 3; i--) {
		for (int j = M - 1; j > M - 3; j--)if (check[N - 3][M - 3] != check[i][j]) {
			cout << -1;
			return 0;
		}
	}

	cout << ans;

	return 0;
}