/*
state 상태는 다음과 같다. 1이 벽돌로 차있는 상태고 0은 비어있는 상태 이전 행(N-1)은 모두 차있다는 가정하에 나올수 있는 state다.
0 :
0
0
0
0

3:
0
0
1
1

6:
0
1
1
0

9:
1
0
0
1

12:
1
1
0
0

cache[N][state] : 4*N크기의 타일에 1~N-1까지는 모두 차있으며 N번 줄은 state인 경우의수

따라서 각각 state를 비트로 표현했고 각 state가 나오기 전에 어떤 state들이 있는지 계산해준다.
-> 참고 블로그 : https://kibbomi.tistory.com/70
*/
#include<iostream>
#include<cstring>

using namespace std;

int cache[501][1<<4];

int sol(int idx, int state) {
	if (idx < 0)return 0;
	if (idx == 0)return state == 0;
	
	int &ret = cache[idx][state];
	if (ret != -1)return ret;

	if (state == 0)ret = sol(idx - 1, 0) + sol(idx - 2, 0) + sol(idx - 1, 3)+ sol(idx - 1, 9) + sol(idx - 1, 12);
	else if (state == 3)ret = sol(idx - 1, 0) + sol(idx - 1, 12);
	else if (state == 6)ret = sol(idx - 1, 9);
	else if (state == 9)ret = sol(idx - 1, 0) + sol(idx - 1, 6);
	else if (state == 12)ret = sol(idx - 1, 0) + sol(idx - 1, 3);

	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	memset(cache, -1, sizeof (cache));

	int T, N;
	cin >> T;
	while (T--) {
		cin >> N;
		cout << sol(N, 0) << "\n";
	}

	return 0;
}