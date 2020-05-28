/*
빡구현

수영장을 3차원 배열로 바라보면 3차원 Bfs를 돌리면 된다. 하지만 너무 복잡하니까 2차원배열을 높이만큼 돌려준다.
*/
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int N, M, ar[51][51], pool[10][51][51], ans;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[51][51];

struct Pos {
	int ypos, xpos;
};

//bfs로 탐색하며 만약 탐색도중 -1(사라진 물)을 만나면 그와 관련된 물은 전부다 -1로 흘러간다.
void bfs(int z, Pos pos) {
	vector<Pos> v;
	queue<Pos> q;
	q.push(pos);
	v.push_back(pos);
	check[pos.ypos][pos.xpos] = true;
	
	bool flag = false;

	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (pool[z][ny][nx] == -1) flag = true;
			if (ny < 1 || nx < 1 || ny >= N - 1 || nx >= M - 1)continue;
			if (pool[z][ny][nx] == 1 || check[ny][nx])continue;
			check[ny][nx] = true;
			q.push({ ny, nx });
			v.push_back({ ny, nx });
		}
	}
	if (flag) for (Pos pos : v)pool[z][pos.ypos][pos.xpos] = -1;
	else ans += v.size();
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

    //수영장 초기화 부분 바닥이 있는 부분은 1 물은 0
	int Max = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char c;
			cin >> c;
			ar[i][j] = c - '0';
			Max = Max < ar[i][j] ? ar[i][j] : Max;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int z = 0; z < ar[i][j]; z++)pool[z][i][j] = 1;
		}
	}

	ans = 0;

    //물은 위에서 아래로 탐색해준다.
	for (int z = Max - 1; z >= 0; z--) {
        //테두리부분 제거해준다. 테두리에 아무것도 없다는것은 그냥 밖으로 넘친다는 얘기임
		for (int i = 0; i < M; i++) {
			if (!pool[z][0][i])pool[z][0][i] = -1;
			if (!pool[z][N - 1][i])pool[z][N - 1][i] = -1;
		}
		for (int i = 1; i < N - 1; i++) {
			if (!pool[z][i][0])pool[z][i][0] = -1;
			if (!pool[z][i][M - 1])pool[z][i][M - 1] = -1;
		}

        //테두리 부분 안쪽을 탐색한다.
		memset(check, false, sizeof(check));
		for (int i = 1; i < N - 1; i++) {
			for (int j = 1; j < M - 1; j++) {
				if (!pool[z][i][j] && !check[i][j])bfs(z, { i,j });
			}
		}
	}

	cout << ans;

	return 0;
}