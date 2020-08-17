/*
다이나믹 프로그래밍 문제는 큰 문제를 작게 나누어 푸는 문제다.
따라서 이 문제는 패턴을 찾는게 가장 크게 작용한다.
n == 1일 때 1로 한 가지 경우가 나오고
n == 2일 때 11 00 두 가지
n == 3일 때 100 111 001 세 가지 
따라서 n번째를 구할때는 n-2에다가 00을 붙이는경우 + n-1인경우는 00을 붙이면 idx가 넘어가니 1을 붙이는 경우를 더해서
피보나치 수열의 경우가 나온다.
따라서 dp[n] = dp[n-1] + dp[n-2]로 풀어주면 되는데 dp배열을 int로 선언해줄 경우에는 계산해줄때마다 나머지를 구해주어야 한다.

 */
#include<iostream>

using namespace std;
int dp[1000001];
//bottom-up 

int main(void) {
	ios::sync_with_stdio(0);
	int n;
	
	cin >> n;
	dp[0] = 1, dp[1] = 2;
	for (int i = 2; i < n; i++) {
		dp[i] = (dp[i - 2] + dp[i - 1]) % 15746;
	}
	
	cout << dp[n - 1];
	
	return 0;
}