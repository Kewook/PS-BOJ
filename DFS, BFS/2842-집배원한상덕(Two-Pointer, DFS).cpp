/*
투포인터를 이용해서 문제를 해결할 수 있다.
예를들어 최소높이 low와 최대높이 h사이의 지형만 지나갈 수 있다고 생각하고 dfs탐색을한다. 그리고 모든 K가 방문이 될 시에 가장 최소 피로도를 갱신해준다.
따라서 height정보를 오름차순으로 정렬하고 [l, r]구간의 높이의 지형만 지나간다고 가정한다.

1. 만약 [l, r]구간으로 모든 K를 방문가능하다면 ans를 갱신한다. 그리고 더 낮은 ans가 있는지 확인하기 위해 l을 한칸 늘려준다.
2. 만약 모든 K를 방문 못한다면 지나갈 수 있는 최대 height를 늘려줘야 한다. 따라서 r을 한칸 늘려준다.
3. 루프가 끝나는 기저사례는 r이 마지막에 다다렀을때 끝내야 한다. l이 끝나는 조건으로 했을때는 r이 boundary를 벗어난다.

어차피 N*N-1에 r이 걸려있을때 l은 모든 방문이 가능해질 때까지 커진다.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, l, r, sy, sx, ans, height[51][51];
int dy[] = { 0,-1,-1,-1,0,1,1,1 }, dx[] = { 1,1,0,-1,-1,-1,0,1 };
vector<int> v;
char map[51][51];
bool check[51][51];

void dfs(int ypos, int xpos) {	
	for (int i = 0; i < 8; i++) {
		int ny = ypos + dy[i], nx = xpos + dx[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N || check[ny][nx])continue;
		if (height[ny][nx] < v[l] || v[r] < height[ny][nx])continue;
		check[ny][nx] = true;
		dfs(ny, nx);
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	char c;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> c;
			map[i][j] = c;
			if (map[i][j] == 'P')sy = i, sx = j;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> height[i][j];
			v.push_back(height[i][j]);
		}
	}
	
	ans = 1e10;
	sort(v.begin(), v.end());
	while (r < N*N) {
        if(height[sy][sx] < v[l] || v[r] < height[sy][sx]){
            r++;
            continue;
        }
		check[sy][sx] = true;
		dfs(sy, sx);
		
		bool flag = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 'K' && !check[i][j]) flag = false;
				check[i][j] = false;
			}
		}
		
		if (flag) {
			ans = min(ans, v[r] - v[l]);
			l++;
		}
		else r++;
	}
	
	cout << ans;
	return 0;
}