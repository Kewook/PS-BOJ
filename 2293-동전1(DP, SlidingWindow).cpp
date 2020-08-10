/*
동전문제

처음에는 Top-down방식으로 접근했으니 메모리 초과 발생. 따라서 dp배열을 1차원으로 줄이고 bottom-up방식으로 해결했다.
*/
#include<iostream>

using namespace std;

int N, K, coin, dp[100001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	
	dp[0] = 1;
	for (int i = 0; i < N; i++) {
		cin >> coin;
		for (int j = coin; j <= K; j++) {
            //dp[j] = 아무것도 추가하지 않은것 + 이전 상태에서 이번코인 추가한것.
			dp[j] = dp[j] + dp[j - coin];
		}
	}
	cout << dp[K];
	return 0;
}