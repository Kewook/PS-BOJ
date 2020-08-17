/*
전형적인 knapsack문제
dp[idx][w][b]는 0~idx선수까지 w만큼의 백팀이 남아있고 b만큼의 흑팀이 남아있을때 얻을수 있는 최대값임.

MCMF라는 방법으로도 풀수 있다고 한다.
*/
#include<iostream>
#include<cstring>

using namespace std;

int N;
int ar[1001][2], dp[1001][16][16];

int max(int a, int b) { return a > b ? a : b; }

int sol(int idx, int w, int b) {
	if (idx == N)return 0;

	if (dp[idx][w][b] != -1)return dp[idx][w][b];
	
	int result = 0;
    //idx를 백팀으로 고름
	if (w > 0)result = max(result, sol(idx + 1, w - 1, b) + ar[idx][0]);
    //흑팀으로 고름
	if (b > 0)result = max(result, sol(idx + 1, w, b - 1) + ar[idx][1]);
	
    //고르지않음
	return dp[idx][w][b] = max(result, sol(idx + 1, w, b));
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	N = 0;
	while (true) {
		cin >> ar[N][0] >> ar[N][1];
		if (cin.eof())break;
		++N;
	}
	memset(dp, -1, sizeof(dp));

	cout << sol(0, 15, 15);
	
	return 0;
}