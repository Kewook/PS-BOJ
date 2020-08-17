/*
top-down

cache[i][l][a] : i번째 날까지 지각은 l번 결석은 연속으로 a번 했을 때 개근상을 받을 수 있는 경우의수

처음에는 ret += (sol(task) % MOD)로 했다가 WA를 받았다.
-> MOD 분배법칙 잘 생각하고 사용하자. 이렇게 썻을때는 ret에 MOD한 연산이 들어가지만 ret자체가 mod연산이 된게 아니다.
*/
#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000;
int N, cache[1005][2][3];

int sol(int cnt, int l, int a) {
	if (cnt >= N) return 1;

	int &ret = cache[cnt][l][a];
	if (ret != -1)return ret;

	ret = 0;
	ret += sol(cnt + 1, l, 0);
	if (a < 2)ret += sol(cnt + 1, l, a + 1);
	if (l < 1)ret += sol(cnt + 1, l + 1, 0);

	ret %= MOD;
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	memset(cache, -1, sizeof(cache));
	cout << sol(0, 0, 0);
	return 0;
}


/*
bottom-up
*/

#include<iostream>

using namespace std;

const int MOD = 1000000;
int N, cache[1005][2][3];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	
	cache[1][0][0] = cache[1][0][1] = cache[1][1][0] = 1;
	
	for (int i = 2; i <= N; i++) {
		cache[i][0][0] = (cache[i - 1][0][0] + cache[i - 1][0][1] + cache[i - 1][0][2]) % MOD;
        //cache[i][0][0] == cache[i - 1][0][0] + cache[i - 1][0][1] + cache[i - 1][0][2]; 앞에서 이미 계산해서 바로 더해줌. (코드 간결화)
		cache[i][1][0] = (cache[i - 1][1][0] + cache[i - 1][1][1] + cache[i - 1][1][2] + cache[i][0][0]) % MOD;
		
		cache[i][0][1] = cache[i - 1][0][0] % MOD;
		cache[i][0][2] = cache[i - 1][0][1] % MOD;
		cache[i][1][1] = cache[i - 1][1][0] % MOD;
		cache[i][1][2] = cache[i - 1][1][1] % MOD;
	}
	
	cout << (cache[N][0][0] + cache[N][0][1] + cache[N][0][2] + cache[N][1][0] + cache[N][1][1] + cache[N][1][2]) % MOD;
	return 0;
}