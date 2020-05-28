/*
틀린이유
1. exit(1); 로 해주면 런타임 오류가 뜬다.
2. 문제를 제대로 안읽었다. 가만히 서있을수도 있다. 그래서 dy[], dx[] 0,0도 추가해야함
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Info {
	int ypos, xpos;
};

vector<Info> wall;
char map[10][10];
int dy[] = { 0,1,-1,0,0,1,-1, 1,-1 };
int dx[] = { 0,0,0,1,-1,1,1, -1,-1 };
bool check[10][10];

void fall(int dir) {
	vector<Info> v;

	for (int i = 0; i < wall.size(); i++) {
		int ypos = wall[i].ypos, xpos = wall[i].xpos;
		
		if (ypos <= 7 && ypos >= 0)map[ypos][xpos] = '.';
		if (ypos + dir <= 7 && ypos + dir >= 0)v.push_back({ ypos + dir, xpos });
		wall[i].ypos += dir;
	}
	
	for (int i = 0; i < v.size(); i++) {
		map[v[i].ypos][v[i].xpos] = '#';
	}
}
void dfs(int ypos, int xpos) {
	if (ypos == 0 && xpos == 7) {
		cout << 1;
		exit(0);
	}


	fall(1);
	if (map[ypos][xpos] != '#') {
		for (int i = 0; i < 9; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny >= 8 || nx >= 8)continue;
			if (map[ny][nx] == '#' || check[ny][nx])continue;
			check[ny][nx] = true;
			dfs(ny, nx);
			check[ny][nx] = false;
		}
	}
	fall(-1);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#')wall.push_back({ i,j });
		}
	}

	
	for (int i = 0; i < 9; i++) {
		int ny = 7 + dy[i], nx = 0 + dx[i];
		if (ny < 0 || nx < 0 || ny >= 8 || nx >= 8)continue;
		if (map[ny][nx] == '#' || check[ny][nx])continue;
		check[ny][nx] = true;
		dfs(ny, nx);
		check[ny][nx] = false;
	}
	
	cout << 0;

	return 0;
}