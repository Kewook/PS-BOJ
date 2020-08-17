/*
오답
이유 : 문제를 잘못읽었다. 문제에서 모두 잠기지 않을 경우를 추가해야하는데 잠기지 않은 경우를 고려하지 않음
따라서 다음과 같이 소스를 짰는데 bfs에서 인덱스가 넘어가는 부분을 처리하지 않은 실수함.
(문제똑바로 읽자)

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };
int ar[100][100];
bool check[100][100];

typedef struct Pair {
	int ypos, xpos;
}Pair;

void bfs(int y, int x, int height) {
	Pair p = { y,x };
	queue<Pair> q;
	q.push(p);
	check[y][x] = true;
	
	while (!q.empty()) {
		int r = q.front().ypos;
		int c = q.front().xpos;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dy[i], nc = c + dx[i];

			if (ar[nr][nc] > height && !check[nr][nc]) {
				p = { nr, nc };
				q.push(p);
			}

			check[nr][nc] = true;
		}
	}

}

int main() {
	int n;
	vector<int> v;

	scanf("%d",&n);

	for (int i = 0; i < n; i++)memset(check[i], false, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &ar[i][j]);
			v.push_back(ar[i][j]);
		}
	}

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	v.push_back(v[0] - 1);

	int max = 0;
	for (int k = 0; k < v.size(); k++) {
		int cnt = 0;
		for (int z = 0; z < n; z++)memset(check[z], false, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ar[i][j] > v[k] && !check[i][j]) {
					bfs(i, j, v[k]);
					cnt++;
				}
			}
		}
		if (cnt > max)max = cnt;
	}

	printf("%d",max);
	
	return 0;
} */

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };
int ar[100][100];
bool check[100][100];

typedef struct Pair {
	int ypos, xpos;
}Pair;

void bfs(int y, int x, int height, int n) {
	Pair p = { y,x };
	queue<Pair> q;
	q.push(p);
	check[y][x] = true;

	while (!q.empty()) {
		int r = q.front().ypos;
		int c = q.front().xpos;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dy[i], nc = c + dx[i];

			if (nr < 0 || nr >= n || nc < 0 || nc >= n)continue;
			if (check[nr][nc])continue;

			if (ar[nr][nc] > height) {
				p = { nr, nc };
				q.push(p);
			}

			check[nr][nc] = true;
		}
	}

}

int main() {
	int n, max = 0;
	
	scanf("%d",&n);

	for (int i = 0; i < n; i++)memset(check[i], false, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &ar[i][j]);
			if (ar[i][j] > max)max = ar[i][j];
		}
	}

	int ans = 0;
	for (int k = 0; k <= max; k++) {
		int cnt = 0;
		for (int z = 0; z < n; z++)memset(check[z], false, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ar[i][j] > k && !check[i][j]) {
					bfs(i, j, k, n);
					cnt++;
				}
			}
		}
		if (cnt > ans)ans = cnt;
	}

	printf("%d",ans);
	
	return 0;
}