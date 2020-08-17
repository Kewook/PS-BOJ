/*
이분탐색을 잘못 구현했다.

lowerbound : 내가 찾고싶은 숫자의 이상의 값이 처음으로 나오는 위치.
따라서 내가 찾고싶은 숫자의 이상의 값(찾고싶은 위치) == if(lis[mid] >= val)이 된다. 이 값이 high로 계속해서 줄어들어야한다.
*/

#include<iostream>

using namespace std;

int N, ar[1000001], lis[1000001];

int lower_bound(int low, int high, int val) {
	while (low < high) {
		int mid = (low + high) / 2;

		if (lis[mid] < val)low = mid + 1;
		else high = mid;
	}
	return high;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; i++)cin >> ar[i];

	int idx = 1;
	lis[0] = ar[0];

	for (int i = 1; i < N; i++) {
		if (lis[idx - 1] < ar[i])lis[idx++] = ar[i];
		else lis[lower_bound(0, idx, ar[i])] = ar[i];
	}

	cout << idx;
	return 0;
}