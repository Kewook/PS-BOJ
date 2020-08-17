/*
1시간동안 로직도 못떠올렸다.

cache[N][L][R] : N개의 건물이 있을때 왼쪽에서 바라보면 L개가 있고 오른쪽에서 바라보면 R개가 있을때의 경우의수

N의 이전단계에 집중해보면 N-1개의 건물이 있을것이고 1 ~ N-1까지의 높이를 가지고있다.
따라서 N개의 건물이 있다고 가정하려면 높이를 모두 1씩 높여주고 높이가 1인 건물을 하나 더 추가하는 방법을 생각할 수 있다.

높이 1인 건물을 맨 왼쪽에 추가했을때는 왼쪽에서 바라볼때 무조건 1개가 더 늘어난다. == cache[N][L][R] += cache[N-1][L-1][R] + 1;
높이 1인 건물을 맨 오른쪽에 추가했을때는 오른쪽에서 바라볼때 무조건 1개가 더 늘어난다. == cache[N][L][R] += cache[N-1][L][R-1] + 1;
높이 1인 건물을 맨 왼쪽, 오른쪽이 아닌 다른곳에 배치했을 때는 왼쪽이든 오른쪽이든 바라볼때 그대로다. == cache[N][L][R] += cache[N-1][L][R]
 => 하지만 이경우는 N-2번 발생할수 있으니 N-2번 더해준다.
*/
#include<iostream>

using namespace std;

const int MOD = 1000000007;

int N, L, R;
long long cache[101][101][101];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L >> R;
	
	cache[1][1][1] = 1;
	for (int i = 2; i <= N; i++) {
		for (int l = 1; l <= L; l++) {
			for (int r = 1; r <= R; r++) {
				cache[i][l][r] = cache[i - 1][l - 1][r] + cache[i - 1][l][r - 1] + cache[i - 1][l][r] * (i - 2);
				cache[i][l][r] %= MOD;
			}
		}
	}
	
	cout << cache[N][L][R];

	return 0;
}