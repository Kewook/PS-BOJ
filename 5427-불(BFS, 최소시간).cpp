/*
틀린이유 1. 예를들어 상근이의 첫 위치가 가장 바깥쪽, 바로 탈출할수 잇는 위치로 주어졌을때 1을 출력하지않고 다른 값을 출력함.
틀린이유 2. ny, nx를 가지고 탈출 여부를 판단하여 flag 를 true로 수정하였으나 flag가 true로 수정이 되면 더 탐색하지 않고 끝내게 함.
*/

#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Info {
	int ypos, xpos;
};

int W, H;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
char map[1001][1001];
bool check[1001][1001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for (int t = 1; t <= T; t++) {
		memset(check, false, sizeof(check));
		queue<Info> q, fire;

		cin >> W >> H;
		
		bool flag = false;

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
				if (map[i][j] == '@') {
					q.push({ i,j });
					check[i][j] = true;
					map[i][j] = '.';
				}
				else if (map[i][j] == '*')fire.push({ i,j });
			}
		}

		for (int k = 0; k < 4; k++) {
			int ny = q.front().ypos + dy[k], nx = q.front().xpos + dx[k];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W) {
				cout << 1 << "\n";
				q.pop();
				break;
			}
		}
		if (q.empty())continue;
		
		int ans = 0;
		while (!q.empty()) {
			int qsize = fire.size();

			for (int i = 0; i < qsize; i++) {
				int ypos = fire.front().ypos, xpos = fire.front().xpos;
				fire.pop();

				for (int k = 0; k < 4; k++) {
					int ny = ypos + dy[k], nx = xpos + dx[k];
					if (ny < 0 || nx < 0 || ny >= H || nx >= W)continue;
					if (map[ny][nx] != '.')continue;
					fire.push({ ny, nx });
					map[ny][nx] = '*';
				}
			}
			
			qsize = q.size();

			for (int i = 0; i < qsize; i++) {
				int ypos = q.front().ypos, xpos = q.front().xpos;
				q.pop();
				
				for (int k = 0; k < 4; k++) {
					int ny = ypos + dy[k], nx = xpos + dx[k];
					if (ny < 0 || nx < 0 || ny >= H || nx >= W) {
						flag = true;
						break;
					}
					if (check[ny][nx] || map[ny][nx] != '.')continue;
					check[ny][nx] = true;
					q.push({ ny, nx });
				}
			}
			++ans;
			if (flag)break;
			
		}
		if (flag) {
			cout << ans << "\n";
			continue;
		}
		if (!flag) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
	}

	return 0;
}