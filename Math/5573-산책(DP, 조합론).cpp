/*
N이 홀수인지 짝수인지 판단하여 문제를 해결할 수 있다.
만약 지금 이동하는 횟수 K(K <= N)가 홀수일경우, 방향표는 초기값과 반대로 되어있다.
반대로 짝수일경우는 방향표가 초기값과 같다.

N-1번 갔다는 전제하에 각 교차로를 몇번 지나쳤는지 확인하고 그 횟수로 방향표를 수정해준다.
그리고 마지막으로 시뮬레이션을 돌려주면 문제가 해결가능함.

cache[i][j] : N-1번 갔을때 교차로 i,j를 지나치는 횟수

cache[1][1]은 N-1로 초기화가 되며 cache[2][1], cache[2][1]은 각각 (N-1) / 2번 지나치게 된다.
하지만 만약 cache[i][j]가 홀수면 정확히 반으로 나눌수 없기 때문에 초기 방향값 map[i][j]의 방향으로 한번 더 가주어야 한다.

따라서
cache[i][j+1] = cache[i][j] /2 + (초기값이 짝수 && cache[i][j]값이 홀수)
cache[i+1][j] = cache[i][j]/2 + (초기값이 홀수 && cache[i][j]값이 짝수)
*/
#include<iostream>

using namespace std;

int H, W, N, map[1005][1005], cache[1005][1005];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> H >> W >> N;

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++)cin >> map[i][j];
	}

	cache[1][1] = N - 1;
	
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cache[i][j + 1] += cache[i][j] / 2 + (map[i][j] && cache[i][j] & 1);
			cache[i + 1][j] += cache[i][j] / 2 + (!map[i][j] && cache[i][j] & 1);
		}
	}
	
	int ypos = 1, xpos = 1;
	while (ypos <= H && xpos <= W) {
        //N-1번 갔을때 짝수면 오른쪽으로 홀수면 밑으로
		(cache[ypos][xpos] + map[ypos][xpos]) & 1 ? xpos++ : ypos++;
	}

	cout << ypos << " " << xpos;
	return 0;
}