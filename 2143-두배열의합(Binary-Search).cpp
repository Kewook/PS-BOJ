/*
1. 각 집합에서 만들수 있는 모든 부분수열의 합을 구한다.
2. A + B = T를 찾기 위해서 조건을 만족하고 A에 해당하는 B를 찾기위해서 이분탐색을 이용한다.
3. 이분탐색을 위해 B를 정렬하고 중복값이 있을 수 있으니 lowerbound 와 upperbound를 사용해서 개수를 구해준다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int T, N, M, a[1001], b[1001];
vector<long long> A, B;

int lower_bound(int l, int r, int target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (B[mid] >= target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int upper_bound(int l, int r, int target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (B[mid] > target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> T >> N;
	for (int i = 0; i < N; i++)cin >> a[i];
	cin >> M;
	for (int i = 0; i < M; i++)cin >> b[i];

	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < N; j++) {
			A.push_back(sum += a[j]);
		}
	}
	for (int i = 0; i < M; i++) {
		int sum = 0;
		for (int j = i; j < M; j++) {
			B.push_back(sum += b[j]);
		}
	}
	sort(B.begin(), B.end());

	long long ans = 0;
	for (int num : A) {
		int s = lower_bound(0, B.size(), T - num);
		int e = upper_bound(0, B.size(), T - num);
		ans += (e - s);
	}

	cout << ans;
	return 0;
}