/*
탑다운 방식으로 풀려고했는데 메모리 초과가 나옴
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>

#define MAX 100000
#define IMPOSSIBLE 123456789

using namespace std;

int dp[350][MAX], N, n = 0;
int value[350];

int sol(int idx, int num) {
	if (idx == n) return (num == 0 ? 0 : IMPOSSIBLE);

	if (dp[idx][num] != -1) return dp[idx][num];

	int result = sol(idx + 1, num);
	if (num >= value[idx])result = min(result, sol(idx, num - value[idx]) + 1);
	dp[idx][num] = result;

	return result;
}

int main(void) {
	cin >> N;

	int temp = 1;

	while (pow(temp, 2) <= N) {
		value[n++] = pow(temp, 2);
		temp++;
	}
	for (int i = 0; i < n; i++)memset(dp[i], -1, sizeof(int)*MAX);

	cout << sol(0, N);

	return 0;
}

따라서 다음과 같이 bottom up방식을 사용했다.

dp[i]가 의미하는 것은 i라는 수를 만들기 위해 제곱수의 합으로 나타내는 최소의 경우 수임
왜냐하면 두번째 for문에서 1부터 제곱수를 i까지 모두 비교하여 넣을 수 있는 경우를 모두 따져주기 때문.
예를들어 dp[15]를 구하자할 때 j가 2라고 가정하고 dp[15]와 dp[11] +1을 비교해준다. 이때 dp[11]은 이미 bottom up방식으로 최소의 경우수가 구해져 있음

따라서 dp[n]을 출력하면 정답이 나온다.

++ 비슷한문제 11052번
*/
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int main(void) {
	int n;
	int dp[100001];
	cin >> n;
	memset(dp, 1000000, sizeof(int) * 100001);

	dp[0] = 0, dp[1] = 1;
	
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j*j <= i; j++) {
			dp[i] = min(dp[i], dp[i - j * j] + 1);
		}
	}
	cout << dp[n];
	
	return 0;
}