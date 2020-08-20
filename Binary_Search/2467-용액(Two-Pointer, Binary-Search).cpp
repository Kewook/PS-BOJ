/*
투포인터를 이용해서 문제풀이를 한다. 이 문제에서 투포인터는 다음과 같이 동작한다.
1. l은 0 r = N-1에서부터 시작하며 l과 r이 같아지면 종료한다.
2. 만약 ar[l] + ar[r]의 혼합값이(절대값이 아니다) 음수면 더 혼합값을 더 줄이기 위해 l을 늘린다.
3. 만약 혼합값의 0 이상이면 혼합값을 더 줄여야하기 때문에 r을 줄여준다.(l을 늘려도 되지만 음수가 있기때문에)
*/
#include<iostream>
#include<cmath>

using namespace std;

int N, ar[100001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	int l = 0, r = N - 1;
	for (int i = 0; i < N; i++) cin >> ar[i];
	
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
이분탐색을 이용해서 푸는 방법은 다음과 같다.
N개의 용액을 검사하면서 lowerbound(-num)을 찾아준다.
이때 return값은 -num값 이상인 값이 처음으로 나오는 위치를 return하게 되는데 이 값이 -num과 같은경우 0으로 최소값을 유지하지만
만약 -num인값이 없을경우를 대비해서 pos-1위치도 찾아주어야한다.

input
-5 -3 -2 0 1 3 4
의 예시로 3과 -3을 대입해보자
*/

#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N, ar[100001];

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