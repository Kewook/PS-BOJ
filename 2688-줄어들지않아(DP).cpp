/*
cache[i][j] : i자리의 숫자에서 맨앞자리가 j일때의 줄어들지않는 수의 개수

cache[i][j] += cache[i-1][k] (j <= k) : 맨앞자리가 j라면 한자리가 적을때 j보다 큰 앞자리의 총합
*/
#include<iostream>

using namespace std;

long long cache[65][10];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	int T, N;
	
	for (int i = 0; i <= 9; i++)cache[1][i] = 1;
	for (int i = 2; i <= 64; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = j; k <= 9; k++) {
				cache[i][j] += cache[i - 1][k];
			}
		}
	}
	
	cin >> T;
	while (T--) {
		cin >> N;

		long long ans = 0;
		for (int i = 0; i <= 9; i++)ans += cache[N][i];

		cout << ans << "\n";
	}
	
	return 0;
}