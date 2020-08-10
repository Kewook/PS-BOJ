/*
처음에는 구조체를
Pos{
    int ypos, xpos, cnt;
    bool key[6];
}
로 선언해서 큐에다가 넣으려고 해서 메모리초과가 났음

==> 비트마스크를 이용하자.
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

struct Pos {
	int ypos, xpos, cnt, key;
};

int N, M;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[51][51][1<<6];// == check[ypos][xpos][key]
char map[51][51];
queue<Pos> q;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == '0') {
				q.push({ i, j, 0, 0 });
			}
		}
	}


    //0은 키가 없는 상태
    //1<<0 이랑 0은 엄연히 다르다.(아무것도 가지지 않은 상태를 1<<0 으로 생각함)
	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos;
		int cnt = q.front().cnt, key = q.front().key;
		q.pop();

		if (map[ypos][xpos] == '1') {
			cout << cnt;
			return 0;
		}

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
			if (check[ny][nx][key] || map[ny][nx] == '#')continue;

			if (map[ny][nx] == '.' || map[ny][nx] == '0' || map[ny][nx] == '1') {
				q.push({ ny, nx, cnt + 1, key });
				check[ny][nx][key] = true;
			}
			else if ((map[ny][nx] >= 'A' && map[ny][nx] <= 'F') && (key & (1 << (int)map[ny][nx] - 'A'))) {
				q.push({ ny, nx, cnt + 1, key });
				check[ny][nx][key] = true;
			}
			else if (map[ny][nx] >= 'a' && map[ny][nx] <= 'f') {
				int nkey = key | (1 << (int)map[ny][nx] - 'a');
				q.push({ ny, nx, cnt + 1, nkey });
				check[ny][nx][nkey] = true;
			}
		}
	}
	cout << -1;

	return 0;
}