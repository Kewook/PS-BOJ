/*
1번 색이 선택된것과 아닌것의 차이에서 값이 변경된다.

cache[idx][cnt][flag]로 구성하면 틀리고
cache[flag][idx][cnt]로 구성하면 맞는다 왜그런지는 아직 모르겠다.
*/

#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000003;

int N, K, cache[2][1001][1001];

int sol(int idx, int cnt, bool flag) {
	if (cnt == K) return 1;

	int &ret = cache[flag][idx][cnt];
	if (ret != -1)return ret;

	ret = 0;
	for (int i = idx; i < N; i++) {
        //1번이 선택됐는데 마지막 색이 선택되면 안된다.
		if (flag && i == N - 1)break;
		
		if (cnt == 0 && i == 0)flag = true;
		else if (cnt == 0 && i > 0)flag = false;
		
		ret += sol(i + 2, cnt + 1, flag);
		ret %= MOD;
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	memset(cache, -1, sizeof(cache));
	cout << sol(0, 0, false);

	return 0;
}


/*
bottom-up방식

cache[i][j] : i가지 색으로 j개 골랐을때 경우의 수

i번째 색을 볼때 선택할수 있고 선택하지 않을 수 있으니 두 가지 경우를 나눠 생각한다.
i번째 색을 선택하는 경우 : i-1번째색은 선택하지 못하니 i-2가지 색으로 j-1개 골랐을때와 같다 == cache[i-2][j-1]
i번째 색을 선택하지 않는 경우 : i-1가지 색으로 j가지 골랐을때 == cache[i-1][j]

마지막 색같은 경우에는 첫번째 색이 선택되지 않아야하기 때문에 예외처리를 해준다.

cache[N][M]을 칠하는 경우 : 첫번째, N-1번째, N번째를 제외하고 N-3가지 색으로 j-1개 골랐을때의 경우의수 == cache[N-3][j-1]
칠하지 않는경우 : N-1개 색으로 j개 골랐을때 경우의수
*/

#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000003;

int N, K, cache[1001][1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> K;	

	for (int i = 1; i <= N; i++) {
		cache[i][0] = 1;
		cache[i][1] = i;
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= K; j++) {
			cache[i][j] = (cache[i - 1][j] + cache[i - 2][j - 1]) % MOD;
		}
	}

	cout << (cache[N - 3][K - 1] + cache[N - 1][K]) % MOD;
	return 0;
}