/*
위성수 S는 곧바로 연결이 가능하기 때문에 MST를 구성하다가 N-S만큼 간선을 추가하면 종료

주의사항 : 정답은 라디오를 통신할 수있는 D의 최소값이다.
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

struct Edge {
	int node1, node2;
	double cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

struct Pos {
	int xpos, ypos;
};

int T, S, N, parent[501];
Pos pos[501];
vector<Edge> edge;

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

double getDist(Pos &p1, Pos &p2) {
	return sqrt(pow(p1.xpos - p2.xpos, 2) + pow(p1.ypos - p2.ypos, 2));
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cout << fixed;
	cout.precision(2);

	cin >> T;

	while (T--) {
		cin >> S >> N;
		for (int i = 1; i <= N; i++)cin >> pos[i].xpos >> pos[i].ypos;
		
		edge.clear();
		for (int i = 1; i < N; i++) {
			for (int j = i + 1; j <= N; j++) {
				edge.push_back({ i,j, getDist(pos[i], pos[j]) });
			}
		}

		memset(parent, -1, sizeof(parent));
		sort(edge.begin(), edge.end());

		int cnt = 0;
		double cost;
		for (auto e : edge) {
			int pa = find(e.node1), pb = find(e.node2);
			
			if (pa != pb) {
				parent[pb] = pa;
				++cnt;
				cost = e.cost;
				if (cnt == N - S)break;
			}
		}
		cout << cost << "\n";
	}
	
	return 0;
}