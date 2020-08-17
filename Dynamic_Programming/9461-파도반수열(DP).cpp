/*
long long선언 주의
*/

#include<iostream>

using namespace std;

long long cache[101] = { 0,1,1 };
int T, num;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 3; i <= 100; i++) cache[i] = cache[i - 2] + cache[i - 3];

	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> num;
		cout << cache[num] << "\n";
	}
	
	return 0;
}