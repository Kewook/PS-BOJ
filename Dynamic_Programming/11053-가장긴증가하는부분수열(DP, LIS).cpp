/*
오답이유 : cout<<dp[N-1]이라고함
반례 : 
9
3 6 7 8 4 4 4 4 4

*/
#include<iostream>

using namespace std;

int N, ar[1001],dp[1001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; i++)cin >> ar[i];

	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (dp[i] == 0)dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (ar[i] > ar[j])dp[i] = dp[i] < dp[j] + 1 ? dp[j] + 1 : dp[i];
		}
		ans = ans < dp[i] ? dp[i] : ans;
	}

	cout << ans;

	return 0;
}