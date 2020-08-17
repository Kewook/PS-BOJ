/*
node의 수가 100000이다. 만약 O(N^2)으로 간선을 뽑아내면 시간초과
하지만 두 행성의 거리의 조건이 min(|X1 - X2|, |Y1 - Y2|, |Z1 - Z2|)이므로 정렬을 이용하여 좌표상 거리가 가까워 MST가 되기 위한 후보 간선을 뽑을 수 있다.
x, y, z좌표 순으로 정렬을 하여 인접한 행성들로만 edge를 구성해준다.
이때 cost는 다르지만 행성이 같은 경우가 생기는데 이는 크루스칼 알고리즘을 수행할때 cost가 높은 간선은 뒤로 밀려나서 해결가능하다.
이때 주의해야할 점은 정렬을 하고 그 인덱스를 노드번호로 사용하면 disjoint-set을 이용할때 부모 간선에 혼동이 생길 수 있다.
따라서 idx를 미리 저장해두어 해결한다.
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

struct Pos {
	int idx, xpos, ypos, zpos;
};

int N, parent[100001];
Pos pos[100001];
vector<Edge> edge;


int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

bool cmpX(Pos &p1, Pos &p2) { return p1.xpos < p2.xpos; }
bool cmpY(Pos &p1, Pos &p2) { return p1.ypos < p2.ypos; }
bool cmpZ(Pos &p1, Pos &p2) { return p1.zpos < p2.zpos; }


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> pos[i].xpos >> pos[i].ypos >> pos[i].zpos, pos[i].idx = i;
	
	sort(pos, pos + N, cmpX);
	for (int i = 0; i < N - 1; i++)edge.push_back({ pos[i].idx, pos[i + 1].idx, abs(pos[i].xpos - pos[i + 1].xpos) });
	sort(pos, pos + N, cmpY);
	for (int i = 0; i < N - 1; i++)edge.push_back({ pos[i].idx, pos[i + 1].idx, abs(pos[i].ypos - pos[i + 1].ypos) });
	sort(pos, pos + N, cmpZ);
	for (int i = 0; i < N - 1; i++)edge.push_back({ pos[i].idx, pos[i + 1].idx, abs(pos[i].zpos - pos[i + 1].zpos) });
	
	memset(parent, -1, sizeof(parent));
	sort(edge.begin(), edge.end());

	int cnt = 0;
	long long cost = 0;

	for (auto e : edge) {
		int pa = find(e.node1), pb = find(e.node2);
		
		if (pa != pb) {
			parent[pb] = pa;
			cost += e.cost;
			if (++cnt == N - 1)break;
		}
	}
	
	cout << cost;
	return 0;
}