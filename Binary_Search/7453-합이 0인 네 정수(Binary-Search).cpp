/*
2143-두배열의합 과 비슷한 문제
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, a[4001], b[4001], c[4001], d[4001];
vector<int> AB, CD;
long long ans;

int lower_bound(int l, int r, long long target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (CD[mid] >= target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int upper_bound(int l, int r, long long target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (CD[mid] > target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			AB.push_back(a[i] + b[j]);
			CD.push_back(c[i] + d[j]);
		}
	}

	sort(CD.begin(), CD.end());
	
	for (int i : AB) {
		int s = lower_bound(0, CD.size(), -i);
		int e = upper_bound(0, CD.size(), -i);
		ans += (e - s);
	}

	cout << ans;
	return 0;
}