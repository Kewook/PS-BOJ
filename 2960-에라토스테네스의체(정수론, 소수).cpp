/*
에라토스테네스의 체
*/
#include<iostream>

using namespace std;

int N, K;
bool check[1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	
	for (int i = 2; i <= N; i++) {
		if (check[i])continue;

		for (int j = i; j <= N; j += i) {
			if (check[j])continue;
			check[j] = true;
			--K;
			if (K == 0) {
				cout << j;
				return 0;
			}
		}
	}
	return 0;
}