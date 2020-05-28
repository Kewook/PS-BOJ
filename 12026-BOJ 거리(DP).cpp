/*
맞았어도 한번 다시 봐보자.
BOJ 숫자로 구현, bottom-up으로 N^2으로 품.
*/
#include<iostream>

#define INF 987654321

using namespace std;

int ar[1001];
int N, dp[1001];

int min(int a, int b) { return a > b ? b : a; }

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		char c;
		cin >> c;

		switch (c) {
		case 'B':ar[i] = 2; break;
		case 'O':ar[i] = 1; break;
		case 'J':ar[i] = 0; break;
		}
		dp[i] = INF;
	}

	dp[0] = 0;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if ((ar[i] + 1) % 3 == ar[j] && dp[j] != INF) {
				dp[i] = min(dp[j] + (i - j)*(i - j), dp[i]);
			}
		}
	}

	if (dp[N - 1] == INF)cout << -1;
	else cout << dp[N - 1];

	return 0;
}