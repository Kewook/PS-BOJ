#include<iostream>

using namespace std;

int N;
long long cache[91];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	cache[1] = 1, cache[2] = 1;

	for (int i = 3; i <= N; i++)cache[i] = cache[i - 1] + cache[i - 2];
	cout << cache[N];
	return 0;
}