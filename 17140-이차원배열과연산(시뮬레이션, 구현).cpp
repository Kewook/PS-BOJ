/*
구현력 딸릴때 풀어보자
*/

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Info {
	int count, num;

	bool operator < (const Info &i) {
		if (count == i.count)return num < i.num;
		else return count < i.count;
	}
};

int R, C, K, A[105][105];
int rsize, csize;

void move(int mode) {
	Info freq[101];
	int R, C;

	if (mode == 0) R = rsize, C = csize;
	else R = csize, C = rsize;

	int Maxsize = 0;

	for (int i = 1; i <= R; i++) {
		for (int j = 0; j <= 100; j++) freq[j] = { 0,j };

		for (int j = 1; j <= C; j++) {
			if (mode == 0) {
				freq[A[i][j]].count++;
				A[i][j] = 0;
			}
			else {
				freq[A[j][i]].count++;
				A[j][i] = 0;
			}
		}
		sort(freq, freq + 101);

		int idx = 1;
		for (int j = 0; j <= 100; j++) {
			if (freq[j].count == 0 || freq[j].num == 0)continue;
			if (mode == 0) {
				A[i][idx++] = freq[j].num;
				A[i][idx++] = freq[j].count;
			}
			else {
				A[idx++][i] = freq[j].num;
				A[idx++][i] = freq[j].count;
			}
			if (idx > 100)break;
		}
		Maxsize = Maxsize < idx ? idx : Maxsize;
	}

	if (mode == 0)csize = Maxsize - 1;
	else rsize = Maxsize - 1;
}

void sol(int cnt) {
	if (A[R][C] == K) {
		cout << cnt;
		return;
	}
	if (cnt > 100) {
		cout << -1;
		return;
	}

	if (rsize >= csize) move(0);
	else move(1);
	sol(cnt + 1);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C >> K;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++)cin >> A[i][j];
	}

	rsize = csize = 3;
	sol(0);

	return 0;
}