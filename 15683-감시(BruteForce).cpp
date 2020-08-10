/*
실수 1: 남쪽으로 움직일때 범위가 넘어나는 계산을 검사할때 if(ny <= n)과 북쪽 범위계산도 잘못 했다.
오류 1: 만약에 카메라가 하나도 없을 경우를 생각해서 0의 갯수를 세주어야 한다.
*/
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

typedef struct Pair {
	int ypos, xpos;
}Pair;

int n, m, map[8][8], ans = 987654321;
vector<Pair> cam;

void go(int ypos, int xpos, int dir) {
	//동
	if (dir == 0) {
		while (true) {
			int nx = xpos + 1;
			if (nx >= m)break;
			if (map[ypos][nx] == 6)break;
			if (map[ypos][nx] == 0)map[ypos][nx] = -1;
			xpos = nx;
		}
	}
	//남
	else if (dir == 1) {
		while (true) {
			int ny = ypos + 1;
			if (ny >= n)break;
			if (map[ny][xpos] == 6)break;
			if (map[ny][xpos] == 0)map[ny][xpos] = -1;
			ypos = ny;
		}
	}
	//서
	else if (dir == 2) {
		
		while (true) {
			int nx = xpos - 1;
			if (nx < 0)break;
			if (map[ypos][nx] == 6)break;
			if (map[ypos][nx] == 0)map[ypos][nx] = -1;
			xpos = nx;
		}
	}
	//북
	else if (dir == 3) {
		while (true) {
			int ny = ypos - 1;
			if (ny < 0)break;
			if (map[ny][xpos] == 6)break;
			if (map[ny][xpos] == 0)map[ny][xpos] = -1;
			ypos = ny;
		}
	}
}


void sol(int idx) {
	if (idx >= cam.size()) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 0)sum++;
			}
		}
		if (ans > sum)ans = sum;
		return;
	}

	int temp[8][8];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			temp[i][j] = map[i][j];
		}
	}
	
	int ypos = cam[idx].ypos, xpos = cam[idx].xpos;
	int type = map[ypos][xpos];
	
	switch (type) {
	case 1:
		for (int dir = 0; dir < 4; dir++) {
			go(ypos, xpos, dir);
			sol(idx + 1);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					map[i][j] = temp[i][j];
				}
			}

		}
		break;
	case 2:
		for (int dir = 0; dir < 2; dir++) {
			go(ypos, xpos, dir);
			go(ypos, xpos, dir + 2);
			sol(idx + 1);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					map[i][j] = temp[i][j];
				}
			}
		}
		break;
	case 3:
		for (int dir = 0; dir < 4; dir++) {
			go(ypos, xpos, dir % 4);
			go(ypos, xpos, (dir + 1) % 4);
			sol(idx + 1);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					map[i][j] = temp[i][j];
				}
			}
		}
		break;
	case 4:
		for (int dir = 1; dir < 5; dir++) {
			go(ypos, xpos, dir % 4);
			go(ypos, xpos, dir - 1);
			go(ypos, xpos, (dir + 1) % 4);

			sol(idx + 1);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					map[i][j] = temp[i][j];
				}
			}
		}
		break;
	case 5:
		for (int dir = 0; dir < 4; dir++) {
			go(ypos, xpos, dir);
		}
		sol(idx + 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				map[i][j] = temp[i][j];
			}
		}
		break;
	}

}
int main(void) {
	ios::sync_with_stdio(0);
	
	cin >> n >> m;

	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)sum++;
			if (map[i][j] >= 1 && map[i][j] <= 5)cam.push_back({ i,j });
		}
	}
	if (sum < ans)ans = sum;
	sol(0);
	cout << ans;
}