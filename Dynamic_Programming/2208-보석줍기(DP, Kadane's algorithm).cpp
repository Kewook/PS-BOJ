/*
부분배열중에서 가장 최대값을 찾는 Kadane's 알고리즘을 사용하면 된다.
브루트포스 방식을 이용하면 O(N^2)으로 쉽게 구할 수 있지만
카데인 알고리즘을 사용하면 O(N)만에 구할 수 있다.
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N, M, cost[100001], psum[100001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++)cin >> cost[i], psum[i] = psum[i - 1] + cost[i];

	int ans = 0, minPsum = 2e9 + 1;
	for (int i = M; i <= N; i++) {
		minPsum = min(minPsum, psum[i - M]);
		ans = max(ans, psum[i] - minPsum);
	}
	
	cout << ans;	
	return 0;
}