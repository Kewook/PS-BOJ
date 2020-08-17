/*
틀린이유1. 바둑을 놓고 백트래킹 안해줌(다시 .로 수정을 안해줌)
틀린이유2. isTrue할때 한 방향으로 ypos, xpos를 조작하여 탐색했지만 반대방향으로 탐색할때
ypos xpos를 pos.ypos, pos.xpos로 다시 재초기화 안해주어서 틀림.
*/
#include<iostream>
#include<vector>

using namespace std;

struct Info {
	int ypos, xpos;
};

char map[10][10];
vector<Info> info;
int dy[] = { -1,-1,-1,0,1,1,1,0 }, dx[] = { -1,0,1,1,1,0,-1,-1 };

bool isTrue(Info pos, int ddy, int ddx) {
	int ypos = pos.ypos, xpos = pos.xpos;
	int cnt = 1;
	
	while (true) {
		int ny = ypos + ddy, nx = xpos + ddx;
		if (ny < 0 || nx < 0 || ny >= 10 || nx >= 10)break;
		if (map[ny][nx] != 'X')break;
		ypos = ny;
		xpos = nx;
		cnt++;
	}
	ddy *= -1; ddx *= -1;
	ypos = pos.ypos; xpos = pos.xpos;
	while (true) {
		int ny = ypos + ddy, nx = xpos + ddx;
		if (ny < 0 || nx < 0 || ny >= 10 || nx >= 10)break;
		if (map[ny][nx] != 'X')break;
		ypos = ny;
		xpos = nx;
		cnt++;
	}

	if (cnt >= 5)return true;
	else return false;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'X')info.push_back({ i,j });
		}
	}

	for (int i = 0; i < info.size(); i++) {
		int ypos = info[i].ypos, xpos = info[i].xpos;

		for (int k = 0; k < 8; k++) {
			int ny = ypos + dy[k], nx = xpos + dx[k];
			if (ny < 0 || nx < 0 || ny >= 10 || nx >= 10)continue;
			if (map[ny][nx] != '.')continue;
			map[ny][nx] = 'X';
			if (isTrue({ ypos, xpos }, dy[k], dx[k])) {
				cout << 1;
				return 0;
			}
			map[ny][nx] = '.';
		}
	}

	cout << 0;

	return 0;
}