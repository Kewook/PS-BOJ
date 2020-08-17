/*
전체적인 패턴이 네개가 있다.
그냥 초기상태, 모두다 채워져있을때, 한번 터졌을때 두번째 터졌을때.
*/
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

typedef struct Pair {
	int ypos, xpos;
}Pair;

int main() {
	ios::sync_with_stdio(0);
	vector<Pair> v;

	int dy[] = { 1,-1,0,0 };
	int dx[] = { 0,0,1,-1 };

	char ar[203][203];
	int r, c, n;
	cin >> r >> c >> n;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char temp;
			cin >> temp;
			ar[i][j] = temp;
			if (temp == 'O') {
				Pair p = { i,j };
				v.push_back(p);
			}
		}
	}

	if (n == 1) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cout << ar[i][j];
			}cout << endl;
		}
		return 0;
	}

	else if (n % 2 == 0) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cout << "O";
			}cout << endl;
		}
		return 0;
	}

	else {
		for (int i = 0; i < r; i++)memset(ar[i], 'O', c);

		for (int i = 0; i < v.size(); i++) {
			int ypos = v[i].ypos, xpos = v[i].xpos;
			ar[ypos][xpos] = '.';
			for (int k = 0; k < 4; k++) {
				int ny = ypos + dy[k], nx = xpos + dx[k];
				if (ny < 0 || ny >= r || nx < 0 || nx >= c)continue;
				ar[ny][nx] = '.';
			}
		}

		v.clear();
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (ar[i][j] == 'O') {
					Pair p = { i,j };
					v.push_back(p);
				}
			}
		}


		if (n % 4 == 1) {
			for (int i = 0; i < r; i++)memset(ar[i], 'O', c);

			for (int i = 0; i < v.size(); i++) {
				int ypos = v[i].ypos, xpos = v[i].xpos;
				ar[ypos][xpos] = '.';
				for (int k = 0; k < 4; k++) {
					int ny = ypos + dy[k], nx = xpos + dx[k];
					if (ny < 0 || ny >= r || nx < 0 || nx >= c)continue;
					ar[ny][nx] = '.';
				}
			}
		}

		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cout << ar[i][j];
			}cout << endl;
		}
	}
	return 0;
}