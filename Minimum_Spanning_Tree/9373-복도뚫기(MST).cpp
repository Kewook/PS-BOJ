/*
처음에는 왜 MST 문제인지 몰랐었다.
하지만 모든 원과 벽에 부딪히지않고 통과하면 가능하다고 생각하면 이해가 된다.

따라서 벽과 각 센서를 노드로 생각하고 노드간 cost를 반지름을 제외한 센서간 거리로 칭한다.
그리고 노드를 통과하는 MST를 구성하면 부딪히지 않고 통과할수 있다.

MST를 구성할때 끝내는 조건을 왼쪽벽과 오른쪽 벽이 같은 집합일때 종료를 해주었는데
이는 굳이 모든 센서를 포함해야할 필요가 없기 때문이다.

=> 로직떠오릴때 센서와 벽사이의 간선을 구해준다고 생각했지 모든 센서를 포함해야 한다고 생각했다.
*/

#include<iostream>
#include<algorithm>
#include<vector>
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
	int x, y, r;
};

int T, W, N, parent[1005];
Pos pos[1005];
vector<Edge> edge;

double getDist(Pos &p1, Pos &p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) - p1.r - p2.r;
}

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cout << fixed;
	cout.precision(6);

	cin >> T;
	while (T--) {
		cin >> W >> N;
		for (int i = 1; i <= N; i++)cin >> pos[i].x >> pos[i].y >> pos[i].r;

		edge.clear();

        //왼쪽벽과 오른쪽 벽의 edge 추가
		edge.push_back({ 0, N + 1, (double)W });
		for (int i = 1; i <= N; i++) {
			parent[i] = i;

            //센서에서 왼쪽, 오른쪽 벽까지의 edge 추가
			edge.push_back({ 0,i, max(0.0, (double)pos[i].x - pos[i].r) });
			edge.push_back({ i,N + 1, max(0.0, (double)W - pos[i].x - pos[i].r) });

            //각 센서끼리 edge 추가
			for (int j = i + 1; j <= N; j++) edge.push_back({ i,j, max(0.0, getDist(pos[i],pos[j])) });
		}

		parent[0] = 0;
		parent[N + 1] = N + 1;
		sort(edge.begin(), edge.end());

		for (auto e : edge) {
			int pa = find(e.node1), pb = find(e.node2);
			
			if (pa != pb) {
				parent[pb] = pa;
				
                //왼쪽벽과 오른쪽벽을 모두 이었다면 통과가능
				if (find(0) == find(N+1)) {
					cout << e.cost / 2 << "\n";
					break;
				}
			}
		}
	}
	
	return 0;
}