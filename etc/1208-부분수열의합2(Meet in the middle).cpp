/*
Meet in the middle 알고리즘 기초
공집합을 포함하지 않으니 S가 0이면 정답을 한개 빼줘야한다.
*/
#include<iostream>
#include<map>

using namespace std;

int N, S, ar[41], half;
map<int, int> mp;
long long ans = 0;

void dfs1(int idx, int sum) {
	if (idx == half) {
		mp[sum]++;
		return;
	}

	dfs1(idx + 1, sum);
	dfs1(idx + 1, sum + ar[idx]);
}

void dfs2(int idx, int sum) {
	if (idx == N) {
		ans += mp[S - sum];
		return;
	}

	dfs2(idx + 1, sum);
	dfs2(idx + 1, sum + ar[idx]);
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> S;
	for (int i = 0; i < N; i++)cin >> ar[i];

	half = N / 2;
	
	dfs1(0, 0);
	dfs2(half, 0);

	if (!S)--ans;
	cout << ans;
	
	return 0;
}