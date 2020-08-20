/*
2467-용액 문제와 동일한 문제다.
*/
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N, ar[1000001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	int l = 0, r = N - 1;
	for (int i = 0; i < N; i++) cin >> ar[i];
	sort(ar, ar + N);
    
	int ans = 2e9 + 1, minl, minr;
	while (l < r) {
		int diff = abs(ar[r] + ar[l]);
		if (diff < ans)ans = diff, minl = l, minr = r;

		if (ar[l] + ar[r] < 0)l++;
		else r--;
	}

	cout << ar[minl] << " " << ar[minr];
	return 0;
}

/*
이분탐색을 이용한 방법
*/

#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N, ar[1000001];

int lower_bound(int l, int r, int target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (ar[mid] >= target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> ar[i];
	sort(ar, ar + N);
    
	int minDiff = 2e9 + 1, ans1, ans2;
	for (int i = 0; i < N; i++) {
		int pos = lower_bound(0, N, -ar[i]);
		for (int j = pos - 1; j <= pos; j++) {
			if (j < 0 || j >= N || i == j)continue;
			int diff = abs(ar[i] + ar[j]);
			if (minDiff > diff) minDiff = diff, ans1 = ar[i], ans2 = ar[j];
		}
	}
	
	cout << min(ans1, ans2) << " " << max(ans1, ans2);
	return 0;
}