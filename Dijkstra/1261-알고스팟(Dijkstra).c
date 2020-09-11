#include <stdio.h>
#include <string.h>
#define MAX 102

struct Pos {
	int ypos, xpos;
}q[MAX*MAX*MAX];

int N, M, map[MAX][MAX];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };

int bfs() {
	int top, end, dist[MAX][MAX];
	memset(dist, 0x3f, sizeof dist);

	top = end = -1;
	q[++end].ypos = 0; q[end].xpos = 0; dist[0][0] = 0;

	while (top != end) {
		int ypos = q[++top].ypos, xpos = q[top].xpos;

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny >= M || nx >= N)continue;
			int cost = dist[ypos][xpos] + map[ny][nx];
			if (cost < dist[ny][nx]) {
				q[++end].ypos = ny; q[end].xpos = nx;
				dist[ny][nx] = cost;
			}
		}
	}
	return dist[M - 1][N - 1];
}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) {
		char str[MAX];
		scanf("%s", &str);
		for (int j = 0; j < N; j++) {
			map[i][j] = str[j] - '0';
		}
	}

	printf("%d", bfs());
	return 0;
}