/*
ypos, xpos 위치, 위, 아래, 오른쪽, 왼쪽 에서 다음 위치까지의 모든 거리를 구해주면 된다.
바로 앞전의 정보만 필요하니 Sliding Window방식을 이용해서 cache값을 cache[2][5]로 구성해준다.

가장 긴 root가 200000이고 N이 10만이 넘으니 cache값은 integer 범위를 넘어선다.
식당은 한군데 위치에서밖에 출발하지 못하니 예외처리를 해준다.
*/
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

const long long INF = 1e15;
int N, ypos, xpos, pypos, pxpos;
int dy[] = { 0,1,-1,0,0 }, dx[] = { 0,0,0,1,-1 };
long long cache[2][5];

int getDist(int y1, int x1, int y2, int x2) { return abs(y1 - y2) + abs(x1 - x2); }

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> pypos >> pxpos;

	for (int c = 1; c <= N; c++) {
		cin >> ypos >> xpos;
		for (int i = 0; i < 5; i++) {
			cache[1][i] = INF;
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || nx > 100000 || ny > 100000)continue;

			for (int j = 0; j < 5; j++) {
				int pny, pnx;
				if (c == 1)pny = pypos, pnx = pxpos;
				else {
					pny = pypos + dy[j], pnx = pxpos + dx[j];
					if (pny < 0 || pnx < 0 || pnx > 100000 || pny > 100000)continue;
				}

				int dist = getDist(pny, pnx, ny, nx);
				cache[1][i] = min(cache[1][i], cache[0][j] + dist);
			}
		}
		for (int i = 0; i < 5; i++)cache[0][i] = cache[1][i];
		pypos = ypos, pxpos = xpos;
	}

	long long ans = INF;
	for (int i = 0; i < 5; i++)ans = min(ans, cache[1][i]);
	cout << ans;
	return 0;
}