/*
문제 한 번 복습해주자.
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

struct Pair {
	int ypos, xpos;
};

int n;
vector<int> adj[105];
bool check[105];

void dfs(int idx) {
	check[idx] = true;
	if (idx == n + 2)return;

	for (int next : adj[idx]) {
		if (check[next])continue;
		dfs(next);
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	for (int T = 1; T <= t; T++) {
		cin >> n;
		
		//초기화
		for (int i = 1; i <= 102; i++)adj[i].clear();
		memset(check, false, sizeof(check));

		Pair conv[105];
		for (int i = 1; i <= n + 2; i++) {
			cin >> conv[i].xpos >> conv[i].ypos;
		}
		
		for (int i = 1; i < n + 2; i++) {
			for (int j = i + 1; j <= n + 2; j++) {
				//맨해튼 거리
				int distance = abs(conv[i].xpos - conv[j].xpos) + abs(conv[i].ypos - conv[j].ypos);
				//거리가 맥주 20병으로 갈수 있는 거리라면 인접행렬에 추가.
				if (distance <= 20 * 50) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}
        
		dfs(1);

		if (check[n + 2])cout << "happy\n";
		else cout << "sad\n";
	}

	return 0;
}