/*
외판원순회 문제와 비슷하게 풀이하면 된다.

cache[idx][prev][check] : idx자리까지 확인했을때 전의 자리수에서 숫자가 prev이고 현재까지 사용한 숫자가 check일때의 경우의수

기저사례에서 모두 방문했을때와 idx>=N일때를 구분해서 return 해주어야한다.
*/
#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1e9;
int N, cache[101][10][1 << 10];

int sol(int idx, int prev, int check) {
	if (idx >= N) {
		if (check == (1 << 10) - 1)return 1;
		else return 0;
	}
	
	int &ret = cache[idx][prev][check];
	if (ret != -1)return ret;

	ret = 0;
	if (prev < 9)ret += sol(idx + 1, prev + 1, check | (1 << (prev + 1)));
	ret %= MOD;
	if (prev > 0)ret += sol(idx + 1, prev - 1, check | (1 << (prev - 1)));
	ret %= MOD;

	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	
	int ans = 0;
	memset(cache, -1, sizeof(cache));

    //첫 번째 자리는 0이 될수 없다.
	for (int i = 1; i <= 9; i++) {
		ans += sol(1, i, 1 << i);
		ans %= MOD;
	}

	cout << ans;
	return 0;
}


/*
bottom-up방식
*/

#include<iostream>

using namespace std;

const int MOD = 1e9;
int N, cache[101][10][1 << 10];


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	
	int all = (1 << 10) - 1;
    //첫자리가 1~9인 사례 초기화
	for (int i = 1; i < 10; i++)cache[1][i][1 << i] = 1;
	
	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k <= all; k++) {
				if (j == 0)cache[i][0][k | (1 << 0)] = (cache[i][0][k | (1 << 0)] + cache[i - 1][1][k]) % MOD;
				else if (j == 9)cache[i][9][k | (1 << 9)] = (cache[i][9][k | (1 << 9)] + cache[i - 1][8][k]) % MOD;
				else {
					cache[i][j][k | (1 << j)] = (cache[i][j][k | (1 << j)] + cache[i - 1][j - 1][k]) % MOD;
					cache[i][j][k | (1 << j)] = (cache[i][j][k | (1 << j)] + cache[i - 1][j + 1][k]) % MOD;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < 10; i++)ans = (ans + cache[N][i][all]) % MOD;
	
	cout << ans;
	return 0;
}