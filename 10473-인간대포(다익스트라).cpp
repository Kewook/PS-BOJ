/*
cannon[1] : 출발위치
cannon[2 ~ N + 1] : 대포위치
cannon[N + 2] : 도착위치

다익스트라를 이용한다
그래프를 생성할때 각 지점에서 다른 지점의 거리를 모두 계산해서 만들어준다.
이때 대포를 타고 그지점에서 걸어가는것과 대포를 타지않고 그냥 걸어가는 cost를 비교해서 계산한다.
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

struct Info {
	int node;
	float cost;

	bool operator < (const Info &ipt)const {
		return cost > ipt.cost;
	}
};

struct Pos {
	float xpos, ypos;
};

const float INF = 987654321;

int N;
float dist[105];
Pos S, E, cannon[105];
vector<Info> adj[105];

float getDist(int node1, int node2) {
	return sqrt(pow(cannon[node1].xpos - cannon[node2].xpos, 2) + pow(cannon[node1].ypos - cannon[node2].ypos, 2));
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> S.xpos >> S.ypos >> E.xpos >> E.ypos >> N;
	cannon[1] = S;
	cannon[N + 2] = E;

	for (int i = 2; i <= N + 1; i++)cin >> cannon[i].xpos >> cannon[i].ypos;

    //출발지에서는 무조건 걸어가야하므로 걷는시간으로 계산
	for(int i = 2;i<= N+2;i++) adj[1].push_back({ i, getDist(1,i) / 5 });

	for (int i = 2; i <= N + 1; i++) {
		for (int j = 2; j <= N + 2; j++) {
			if (i == j)continue;
			float tdist = getDist(i, j);
            
            //50보다 적다면 대포를 타고 가는것과 그냥 걸어가는 것의 차이를 구해줌
			if (tdist < 50) {
				float walk = tdist / 5, jump = 2 + (50 - tdist) / 5;
				walk > jump ? adj[i].push_back({ j,jump }) : adj[i].push_back({ j,walk });
			}
            //50이상이면 무조건 대포 타고가는게 좋음
			else {
				if (tdist > 50)adj[i].push_back({ j, 2 + (tdist - 50) / 5 });
				else adj[i].push_back({ j, tdist / 5 });
			}
		}
	}

	for (int i = 2; i <= N + 2; i++)dist[i] = INF;

	priority_queue<Info> pq;
	pq.push({ 1, 0 });
	dist[1] = 0;

    //dijkstra
	while (!pq.empty()) {
		int node = pq.top().node;
		float cost = pq.top().cost;
		pq.pop();

		if (dist[node] < cost)continue;

		for (Info &iter : adj[node]) {
			int next = iter.node;
			float ncost = iter.cost;
			if (dist[next] > dist[node] + ncost) {
				dist[next] = dist[node] + ncost;
				pq.push({ next, dist[next] });
			}
		}
	}

	cout << dist[N + 2];
	return 0;
}