/*
cache[i][j] = (i,j)까지 봤을때 만들수 있는 최대수

행(Row)기준으로 A[i][j]는 (i,j)부터 (R,C)까지의 A누적합 B[i][j]는 (0,j)부터 (i,j)까지의 B누적합.

i와 j가 1일경우는 국경선이 경계에 걸쳐있기 때문에 예외처리를 해줘야한다.
(i-1,j -1) ( => 대각선방향)와 (i, j-1) ( => 옆방향)은 행을 기준으로 누적합을 갱신해줬기 때문에 A와 B모두 더해줘야한다.
(누적합인 A와 B의 값이 cache값에 영향을 미치지 않았다고 생각하면 편하다.)
그리고 누적합이 cache에 연관되어있는 (i-1,j)는 (i,j)가 A였을경우 그 개수만큼 빼줘야한다.
(cache[i-1][j]는 (i,j)가 A나라 땅이라고 계산했기 때문이라고 생각하면 편하다.)
*/
#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

int R, C, cache[1501][1501], A[1501][1501], B[1501][1501];

int max(int a, int b) { return a < b ? b : a; }

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C;

	string str;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> str;
			(str[0] == 'A' ? A[i][j] : B[i][j]) += atoi(str.substr(1).c_str());
		}
	}

	for (int i = 1; i <= C; i++) {
		for (int j = 1; j <= R; j++) {
			B[j][i] += B[j - 1][i];
			A[R - j + 1][i] += A[R - j + 2][i];
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (i == 1 || j == 1) {
				cache[i][j] = cache[i][j - 1] + A[i + 1][j];
				continue;
			}

			cache[i][j] = max(cache[i][j - 1], cache[i - 1][j - 1]) + A[i + 1][j] + B[i - 1][j];
			cache[i][j] = max(cache[i][j], cache[i - 1][j] - A[i][j] + A[i + 1][j]);
		}
	}

	cout << cache[R][C];
	return 0;
}