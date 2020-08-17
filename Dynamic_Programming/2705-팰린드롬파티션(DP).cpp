/*
dp[N] : 합이 N인 재귀적인 팰린드롬 파티션의 개수
dp[N] = dp[(N-가운데수) / 2] ( 0 <= 가운데수 <= N)

dp[N]의 값은 1로 초기화 되어야함 : N자체가 재귀적인 팰린드롬 파티션이다.

예를들어 N이 7이라 할때 가운데수는 0~6이 될수있는데 0은 가운데수가 없는것을 뜻한다.
가운데수가 3일때 총 4의 합을 가진 팰린드롬 파티션을 절반인 2씩 옆에 둘수있다.

*/
#include<iostream>

using namespace std;

int dp[1001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 1; i <= 1000; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if ((i - j) % 2)continue;
			dp[i] += dp[(i - j) / 2];
		}
	}

	int T, N;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		cout << dp[N] << "\n";
	}

	return 0;
}