/*
기초에 충실해야하는 문제
시간초과이유는 dfs탐색에서 길어져서 시간초과 남.
주의점

sol(idx+1);
check[idx] = true;
sol(idx+1);하면 틀린다.
백트래킹할때 flase로 바꿔지지 않으므로 의미없는 조합이 만들어진다.
*/

#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>

#define INF 987654321
using namespace std;

vector<int> adj[11];
bool check[11], visited[11];
int ar[11], N;
int ans = INF;

int dfs(int node, bool flag) {
	int cnt = 1;
	visited[node] = true;

	for (int next : adj[node]) {
		if (visited[next])continue;
		if (check[next] != flag)continue;
		cnt += dfs(next, flag);
	}

	return cnt;
}

void sol(int idx) {
	if (idx > N) {
		int a = 0, b = 0;
		int nodeA = 0, nodeB = 0;

		for (int i = 1; i <= N; i++) {
			if (check[i]) {
				nodeA = i;
				a++;
			}
			else {
				nodeB = i;
				b++;
			}
		}

		if (a != 0 && b != 0) {
			memset(visited, false, sizeof(visited));
			if (a == dfs(nodeA, true) && b == dfs(nodeB, false)) {
				a = b = 0;
				for (int i = 1; i <= N; i++) {
					if (check[i]) a += ar[i];
					else b += ar[i];
				}
				ans = ans < abs(a - b) ? ans : abs(a - b);
			}
		}
		return;
	}

	check[idx] = true;
	sol(idx + 1);
	check[idx] = false;
	sol(idx + 1);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) cin >> ar[i];


	for (int i = 1; i <= N; i++) {
		int num;
		cin >> num;

		for (int j = 1; j <= num; j++) {
			int node;
			cin >> node;
			adj[i].push_back(node);
			adj[node].push_back(i);
		}
	}


	sol(1);


	if (ans == INF)cout << -1;
	else cout << ans;

	return 0;
}