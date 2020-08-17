/*
구현력을 기르자 move부분을 구현을 못했다.
*/
#include<iostream>
#include<queue>

using namespace std;
int n, maxnum = 0;
int ar[21][21];

void move(int dir) {
	queue<int> q;

	switch (dir) {
	case 0:
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ar[i][j])q.push(ar[i][j]);
				ar[i][j] = 0;
			}
			int idx = 0;

			while (!q.empty()) {
				int num = q.front();
				q.pop();
				if (ar[i][idx] == 0)ar[i][idx] = num;
				else if (ar[i][idx] == num) {
					ar[i][idx] *= 2;
					idx++;
				}
				else {
					ar[i][++idx] = num;
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j >= 0; j--) {
				if (ar[i][j])q.push(ar[i][j]);
				ar[i][j] = 0;
			}
			int idx = n - 1;
			while (!q.empty()) {
				int num = q.front();
				q.pop();

				if (ar[i][idx] == 0)ar[i][idx] = num;
				else if (ar[i][idx] == num) {
					ar[i][idx] *= 2;
					idx--;
				}
				else ar[i][--idx] = num;
			}
		}
		break;
	case 2:
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (ar[j][i])q.push(ar[j][i]);
				ar[j][i] = 0;
			}
			int idx = 0;
			while (!q.empty()) {
				int num = q.front();
				q.pop();
				if (ar[idx][i] == 0)ar[idx][i] = num;
				else if (ar[idx][i] == num) {
					ar[idx][i] *= 2;
					idx++;
				}
				else ar[++idx][i] = num;
			}
		}
		break;
	case 3:
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j >= 0; j--) {
				if (ar[j][i])q.push(ar[j][i]);
				ar[j][i] = 0;
			}
			int idx = n - 1;
			while (!q.empty()) {
				int num = q.front();
				q.pop();
				if (ar[idx][i] == 0)ar[idx][i] = num;
				else if (ar[idx][i] == num) {
					ar[idx][i] *= 2;
					idx--;
				}
				else ar[--idx][i] = num;
			}
		}
		break;
	}

}
void sol(int idx) {
	
	if (idx == 5) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				maxnum = maxnum < ar[i][j] ? ar[i][j] : maxnum;
			}
		}
		return;
	}

	int temp[21][21];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)temp[i][j] = ar[i][j];
	}

	for (int i = 0; i < 4; i++) {
		move(i);
		sol(idx + 1);

		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++)ar[j][k] = temp[j][k];
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ar[i][j];
			maxnum = maxnum < ar[i][j] ? ar[i][j] : maxnum;
		}
	}
	sol(0);

	cout << maxnum;
	
	return 0;
}