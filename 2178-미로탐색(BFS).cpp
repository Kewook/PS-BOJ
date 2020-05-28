//bfs로 최단거리를 구하는것은 알고있었지만 실제로 어떻게 해야하는지 모름
//따라서 인터넷 검색후 큐의 사이즈를 체크해가면서 그만큼 while문을 돌려준다면 탐색트리의 깊이를 잴수 있다.

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int n, m;
bool matrix[100][100];
bool check[100][100];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

typedef struct Pair {
	int xpos, ypos;
}Pair;

int bfs(int x, int y) {
	int cnt = 1;
	queue<Pair> q;
	Pair p = { x,y };
	q.push(p);

	while (!q.empty()) {
		int size = q.size();

		for (int i = 0; i < size; i++) {
			int xpos = q.front().xpos;
			int ypos = q.front().ypos;
			q.pop();

			if (xpos == n - 1 && ypos == m - 1) {
				return cnt;
			}
			
			for (int j = 0; j < 4; j++) {
				int nx, ny;
				nx = xpos + dx[j];
				ny = ypos + dy[j];
				if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
				if (check[nx][ny] || !matrix[nx][ny])continue;
				check[nx][ny] = true;
				p = { nx, ny };
				q.push(p);
			}
		}
		cnt++;
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)memset(check, false, m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			matrix[i][j] = c - '0';
		}
	}

	check[0][0] = true;
	int cnt = bfs(0, 0);
	printf("%d",cnt);
	
	return 0;
}