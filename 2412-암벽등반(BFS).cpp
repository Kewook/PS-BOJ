/*
BFS의 시간을 줄이기 위해 idx를 기억해두고 그 idx에서부터 시작해서 탐색한다. 그러려면 sorting이 필요
하지만 xpos가 같을시 ypos를 오름차순으로 정렬해주어야 하는데 그걸 안해줘서 틀림.
*/

#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>

using namespace std;

struct Pos {
	int xpos, ypos, idx;
	
	bool operator < (const Pos &p) {
		if (xpos == p.xpos)return ypos < p.ypos;
		else return xpos < p.xpos;
	}
};

int N, T;
bool check[50005];
Pos pos[50005];


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> T;
	
	pos[0] = { 0,0 };
	for (int i = 1; i <= N; i++) {
		cin >> pos[i].xpos >> pos[i].ypos;
	}
	
	sort(pos, pos + N + 1);
	
	queue<int> q;
	q.push(0);
	check[0] = true;

	int dist = 1;
	while (!q.empty()) {
		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			int idx = q.front();
			q.pop();

			if (pos[idx].ypos == T) {
				cout << dist - 1;
				return 0;
			}

			for (int j = idx + 1; j <= N; j++) {
				if (check[j])continue;
				if (abs(pos[j].xpos - pos[idx].xpos) > 2)break;
				if (abs(pos[j].ypos - pos[idx].ypos) > 2)continue;
				check[j] = true;
				q.push(j);				
			}

			for (int j = idx - 1; j > 0; j--) {
				if (check[j])continue;
				if (abs(pos[j].xpos - pos[idx].xpos) > 2)break;
				if (abs(pos[j].ypos - pos[idx].ypos) > 2)continue;
				check[j] = true;
				q.push(j);
			}
		}
		++dist;
	}
	
	cout << -1;
	return 0;
}