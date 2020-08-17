/*
재방문 표시를 check[999999999]으로 하려고했더니 메모리가 32MB임
자료구조를 사용하자 Map! ==> 방문하는 공간만 사용할 수 있다.
*/

#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<map>

using namespace std;

const int ANS = 123456780;

string str;
map<int, int> mp;
queue<string> q;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	str.resize(9);
	
	for (int i = 0; i < 9; i++) {
		int num;
		cin >> num;
		str[i] = num + '0';
	}
	
	int idx = str.find('0');
	q.push(str);
	mp[stoi(str)] = 1;
	
	int ans = 0;
	while (!q.empty()) {
		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			string num = q.front();
	
			if (stoi(num) == ANS) {
				cout << ans;
				return 0;
			}

			idx = num.find('0');
			int ypos = idx / 3, xpos = idx % 3;
			q.pop();

			for (int k = 0; k < 4; k++) {
				int ny = ypos + dy[k], nx = xpos + dx[k];
				if (ny < 0 || nx < 0 || ny >= 3 || nx >= 3)continue;

				string temp = num;
				swap(temp[idx], temp[ny * 3 + nx]);
				if (mp[stoi(temp)])continue;
				mp[stoi(temp)] = 1;
				q.push(temp);
			}
		}
		++ans;
	}

	cout << -1;
	return 0;
}