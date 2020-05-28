/*
가까이 있는 적을 제거해야함 따라서 제거할수 있는 적의 후보를 모으고 한꺼번에 제거해야함
cmp함수 관련해서 가까이 있는적이 아니라 xpos가 가장 적고 ypos가 가장가까운 적을 골라 오답.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Pair {
	int ypos, xpos, dist;
};

bool cmp(const Pair &p1, const Pair &p2) {
	if (p1.dist < p2.dist)return true;
	else if (p1.dist == p2.dist)return p1.xpos < p2.xpos;
	else return false;
}

int N, M, D, ans, ar[17][17];
Pair arch[3];

void sol() {
	int map[17][17];
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)map[i][j] = ar[i][j];

	int score = 0;

	//적이 내려오는 횟수
	for (int t = 0; t < N; t++) {		
		//모아서 제거하기 위함
		vector<Pair> k;

		//공격
		for (int a = 0; a < 3; a++) {
			int ypos = arch[a].ypos, xpos = arch[a].xpos;

			vector<Pair> v;
			for (int i = 1; i <= D; i++) {
				for (int j = 0; j <= D - i; j++) {
					if(ypos - i >= 0 && xpos + j < M)if (map[ypos - i][xpos + j])v.push_back({ ypos - i, xpos + j, i + j });
					if(ypos - i >= 0 && xpos - j >= 0)if (map[ypos - i][xpos - j])v.push_back({ ypos - i, xpos - j, i + j });
				}
			}
			
			//가장 왼쪽 모음
			if (v.size()) {
				sort(v.begin(), v.end(), cmp);
				k.push_back({ v[0].ypos, v[0].xpos });
			}
		}

		//제거
		for (Pair p : k) {
			if (map[p.ypos][p.xpos]) {
				map[p.ypos][p.xpos] = 0;
				++score;
			}
		}

		int temp[16][16];
		for (int i = 0; i < M; i++)temp[0][i] = 0;
		for (int i = 1; i < N; i++) for (int j = 0; j < M; j++)temp[i][j] = map[i - 1][j];
		for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)map[i][j] = temp[i][j];
	}
	ans = ans < score ? score : ans;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> D;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> ar[i][j];
		}
	}

	
	for (int i = 0; i < M - 2; i++) {
		for (int j = i + 1; j < M - 1; j++) {
			for (int z = j + 1; z < M; z++) {
				arch[0] = { N, i };
				arch[1] = { N, j };
				arch[2] = { N, z };
				sol();
			}
		}
	}
	
	cout << ans;
	
	return 0;
}