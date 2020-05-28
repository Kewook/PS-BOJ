/*
구현력 딸릴때 한번씩 풀어보자.
*/

#include<iostream>

using namespace std;

struct Info {
	char color;
	int num;
};

char ing[11][4][4][4];
int N, eff[11][4][4][4], ans;
int dy[] = { 0,0,1,1 }, dx[] = { 0,1,0,1 };
bool comb[11], pos[3][4], mode[3][4];
int rootnum[3], rootpos[3], rootmode[3];

void checkMode(int idx) {
	if (idx >= 3) {
		Info info[5][5];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)info[i][j] = { 'W', 0 };
		}

		for (int n = 0; n < 3; n++) {
			int num = rootnum[n], mode = rootmode[n];
			int ypos = dy[rootpos[n]], xpos = dx[rootpos[n]];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					info[i + ypos][j + xpos].num += eff[num][mode][i][j];
					if (info[i + ypos][j + xpos].num < 0)info[i + ypos][j + xpos].num = 0;
					if (info[i + ypos][j + xpos].num > 9)info[i + ypos][j + xpos].num = 9;
					if (ing[num][mode][i][j] != 'W') info[i + ypos][j + xpos].color = ing[num][mode][i][j];
				}
			}
		}

		int sum = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (info[i][j].color == 'R')sum += info[i][j].num * 7;
				else if (info[i][j].color == 'B')sum += info[i][j].num * 5;
				else if (info[i][j].color == 'G')sum += info[i][j].num * 3;
				else if (info[i][j].color == 'Y')sum += info[i][j].num * 2;
			}
		}

		ans = ans < sum ? sum : ans;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (mode[idx][i])continue;
		mode[idx][i] = true;
		rootmode[idx] = i;
		checkMode(idx + 1);
		mode[idx][i] = false;
	}
}

void checkPos(int idx) {
	if (idx >= 3) {
		checkMode(0);
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		if (pos[idx][i])continue;
		pos[idx][i] = true;
		rootpos[idx] = i;
		checkPos(idx + 1);
		pos[idx][i] = false;
	}
}

void checkNum(int cnt) {
	if (cnt >= 3) {
		checkPos(0);
		return;
	}

	for (int i = 0; i < N; i++) {
		if (comb[i])continue;
		comb[i] = true;
		rootnum[cnt] = i;
		checkNum(cnt + 1);
		comb[i] = false;
	}
}



int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	for (int n = 0; n < N; n++) {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> eff[n][0][i][j];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> ing[n][0][i][j];
			}
		}
	}

	//회전 preprocess
	for (int n = 0; n < N; n++) {
		for (int r = 1; r < 4; r++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					ing[n][r][j][3 - i] = ing[n][r - 1][i][j];
					eff[n][r][j][3 - i] = eff[n][r - 1][i][j];
				}
			}
		}
	}
	ans = 0;
	checkNum(0);
	
	cout << ans;

	return 0;
}