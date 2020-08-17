/*
메모리 제한이 극도로 작은 문제다.
따라서 DP + 슬라이딩윈도우 기법을 적용하면 된다.
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N, maxdp[2][3], mindp[2][3];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	int a, b, c;
	for (int i = 1; i <= N; i++) {
		cin >> a >> b >> c;
		maxdp[1][0] = a + max(maxdp[0][0], maxdp[0][1]);
		maxdp[1][1] = b + max(maxdp[0][0], max(maxdp[0][1], maxdp[0][2]));
		maxdp[1][2] = c + max(maxdp[0][1], maxdp[0][2]);

		mindp[1][0] = a + min(mindp[0][0], mindp[0][1]);
		mindp[1][1] = b + min(mindp[0][0], min(mindp[0][1], mindp[0][2]));
		mindp[1][2] = c + min(mindp[0][1], mindp[0][2]);

		for (int j = 0; j < 3; j++)maxdp[0][j] = maxdp[1][j], mindp[0][j] = mindp[1][j];
	}

	cout << max(maxdp[1][0], max(maxdp[1][1], maxdp[1][2])) << " " << min(mindp[1][0], min(mindp[1][1], mindp[1][2]));
	return 0;
}