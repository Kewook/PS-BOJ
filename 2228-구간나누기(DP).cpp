/*
cache[i][j] : 1~i인덱스 사이에서 j개의 구간을 선택했을때 얻을수있는 합의 최대값

나올수 있는 수가 음수와 양수가 모두 존재한다. ==> cache배열 초기화 똑바로하자
cache배열에 -20억으로 초기화하고 25번라인에 ret = -10억을 주고 탐색하는 방식도 있다

cache배열을 -1로 보통 초기화하지만 음수들의 합으로 답에 -1이 나올수 있는경우를 대비해서 check배열을 두는 방식도 있다.
*/

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int N, M, cache[101][51], psum[101];

int sol(int idx, int cnt) {
	if (!cnt)return 0;
	if (idx > N)return -INF;
	
	int &ret = cache[idx][cnt];
	if (ret != -1)return ret;

    //idx가 구간에 속하지 않고 넘어가는 경우
	ret = sol(idx + 1, cnt);
    //idx가 구간에 속하는경우 구간은 인접할수 없으니 i+2를 인자로 넘겨준다.
	for (int i = idx; i <= N; i++) {
		ret = max(ret, sol(i + 2, cnt - 1) + psum[i] - psum[idx - 1]);
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	
	int num = 0;
	for (int i = 1; i <= N; i++) {
		cin >> num;
		psum[i] = psum[i - 1] + num;
	}
	
	memset(cache, -1, sizeof(cache));
	cout << sol(1, M);

	return 0;
}