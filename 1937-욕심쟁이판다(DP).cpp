/*
N이 500이므로 naive하게 풀이를 하면 500 *500 * 500 * 500의 시간복잡도가 필요하다.
따라서 DP를 이용해 가지치기를 줄여준다.

처음에는 팬더가 시작하는 칸마다 cache를 초기화해줘서 TLE를 받음
cache를 초기화해줄 필요가 없는 이유는 어차피 그 다음칸에서 가볼수있는 모든 경우의 수를 다 저장해놨기 때문에 초기화해줄 필요가 없다.
*/

////////////// top-down ////////////////
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int N, map[501][501], cache[501][501], ans;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };

int dfs(int ypos, int xpos) {
	int &ret = cache[ypos][xpos];
	if (ret != 0)return ret;

	ret = 1;
	for (int i = 0; i < 4; i++) {
		int ny = ypos + dy[i], nx = xpos + dx[i];
		if (ny < 1 || nx < 1 || ny > N || nx > N)continue;
		if (map[ypos][xpos] >= map[ny][nx])continue;

		ret = max(ret, dfs(ny, nx) + 1);
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	
	ans = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ans = max(ans, dfs(i, j));
		}
	}

	cout << ans;
	return 0;
}



////////////// bottom-up ////////////////
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Node {
	int ypos, xpos, val;

	bool operator < (const Node &ipt) {
		return val < ipt.val;
	}
};

int N, map[501][501], cache[501][501];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
vector<Node> node;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			cache[i][j] = 1;
			node.push_back({ i,j, map[i][j] });
		}
	}
	
	sort(node.begin(), node.end());
	
	int ans = 0;
	for (auto next : node) {
		int ypos = next.ypos, xpos = next.xpos;

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 1 || nx < 1 || ny > N || nx > N)continue;
			if (map[ypos][xpos] <= map[ny][nx])continue;
			cache[ypos][xpos] = max(cache[ypos][xpos], cache[ny][nx] + 1);
		}
		ans = max(ans, cache[ypos][xpos]);
	}

	cout << ans;
	return 0;
}