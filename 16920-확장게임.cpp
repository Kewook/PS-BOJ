/*
확장이 한단계씩 늘어날때마다 check를 해주면 안된다.
다른 번호가 check가 되어 갈수있음에도 불구하고 가려지면 못간다.

ex)
5 10 4
1 2 1 2
1........2
.....44...
......4...
2.........
....3.....
output : 5 21 4 20
 */
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;


typedef struct Pair {
	int ypos, xpos, cnt;
}Pair;

int n, m, p, s[10], ans[10];
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
char ar[1001][1001];
queue<Pair> q[10];

bool sol(int idx) {
	bool test = false;
	queue<Pair> tempQ;
	tempQ = q[idx];
	
	while (!tempQ.empty()) {
		int ypos = tempQ.front().ypos;
		int xpos = tempQ.front().xpos;
		int cnt = tempQ.front().cnt;
		tempQ.pop();

		if (cnt == s[idx])q[idx].pop();
		
		if (cnt > 0) {
			for (int i = 0; i < 4; i++) {
				int ny = ypos + dy[i], nx = xpos + dx[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m)continue;
				if (ar[ny][nx] != '.')continue;

				ar[ny][nx] = idx + '0';
				tempQ.push({ ny, nx, cnt - 1 });
				q[idx].push({ ny, nx, s[idx] });
				ans[idx]++;
				test = true;
			}
		}
	}

	return test;
}

int main(void) {
	ios::sync_with_stdio(0);
	bool flag[10];

	cin >> n >> m >> p;
	memset(ans, 0, sizeof(int)*p + 1);
	memset(flag, true, p + 1);

	for (int i = 1; i <= p; i++)cin >> s[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> ar[i][j];
			if (ar[i][j] >= '1' && ar[i][j] <= '9') {
				q[ar[i][j] - '0'].push({ i,j, s[ar[i][j] - '0'] });
				ans[ar[i][j] - '0']++;
			}
		}
	}
	
	while (true) {
		
		for (int i = 1; i <= p; i++) {
			if (flag[i]) flag[i] = sol(i);
		}

		bool check = true;
		for (int i = 1; i <= p; i++) if (flag[i])check = false;
		if (check)break;
	}
	
	for (int i = 1; i <= p; i++)cout << ans[i] << " ";

	return 0;
}