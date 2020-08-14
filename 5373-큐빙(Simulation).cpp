#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

struct Order {
	int num, fy, fx, sy, sx, ey, ex;
};

struct Pos {
	int ypos, xpos;
};

int T, N;
Order order[6][4] = {
	{{5,2,2,1,2,0,2}, {1,0,0,1,0,2,0}, {4,2,2,1,2,0,2}, {3,2,2,1,2,0,2}},
	{{5,0,2,0,1,0,0}, {2,0,0,1,0,2,0}, {4,2,0,2,1,2,2}, {0,2,2,1,2,0,2}},
	{{5,0,0,1,0,2,0}, {3,0,0,1,0,2,0}, {4,0,0,1,0,2,0}, {1,2,2,1,2,0,2}},
	{{5,2,0,2,1,2,2}, {0,0,0,1,0,2,0}, {4,0,2,0,1,0,0}, {2,2,2,1,2,0,2}},
	{{3,2,0,2,1,2,2}, {0,2,0,2,1,2,2}, {1,2,0,2,1,2,2}, {2,2,0,2,1,2,2}},
	{{1,0,2,0,1,0,0}, {0,0,2,0,1,0,0}, {3,0,2,0,1,0,0}, {2,0,2,0,1,0,0}}
};

Pos pos[2][9] = {
	{{2,0}, {1,0}, {0,0}, {2,1}, {1,1}, {0,1}, {2,2}, {1,2}, {0,2}},
	{{0,2}, {1,2}, {2,2}, {0,1}, {1,1}, {2,1}, {0,0}, {1,0}, {2,0}}
};
char state[6][3][3], color[] = { 'b', 'o', 'g', 'r', 'y', 'w' };

void rotate(char w, int dir) {
	int s, e;
	if (dir == 1)s = 0, e = 4;
	else s = 3, e = -1;

	char prev[3] = { state[order[w][s].num][order[w][s].fy][order[w][s].fx] , state[order[w][s].num][order[w][s].sy][order[w][s].sx], state[order[w][s].num][order[w][s].ey][order[w][s].ex] };
	for (int i = s + dir; i != e; i += dir) {
		char cur[3] = { state[order[w][i].num][order[w][i].fy][order[w][i].fx] , state[order[w][i].num][order[w][i].sy][order[w][i].sx], state[order[w][i].num][order[w][i].ey][order[w][i].ex] };
		state[order[w][i].num][order[w][i].fy][order[w][i].fx] = prev[0];
		state[order[w][i].num][order[w][i].sy][order[w][i].sx] = prev[1];
		state[order[w][i].num][order[w][i].ey][order[w][i].ex] = prev[2];
		for (int j = 0; j < 3; j++)prev[j] = cur[j];
	}
	state[order[w][s].num][order[w][s].fy][order[w][s].fx] = prev[0]; state[order[w][s].num][order[w][s].sy][order[w][s].sx] = prev[1]; state[order[w][s].num][order[w][s].ey][order[w][s].ex] = prev[2];

	char temp[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)temp[i][j] = state[w][i][j];
	}
	int idx = 0, cnt = 0;
	if (dir == -1)idx = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state[w][i][j] = temp[pos[idx][cnt].ypos][pos[idx][cnt].xpos];
			++cnt;
		}
	}
}
	
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> T;
	while (T--) {
		for (int c = 0; c < 6; c++) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					state[c][i][j] = color[c];
				}
			}
		}

		cin >> N;
		string str;
		for (int i = 0; i < N; i++) {
			cin >> str;
			int w;
			if (str[0] == 'U')w = 5;
			else if (str[0] == 'D')w = 4;
			else if (str[0] == 'F')w = 3;
			else if (str[0] == 'L')w = 2;
			else if (str[0] == 'B')w = 1;
			else w = 0;

			rotate(w, str[1] == '+' ? 1 : -1);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << state[5][i][j];
			}
			cout << "\n";
		}
	}
	return 0;
}