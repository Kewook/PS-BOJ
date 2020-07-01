/*
오답이유:문제를 잘못이해했다.
문자하나하나를 모두 팰린드롬으로 만들어야 한다고 생각했다. 하지만 숫자 한개를 문자 자체로 생각하고 풀어야 하는 문제.

Input
3
122 221 22221
2
1 2
1 3

Output
0
0

*/
#include<iostream>

using namespace std;

int N, M, S, E, num[2001];
bool cache[2001][2001];


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; i++)cin >> num[i];

	for (int i = 1; i <= N; i++)cache[i][i] = true;
	for (int i = 1; i < N; i++)if (num[i] == num[i + 1])cache[i][i + 1] = cache[i + 1][i] = true;

	for (int i = 2; i <= N - 1; i++) {
		for (int j = 1; j <= N - i; j++) {
			if (num[j] == num[j + i] && cache[j + 1][j + i - 1])cache[j][j + i] = cache[j + i][j] = true;
		}
	}
	
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << cache[S][E] << "\n";
	}
	
	return 0;
}