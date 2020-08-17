/*
탐색 + dp문제
만약 네가지 숫자가 모두 같으면 무한루프가 생길 수 있으니 사이클이 생기는지 확인해야 한다.
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

int N, M, map[51][51], cache[51][51];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[51][51];

int sol(int ypos, int xpos) {
	if (ypos < 0 || xpos < 0 || ypos >= N || xpos >= M || !map[ypos][xpos])return 0;
    //사이클이 생기는지 확인
	if (check[ypos][xpos]) {
		cout << -1;
		exit(0);
	}

	int &ret = cache[ypos][xpos];
	if (ret != -1)return ret;
	
	for (int i = 0; i < 4; i++) {
		check[ypos][xpos] = true;
		ret = max(ret, sol(ypos + dy[i] * map[ypos][xpos], xpos + dx[i] * map[ypos][xpos]) + 1);
		check[ypos][xpos] = false;
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	
	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		for (int j = 0; j < M;j++) {
			map[i][j] = str[j] == 'H' ? 0 : str[j] - '0';
		}
	}
	
	memset(cache, -1, sizeof(cache));
	cout << sol(0, 0);
	return 0;
}