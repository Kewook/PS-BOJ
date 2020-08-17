/*
문제 제대로 안읽어서 틀림 => 비활성바이러스(2중에서 선택되지 않은 부분)에 바이러스가 가면 그부분이 활성화가 되어야한다.
*/
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Pos {
	int ypos, xpos;
};

const int INF = 987654321;

int N, M, map[51][51], virus[11], zero, vcnt, ans;
int dy[] = { 1,-1, 0,0 }, dx[] = { 0,0,1,-1 };
bool check[51][51], vcheck[11];
Pos pos[11];

void bfs() {
	memset(check, false, sizeof(check));
	queue<Pos> q;
	
	for (int i = 0; i < M; i++) {
		q.push(pos[virus[i]]);
		check[pos[virus[i]].ypos][pos[virus[i]].xpos] = true;
	}

	int infect = 0;
	int dist = 1;
	while (!q.empty()) {
		int qsize = q.size();

		for (int k = 0; k < qsize; k++) {
			int ypos = q.front().ypos, xpos = q.front().xpos;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = ypos + dy[i], nx = xpos + dx[i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
				if (check[ny][nx] || map[ny][nx] == 1)continue;

				check[ny][nx] = true;
				if (map[ny][nx] == 2) q.push({ ny, nx });
				else {
					q.push({ ny, nx});
					++infect;
				}
			}
		}

		if (infect == zero) ans = ans > dist ? dist : ans;
		++dist;
	}
}

void sol(int idx, int cnt) {
	if (cnt >= M) {
		bfs();
		return;
	}
	
	for (int i = idx; i < vcnt; i++) {
		if (vcheck[i])continue;
		vcheck[i] = true;
		virus[cnt] = i;
		sol(i, cnt + 1);
		vcheck[i] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	
	vcnt = 0;
	zero = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)zero++;
			if (map[i][j] == 2)pos[vcnt++] = { i,j };
		}
	}

	ans = INF;
	sol(0, 0);
	
	if (zero == 0)cout << 0;
	else if(ans == INF)cout << -1;
	else cout << ans;
	
	return 0;
}