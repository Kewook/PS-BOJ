/*
지역변수로 배열의 크기를 30만 넘는것을 선언하면 stack overflow가 나온다. == 전역변수로 선언하자
기본적인 greedy로 풀면 되는 문제
다만 입력이
1000000
1000000.........
1 1
일경우에 ans는 1000000000000(1조)가 되기때문에 int의 표현범위 20억을 넘어간다. 따라서 long long으로 ans를 선언해야함.
long long의 표현범위 9223372036854775807
*/
#include<iostream>
using namespace std;

int n, a[1000000], b, c;
long long ans = 0;

int main(void) {
	ios::sync_with_stdio(0);
	cin >> n;

	for (int i = 0; i < n; i++)cin >> a[i];
	cin >> b >> c;

	for (int i = 0; i < n; i++) {
		ans++;
		a[i] -= b;
		if (a[i] > 0) {
			ans += (a[i] / c);
			a[i] %= c;
			if (a[i] > 0)ans++;
		}
	}

	cout << ans;
	return 0;
}