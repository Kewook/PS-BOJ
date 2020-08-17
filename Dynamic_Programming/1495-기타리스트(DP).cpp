/*
cache[i][j] : i번째 곡을 j 볼륨으로 틀수 있는지에 대한 boolean배열
=> 슬라이딩 윈도우 적용해서 풀었다.
*/
#include<iostream>
#include<cstring>

using namespace std;

int N, S, M;
bool cache[2][1001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> S >> M;

	cache[0][S] = true;

	int v;
	for (int i = 1; i <= N; i++) {
		cin >> v;
		
		memset(cache[1], false, 1001);
		for (int j = M; j >= 0; j--) {
			if (cache[0][j] && j + v <= M)cache[1][j + v] = true;
			if (cache[0][j] && j - v >= 0)cache[1][j - v] = true;
		}
		for (int j = 0; j <= M; j++)cache[0][j] = cache[1][j];
	}

	for (int j = M; j >= 0; j--) {
		if (cache[1][j]) {
			cout << j;
			return 0;
		}
	}

	cout << -1;
	return 0;
	
}