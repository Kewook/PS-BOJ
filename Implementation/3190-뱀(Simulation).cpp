/*
구현의 문제차.
이해못한점. 문제에서 벽이라는게 ar[][]안에서 0번인덱스가 들어간것드리 벽이라는줄 알았다.벽은 ar[][]이외의 벽을 얘기함.
실수1. 사과가 없을때 ar[ny][nx] = 0;으로해줌.
*/
#include<iostream>
#include<cstring>
#include<queue>

#define LEN 101
using namespace std;

typedef struct Pair {
	int ypos, xpos;
}Pair;

typedef struct swap_info {
	int sec;
	char dir;
}swap_info;

int n, a_num, l, dy = 0, dx = 1;
int ar[LEN][LEN] = { 0 };
bool check[LEN][LEN];
//Pair apple[LEN];
swap_info info[LEN];
queue<Pair> q;

void swap(char dir) {
	if (dir == 'D') {
		if (dy == 0 && dx == 1) {
			dy = 1, dx = 0;
		}
		else if (dy == 1 && dx == 0) {
			dy = 0, dx = -1;
		}
		else if (dy == 0 && dx == -1) {
			dy = -1, dx = 0;
		}
		else if (dy == -1 && dx == 0) {
			dy = 0, dx = 1;
		}
	}
	else {
		if (dy == 0 && dx == 1) {
			dy = -1, dx = 0;
		}
		else if (dy == 1 && dx == 0) {
			dy = 0, dx = 1;

		}
		else if (dy == 0 && dx == -1) {
			dy = 1, dx = 0;
		}
		else if (dy == -1 && dx == 0) {
			dy = 0, dx = -1;
		}
	}
}

int start(int dir_idx) {
	int time = 0;
	int ypos = q.front().ypos, xpos = q.front().xpos;

	while (!q.empty()) {
		time++;
		int ny = ypos + dy, nx = xpos + dx;
		if (ny < 0 || ny >= n || nx < 0 || nx >=  n)break;
		if (check[ny][nx])break;

		check[ny][nx] = true;
		q.push({ ny, nx });

		if (ar[ny][nx] == 1) {
			ar[ny][nx] = 0;
		}
		//사과없음
		else if (ar[ny][nx] != 1) {
			check[q.front().ypos][q.front().xpos] = false;
			q.pop();
		}

		ypos = ny, xpos = nx;

		if (time == info[dir_idx].sec) {
			swap(info[dir_idx++].dir);
		}
	}

	return time;
}

int main(void) {
	ios::sync_with_stdio(0);

	cin >> n;
	
	for (int i = 0; i < n; i++)memset(check[i], false, n);
	cin >> a_num;

	for (int i = 0; i < a_num; i++) {
		int r, c;
		cin >> r >> c;
		ar[r-1][c-1] = 1;
	}

	cin >> l;
	for (int i = 0; i < l; i++) {
		cin >> info[i].sec >> info[i].dir;
	}

	check[0][0] = true;
	q.push({ 0,0 });

	cout << start(0);

	return 0;
}