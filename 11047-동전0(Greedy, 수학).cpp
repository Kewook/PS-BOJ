/*
동전문제

처음에는 DP로 풀려다가 메모리초과가 났다. 메모리 제한은 256Mbye(2억5천6백만 바이트) dp배열의 최대 크기는 1억이 넘으므로 메모리초과 발생
문제의 조건에 큰단위 동전은 작은단위 동전의 배수라는 조건이 있어서 그리디로 접근 가능하다.
*/
#include<iostream>

using namespace std;

int N, K, coin[10];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++)cin >> coin[i];

	int ans = 0;
	while (K > 0) {
		if (K / coin[N - 1]) ans += K / coin[N - 1];
		K %= coin[N - 1];
		--N;
	}

	cout << ans;
	return 0;
}