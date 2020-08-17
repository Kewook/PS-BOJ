#include<iostream>
#include<queue>

using namespace std;

struct Pair {
	int ypos, xpos, cnt;
};

int ky[] = { -1,-2,-2,-1,1,2,2,1 }, kx[] = { 2,1,-1,-2, -2,-1,1,2 };
int dy[] = { 1,-1,0, 0 }, dx[] = { 0,0,1,-1 };

int w, h, k, map[201][201];
queue<Pair> q;
//일반적인 BFS를 통한 최단거리 문제
//이 문제의 특징은 능력을 사용할수 있는지가 관건임
//이미 방문했던 점이라 할지라도 능력을 사용했던 횟수가 다를수 있다.
//따라서 특정정점을 밟았을때 능력 사용횟수를 추가해준다.
bool check[201][201][35];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> k;
	cin >> w >> h;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
		}
	}

	q.push({ 0,0,k });
	check[0][0][k] = true;

	int ans = 0;
	while (!q.empty()) {
		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			int ypos = q.front().ypos, xpos = q.front().xpos;
			int cnt = q.front().cnt;
			q.pop();

			if (ypos == h - 1 && xpos == w - 1) {
				cout << ans;
				return 0;
			}

			if (cnt > 0) {
				for (int j = 0; j < 8; j++) {
					int ny = ypos + ky[j], nx = xpos + kx[j];
					if (ny < 0 || nx < 0 || ny >= h || nx >= w)continue;
					if (check[ny][nx][cnt - 1] || map[ny][nx])continue;
					check[ny][nx][cnt - 1] = true;
					q.push({ ny, nx, cnt - 1 });
				}
			}

			for (int j = 0; j < 4; j++) {
				int ny = ypos + dy[j], nx = xpos + dx[j];
				if (ny < 0 || nx < 0 || ny >= h || nx >= w)continue;
				if (check[ny][nx][cnt] || map[ny][nx])continue;
				check[ny][nx][cnt] = true;
				q.push({ ny, nx, cnt });
			}
		}
		++ans;
	}

	cout << -1;
	return 0;
}