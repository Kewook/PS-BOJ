/*
플로이드 와샬 알고리즘을 사용해서 모든 정점에서 각 정점의 의사전달비용이 최소비용을 찾아낸다.

그리고 의사전달비용의 합이 최소가 되는게 아니라 의사전달비용의 최대가 최소가 되어야한다.

그룹핑을 해줄때 disjoint-set을 사용하면 좋지만 N이 크지 않으니 O(N^2)으로도 충분히 가능하다.
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

const int INF = 101;
int N, M, cache[101][101];
bool check[101];
vector<int> group[101];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

    //init
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) cache[i][j] = i == j ? 0 : INF;
	}

    //input
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cache[b][a] = cache[a][b] = 1;
	}

    //Floyd-Warshall
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cache[i][j] = min(cache[i][j], cache[i][k] + cache[k][j]);
			}
		}
	}

    //grouping
    //N이 크면 disjoint-set을 사용하자
	int gcnt = 0;
	for (int i = 1; i <= N; i++) {
		if (check[i])continue;
		for (int j = 1; j <= N; j++) {
            //갈수있고(!INF) 방문을 안한 노드라면 같은그룹이다
			if (cache[i][j] == INF || check[j])continue;
			check[j] = true;
			group[gcnt].push_back(j);
		}
		gcnt++;
	}

	vector<int> ans(gcnt);
	for (int i = 0; i < gcnt; i++) {
		int mincost = INF;
		for (int top : group[i]) {
			int cost = 0;
            //cost의 합의 최소가 아니라 최대 cost중에서 최소를 가려내야한다.
			for (int j = 1; j <= N; j++) if (cache[top][j] != INF)cost = max(cost, cache[top][j]);
			if (mincost > cost)mincost = cost, ans[i] = top;
		}
	}
	
	sort(ans.begin(), ans.end());
	cout << gcnt << "\n";
	for (int num : ans)cout << num << "\n";
	return 0;
}