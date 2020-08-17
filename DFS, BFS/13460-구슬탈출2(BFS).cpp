/*
10번 기울이는것을 최대로 주어졌으니 브루트포스로도 가능하다.
go()함수부분 : 그냥 둘다 끝까지 보내놓고 같이 겹쳐있으면 원래 위치와 비교하여 하나를 돌려놓으면 된다.

제출1. 55%오답 => swap = -1로 둔점은 처음 위치를 pop()했을때 0번 기울인거니까 그것을 위해 -1로 주었다. 그 다음부터는 1씩들어나는데
11이 되었을때는 11번 기울였다는 뜻이므로 swap == 11일때 return 시켜주어야 한다.

*/
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

typedef struct Pair {
	int rypos, rxpos, bypos, bxpos;
}Pair;

queue<Pair> q;
int dy[] = { 1,0,-1,0 }, dx[] = { 0,1,0,-1 };
bool check[11][11][11][11];
char map[11][11];
int ans = -1;

void go(int &ypos, int &xpos, int dy, int dx) {
	
	while (true) {
		ypos += dy, xpos += dx;
		if (map[ypos][xpos] == 'O')break;
		if (map[ypos][xpos] == '#') {
			ypos -= dy, xpos -= dx;
			break;
		}
	}
}

void sol() {
	int swap = -1;
	bool flag = true;

	while (!q.empty()) {
		int qsize = q.size();
		swap++;

		if (swap == 11)return;
		
		for (int i = 0; i < qsize; i++) {
			Pair now = q.front();
			if (map[now.rypos][now.rxpos] == 'O') {
				ans = swap;
				return;
			}
			q.pop();

			for (int j = 0; j < 4; j++) {
				int nry = now.rypos, nrx = now.rxpos;
				int nby = now.bypos, nbx = now.bxpos;
				
				go(nry, nrx, dy[j], dx[j]);
				go(nby, nbx, dy[j], dx[j]);

				if (map[nby][nbx] == 'O')continue;

				if (nry == nby && nrx == nbx) {
					if (j == 0) {
						now.rypos < now.bypos ? nry-- : nby--;
					}
					else if (j == 1) {
						now.rxpos < now.bxpos ? nrx-- : nbx--;
					}
					else if (j == 2) {
						now.rypos < now.bypos ? nby++ : nry++;
					}
					else if (j == 3) {
						now.rxpos < now.bxpos ? nbx++ : nrx++;
					}
				}

				if (!check[nry][nrx][nby][nbx]) {
					check[nry][nrx][nby][nbx] = true;
					q.push({ nry, nrx, nby, nbx });
				}
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	int n, m, ry, rx, by, bx;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				ry = i, rx = j;
			}
			if (map[i][j] == 'B') {
				by = i, bx = j;
			}
		}
	}

	q.push({ ry,rx,by,bx });
	check[ry][rx][by][bx] = true;

	sol();
	cout << ans;
	
	return 0;
}