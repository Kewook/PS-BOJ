/*
1. isTrue 부분에서 거리를 벗어날경우 overflow 체크 안해줌
2. paper배열 조작할때 인덱스 잘못 줌.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Pair {
	int ypos, xpos, flag;
};

int ar[11][11], paper[5], ans;
bool check[11][11];
vector<Pair> v;

bool isTrue(int ypos, int xpos, int len) {
	if (ypos + len > 10 || xpos + len > 10)return false;

	for (int i = ypos; i < ypos + len; i++) {
		for (int j = xpos; j < xpos + len; j++) {
			if (check[i][j] || !ar[i][j]) {
				return false;
			}
		}
	}

	return true;
}

void dfs(int idx) {
	if (idx == v.size()) {
		int sum = 25;
		for (int i = 0; i < 5; i++) {
			sum -= paper[i];
		}
		ans = ans > sum ? sum : ans;
		return;
	}
	
	int ypos = v[idx].ypos, xpos = v[idx].xpos;
	if (check[ypos][xpos]) dfs(idx + 1);

	else {
		for (int i = 5; i >= 1; i--) {
			if (paper[i - 1] && isTrue(ypos, xpos, i)) {
				for (int r = ypos; r < ypos + i; r++) for (int c = xpos; c < xpos + i; c++) check[r][c] = true;
				--paper[i - 1];

				dfs(idx + 1);

				for (int r = ypos; r < ypos + i; r++) for (int c = xpos; c < xpos + i; c++) check[r][c] = false;
				++paper[i - 1];
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	ans = 987654321;
	fill(paper, paper + 5, 5);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> ar[i][j];
			if (ar[i][j]) v.push_back({ i,j });
		}
	}

	dfs(0);

	if (ans == 987654321)cout << -1;
	else cout << ans;

	return 0;

}