/*
dp[K][N] == K개 수를 골라서 합이 N을 만들수 있는 경우의 수
처음에는 0~20이라는 수가 있다고 가정하고 숫자 하나하나에 집중해서 풀려했다

숫자 하나하나에 집중하기 보다는 N이 합이라는 점에 주의해서 풀면 편하다.
K개 수를 골라서 N을 만들수 있다면 K-1개를 골랐을때(이 전의 상황을 고려한 것) K-1개 골랐던 경우와 K개 골랐던 경우는 숫자 한개밖에 차이나지 않는다.
따라서 dp[K][N]은 dp[K-1][N-임의의수]로 구할 수 있는데 임의의수는 N보다 클수 없다. 따라서 N이하의 모든 임의의수에 대해서 경우의 수를 더해준다.
*/

#include<iostream>

using namespace std;

const long long MOD = 1000000000;
long long dp[201][201];
int N, K;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> K;

	for (int i = 0; i <= N; i++)dp[1][i] = 1;
	
	for (int i = 1; i <= K; i++) {
		for (int j = 0; j <= N; j++) {
			for (int num = 0; num <= j; num++) {
				dp[i][j] += dp[i - 1][j - num];
			}
			dp[i][j] %= MOD;
		}
	}

	cout << dp[K][N];
	return 0;
}