/*
BFS와 비트마스킹을 이용한 문제

시간 계속 오래쓰고 풀었음 ==> dy, dx인덱스 잘못주고 풀어서 오래걸림.

이 문제에서 기억해야 할거는 비트마스킹인데 74번, 78번 비트마스킹을 이용한 백트래킹 스킬 기억해두자.
*/
#include<iostream>
#include<queue>
#include<cstring>

struct Info {
	int ypos, xpos;
};

using namespace std;

int N, M, nRoom, sRoom, dRoom;
int dy[] = { 0,-1,0,1 }, dx[] = { -1,0,1,0 };
int map[51][51];
bool check[51][51];

int bfs(Info info) {
	queue<Info> q;
	q.push(info);
	check[info.ypos][info.xpos] = true;

	int size = 1;
	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (map[ypos][xpos] & (1 << i)) continue;
			if (ny < 0 || nx < 0 || ny >= M || nx >= N)continue;
			if (check[ny][nx]) continue;
			check[ny][nx] = true;
			++size;
			q.push({ ny, nx });
		}
	}
	return size;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	nRoom = sRoom = dRoom = 0;

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j])continue;
			int size = bfs({ i,j });
			sRoom = sRoom < size ? size : sRoom;
			++nRoom;
		}
	}

	
	//한쪽만 뚫고 최대 넓이 갱신
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < 4; k++) {
				if (map[i][j] & (1 << k)) {
					map[i][j] &= ~(1 << k);
					memset(check, false, sizeof(check));
					int size = bfs({ i,j });
					dRoom = dRoom < size ? size : dRoom;
					map[i][j] |= (1 << k);
				}
			}
		}
	}
	cout << nRoom << "\n" << sRoom << "\n" << dRoom;
	return 0;
}