/*
cache[i][num] : i번째 자리까지의 숫자를 사용해서 num을 만들수 있는 경우의수
*/
#include<iostream>

using namespace std;

int N, ar[101];
long long cache[101][21];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++)cin >> ar[i];

	cache[1][ar[1]]++;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= 20; j++) {
            //0~20을 사용해서 만들수 있는 모든 경우의수를 구한다.
			if (j + ar[i] <= 20)cache[i][j + ar[i]] += cache[i - 1][j];
			if (j - ar[i] >= 0)cache[i][j - ar[i]] += cache[i - 1][j];
		}
	}
	
    //마지막수는 결과로 써야한다.
	cout << cache[N - 1][ar[N]];
	return 0;
}