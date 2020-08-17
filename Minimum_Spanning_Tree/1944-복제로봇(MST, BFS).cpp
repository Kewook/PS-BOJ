/*
Logic
1. 시작지점 S와 키가 있는지점 K에 번호와 위치를 기억해준다.
2. 각 노드를 돌면서 모든 노드가 연결이 되는지 확인한다.
3. MST를 구성해준다.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

struct Edge {
	int node1, node2, cost;

	bool operator < (const Edge &ipt) {
		return cost < ipt.cost;
	}
};

struct Pos {
	int ypos, xpos, cnt;
};

int N, M, node[51][51], parent[251];
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
char map[51][51];
vector<Pos> pos;
vector<Edge> edge;

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

bool bfs(Pos p) {
	queue<Pos> q;
	bool check[51][51];
	int nnode = 1;

	memset(check, false, sizeof(check));
	check[p.ypos][p.xpos] = true;
	q.push(p);

	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos, cnt = q.front().cnt;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			if (check[ny][nx] || map[ny][nx] == '1')continue;
			if (map[ny][nx] == 'S' || map[ny][nx] == 'K') {
				++nnode;
				if (node[ny][nx] > node[p.ypos][p.xpos]) edge.push_back({ node[p.ypos][p.xpos] , node[ny][nx], cnt + 1 });
			}
			q.push({ ny, nx, cnt + 1 });
			check[ny][nx] = true;
		}
	}

    //모든 노드와 연결이 가능하면 분리된 노드가 아니다
	if (nnode == pos.size())return true;
	else return false;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'S' || map[i][j] == 'K') {
				pos.push_back({ i,j,0 });
				node[i][j] = pos.size() - 1;
			}
		}
	}

	for (auto n : pos) {
		if (!bfs(n)) {
			cout << -1;
			return 0;
		}
	}

	memset(parent, -1, sizeof(parent));
	sort(edge.begin(), edge.end());

	int cnt = 0, cost = 0;
	for (auto e : edge) {
		int pa = find(e.node1), pb = find(e.node2);

		if (pa != pb) {
			parent[pb] = pa;
			cost += e.cost;
			if (++cnt == pos.size() -1)break;
		}
	}

	cout << cost;
	return 0;
}