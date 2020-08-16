/*
문명 전파하고 합치는데 부모의 인덱스를 주는 과정에서 해맸다.
이것을 map[ny][nx]에 각 노드들의 부모를 저장하여 해결할 수 있다.
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct Pos {
	int ypos, xpos;
};

int N, K, gcnt, map[2001][2001], parent[4000005];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };;
queue<Pos> propa, merg;

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

//문명을 전파하는 과정
void propagation() {
	while (!propa.empty()) {
		int ypos = propa.front().ypos, xpos = propa.front().xpos;
		propa.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 1 || nx < 1 || ny>N || nx > N)continue;
            //전파가 되지 않은곳은 합쳐지는지 확인하기 위해 merg 큐에 넣어준다.
			if (!map[ny][nx]) {
				map[ny][nx] = map[ypos][xpos];
				merg.push(Pos{ ny, nx });
			}
		}
	}
}

//전파를 하고 합쳐지는지 확인하는 과정
void Merge() {
	while (!merg.empty()) {
		int ypos = merg.front().ypos, xpos = merg.front().xpos;
        //이 노드들은 모두 다시 전파되어야 한다.
		propa.push(merg.front());
		merg.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 1 || nx < 1 || ny>N || nx > N)continue;
            //전파가되었고 다른 문명이라면 합쳐져야 한다.
			if (map[ny][nx] && (map[ny][nx] != map[ypos][xpos])) {
				int pnow = find(map[ypos][xpos]), pnext = find(map[ny][nx]);
				if (pnow != pnext) {
                    //합쳐지면 문명의수가 하나 줄어든다.
					parent[pnext] = pnow;
					--gcnt;
				}
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> K;

	int a, b;
	for (int i = 1; i <= K; i++) {
		cin >> a >> b;
		map[a][b] = i;
		parent[i] = i;
		merg.push(Pos{ a,b });
		++gcnt;
	}

	int ans = 0;
	while (true) {
        //merge먼저 하는 이유는 이미 붙어있는 문명이 있을수도 있다.
		Merge();
		if (gcnt == 1)break;
		propagation();
		++ans;
	}
	
	cout << ans;
	return 0;
}