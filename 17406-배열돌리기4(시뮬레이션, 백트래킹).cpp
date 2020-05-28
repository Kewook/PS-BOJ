/*
연산을 하지 않았을때 ans의 값을 지정해주면 안된다. 초기 배열의 값으로 최소값을 찾아주면 안된다.
*/
#include<iostream>

using namespace std;

struct Pair {
	int r, c, s;
};

int n, m, k;
int test[55][55], ans, path[7];
Pair op[7];
bool check[7];


void sol() {
	int ar[55][55];
	for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)ar[i][j] = test[i][j];

	for (int z = 1; z <= k; z++) {
		int r = op[path[z]].r, c = op[path[z]].c, s = op[path[z]].s;

		int temp[55][55];
		for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)temp[i][j] = ar[i][j];

		//껍질안에서 한번에 움직이는 개수
		int num = 2 * s;

		for (int t = 0; t < s; t++) {
			int ypos = r - s + t, xpos = c - s + t;
			for (int i = 0; i < num; i++) {
				temp[ypos][xpos + 1] = ar[ypos][xpos];
				xpos++;
			}

			ypos = r - s + t, xpos = c + s - t;
			for (int i = 0; i < num; i++) {
				temp[ypos + 1][xpos] = ar[ypos][xpos];
				ypos++;
			}

			ypos = r + s - t, xpos = c + s - t;
			for (int i = 0; i < num; i++) {
				temp[ypos][xpos - 1] = ar[ypos][xpos];
				xpos--;
			}

			ypos = r + s - t, xpos = c - s + t;
			for (int i = 0; i < num; i++) {
				temp[ypos - 1][xpos] = ar[ypos][xpos];
				ypos--;
			}
			num -= 2;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				ar[i][j] = temp[i][j];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		int sum = 0;
		for (int j = 1; j <= m; j++) {
			sum += ar[i][j];
		}
		ans = ans > sum ? sum : ans;
	}
}

void dfs(int idx) {
	if (idx > k) {
		sol();
		return;
	}

	for (int i = 1; i <= k; i++) {
		if (check[i])continue;
		check[i] = true;
		path[idx] = i;
		dfs(idx + 1);
		check[i] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> k;
	ans = 987654321;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> test[i][j];
		}
	}

	for (int i = 1; i <= k; i++) {
		int r, c, s;
		cin >> op[i].r >> op[i].c >> op[i].s;
	}

	dfs(1);

	cout << ans;
	return 0;
}