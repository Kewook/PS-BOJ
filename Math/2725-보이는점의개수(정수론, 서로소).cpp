/*
(x,y)에서 x와 y가 서로 서로소인 점의 개수를 찾으면 된다.

처음에는 테스트케이스의 개수가 1000임을 감안 못하고 O(N^3)으로 풀어서 TLE

cache배열에 그전의 값을 저장해놓으면 빠르게 풀수 있다.
*/
#include<iostream>

using namespace std;

int cache[1001], T, N;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> T;

	cache[1] = 3;
	for (int i = 2; i <= 1000; i++) {
		cache[i] = cache[i - 1];
		for (int j = 1; j < i; j++)if (gcd(i, j) == 1)cache[i] += 2;
	}
	
	while (T--) {
		cin >> N;
		cout << cache[N] << "\n";
	}
	return 0;
}