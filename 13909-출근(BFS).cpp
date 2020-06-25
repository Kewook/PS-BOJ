#include<iostream>
#include<queue>

using namespace std;

struct Pos {
	int ypos, xpos, cnt;
};

const int INF = 987654321;

int R, C, N, map[1001][1001];
int dy[10], dx[10];
bool check[1001][1001];


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C;
	
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}
	}

	cin >> N;
	for (int i = 0; i < N; i++) cin >> dy[i] >> dx[i];

	queue<Pos> q;
	for (int i = 0; i < C; i++)if (map[0][i])q.push({ 0,i,0 }), check[0][i] = true;

	int ans = INF;
	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos, cnt = q.front().cnt;
		q.pop();

		if (ypos == R - 1) {
			ans = ans > cnt ? cnt : ans;
			break;
		}

		for (int i = 0; i < N; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny >= R || nx >= C)continue;
			if (check[ny][nx] || !map[ny][nx])continue;
			check[ny][nx] = true;
			q.push({ ny, nx, cnt + 1 });
		}
	}
	
	if (ans == INF)cout << -1;
	else cout << ans;

	return 0;
}