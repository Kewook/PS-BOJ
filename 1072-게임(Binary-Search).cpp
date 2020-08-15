/*
Z가 변하는 게임 횟수 a를 이분탐색을 이용해서 찾는다.
*/

#include<iostream>

using namespace std;

long long x, y, z;

long long calc(long long a) {
    //(y+a) / (x + a)먼저하면 소수점이 유실된다.
	return ((y + a) * 100) / (x + a);
}

long long lower_bound(long long l, long long r) {
    //모두다 long long 형으로 선언해주었는데 calc부분에서 *100을 하면 integer범위가 넘어선다.
	while (l < r) {
		long long mid = (l + r) / 2;
		if (calc(mid) >= z + 1)r = mid;
		else l = mid + 1;
	}
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> x >> y;
	z = calc(0);
	
    //승률이 99%면 절대 높아질 수 없다.
	if (z >= 99)cout << -1;
	else cout << lower_bound(0, 1000000001);

	return 0;
}