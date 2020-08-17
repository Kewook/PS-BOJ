/*
문제를 읽고 직접 input값을 만들어보며 패턴을 파악하는게 중요하다.
4
2 3 4 1 과

8
1 6 2 3 7 4 5 8
이 두가지 예에서 보다시피 꼬인 전기줄 최소로 자르기 위해 꼬인 부분을 가장 길게 가져가야 하는데
그 꼬인부분이 가장 길다라는 것은 가장 긴 증가하는 부분 수열(LIS)다.
*/
#include<iostream>
#include<vector>

using namespace std;

int N;
vector<int> lis;

int lower_bound(int l, int r, int target) {
	while (l < r) {
		int mid = (l + r) / 2;
		if (lis[mid] >= target)r = mid;
		else l = mid + 1;
	}
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int num;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (!lis.size() || lis[lis.size() - 1] < num)lis.push_back(num);
		else lis[lower_bound(0, lis.size(), num)] = num;
	}
	
	cout << N - lis.size();
	return 0;
}