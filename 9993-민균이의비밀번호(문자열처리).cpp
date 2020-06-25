/*
팰린드롬이면 자기자신이 정답임
반례)
3
level
xyz
d
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int N;
string pw[101];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> pw[i];
	}


	for (int i = 0; i < N; i++) {
		bool flag = true;
		for (int j = 0; j < pw[i].size(); j++) if (pw[i][j] != pw[i][pw[i].size() - j - 1])flag = false;
		if (flag) {
			cout << pw[i].size() << " ";
			cout << pw[i][pw[i].size() / 2];
			return 0;
		}
		reverse(pw[i].begin(), pw[i].end());
		for (int j = 0; j < N; j++) {
			if (i == j)continue;
			if (pw[i] == pw[j]) {
				cout << pw[i].size() << " ";
				cout << pw[i][pw[i].size()/2];
				return 0;
			}
		}
	}
	
	return 0;
}