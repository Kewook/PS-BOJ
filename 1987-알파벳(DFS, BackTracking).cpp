/*
백트래킹을 적용하지 않았다.
예를들어
2 4
ABCA
CAAA인경우에 답이 2가 나오게 하였다.
반드시 방문을하지 않으면 check를 false로 해주어야 함.
*/
#include<iostream>
#include<cstring>

using namespace std;

int r, c, ans = 0;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
char map[21][21];
//알파벳 26개
bool check[26];

typedef struct Pair {
	int ypos, xpos;
}Pair;

void dfs(Pair p, int cnt) {
	ans = cnt > ans ? cnt : ans;

	int ypos = p.ypos, xpos = p.xpos;
	for (int i = 0; i < 4; i++) {
		int ny = ypos + dy[i], nx = xpos + dx[i];
		if (ny < 0 || nx < 0 || ny >= r || nx >= c)continue;
		int index = map[ny][nx] - 'A';
		if (check[index])continue;
		check[index] = true;
		dfs({ ny, nx }, cnt + 1);
		check[index] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);

	cin >> r >> c;
	memset(check, false, 26);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	}

	check[map[0][0] - 'A'] = true;
	dfs({ 0,0 }, 1);
	
	cout << ans;
	return 0;
}