/*
대칭으로 겹치는 경우를 제외하고 생각했을때 풀이법은 다음과 같다.
cache[i] = N이 i일때 경우의 수
2*1 타일을 하나 채우는경우 == cache[i-1]
2*2 / 1*2 타일을 이용해 2*2 면적을 채우는경우 == 2 * cache[i-2]
따라서 cache[i] = cache[i - 1] + 2 * cache[i-];

하지만 대칭으로 중복되는 경우를 제외해 주어야한다.
중복되는 경우를 찾아서 없애주는게 아니라 중복되지 않는 경우를 이용해서 겹치는 경우를 제거해준다.

이는 다음과 같은 식으로 구할 수 있다.
모든경우의 수 = 중복x + 중복o + 중복o
따라서 모든 경우의 수에 중복x 인경우를 더해서 2로 나누면 얻을 수 있다.

중복을 제외한 경우의수 = (모든경우의수(중복x + 중복o + 중복o) + 중복x ) /2 == 중복o + 중복x

무조건 중복되지 않는 경우는 2*1 타일을 연속으로 나열하는 것과같은 완전 대칭 타일을 예로 들수 있다.
완전대칭타일은 홀수와 짝수일때 다른방식으로 구해야한다.

S[i] == i길이에서 완전대칭타일의 개수

ex) N == 5
가운데 2*1타일을 하나 두고 양옆에 길이가 2씩 남아있는 경우
S[i] = cache[(i-1) / 2]

ex) N == 6
가운데 2*1타일을 두개둔경우 + 가운데 2*2 타일을 둔경우 + i/2길이만큼 대칭인경우
S[i] = cache[i/2] + 2 * cache[i/2 + 1];

답을 구할때 cache는 변경하면 안된다.
따라서 N == 1 || N == 2 인경우에 조심해야함.
*/
#include<iostream>

using namespace std;

int N, cache[31];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	cache[1] = 1, cache[2] = 3;

	if (N < 3)cout << cache[N];
	else {
		int ans;
		for (int i = 3; i <= N; i++) {
			cache[i] = cache[i - 1] + 2 * cache[i - 2];
			if (i % 2)ans = (cache[i] + cache[i / 2]) / 2;
			else ans = (cache[i] + (cache[i / 2] + cache[i / 2 - 1] * 2)) / 2;
		}

		cout << ans;
	}
	return 0;
}