/*
YES, NO가 아니라
Yes, No다
*/
#include<iostream>
#include<cstring>

using namespace std;

struct Info {
	int ypos, xpos;
};

int N, M;
int dy[] = { 1,-1,0,0 };
int dx[] = { 0,0, 1, -1 };
char map[51][51];
bool check[51][51];

void dfs(Info s, Info cur, int cnt) {
	

	for (int i = 0; i < 4; i++) {
		int ny = cur.ypos + dy[i], nx = cur.xpos + dx[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
		if (map[ny][nx] != map[s.ypos][s.xpos])continue;
		if (s.ypos == ny && s.xpos == nx && cnt >= 4) {
			cout << "Yes";
			exit(0);
		}
		if (check[ny][nx])continue;
		check[ny][nx] = true;
		dfs(s, { ny, nx }, cnt + 1);
		check[ny][nx] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			memset(check, false, sizeof(check));
			check[i][j] = true;
			dfs({ i,j }, { i,j }, 1);
		}
	}

	cout << "No";

	return 0;
}