/*
틀린이유 : dfs로 풀면 일단 무조건 시간초과가 난다.
각 칸의 개수는 500*500 = 250000개이고 4가지 방향으로 갈수 있으니 최악의 탐색조건은 4^250000임.

처음에 풀었을 때는 dfs로 탐색을하고 탐색이 가능한 위치는 dp배열을 전부 1로 해주었다.
하지만 이렇게 하면 목적지에 도달하지 못해도 1이 계속 저장되는 오류

시간초과 이유 : dp배열을 -1로 초기화하지않고 하면 탐색을 이미 햇는데 목적지로 가지 못한 점을 재탐색 하는 경우가 생긴다.
이걸 없애주기 위해 한번 탐색한 위치는 전부 0으로 바꿔준다.
*/

#include<iostream>
#include<cstring>

using namespace std;

int N, M;
int dp[505][505], ar[505][505];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };

int dfs(int ypos, int xpos) {
	if (ypos == N && xpos == M) return 1;

	if (dp[ypos][xpos] != -1) return dp[ypos][xpos];

	dp[ypos][xpos] = 0;
	for (int i = 0; i < 4; i++) {
		int ny = ypos + dy[i], nx = xpos + dx[i];
		if (ny < 1 || nx < 1 || ny > N || nx > M)continue;
		if (ar[ny][nx] < ar[ypos][xpos]) dp[ypos][xpos] += dfs(ny, nx);
	}
	
	return dp[ypos][xpos];
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> ar[i][j];
		}
	}

	cout << dfs(1, 1);
	
	return 0;
}