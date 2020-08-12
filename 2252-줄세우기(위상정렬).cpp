/*
위상정렬 기본예제
*/
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

vector<int> v[32005];
int degree[32005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		degree[b]++;
		v[a].push_back(b);
	}
	
	queue<int> q;

	for (int i = 1; i <= n; i++) {
		if (!degree[i])q.push(i);
	}

	for (int i = 0; i < n; i++) {
		int node = q.front();
		q.pop();
		cout << node << " ";
		
		for (int next : v[node]) {
			degree[next]--;
			if (!degree[next])q.push(next);
		}
	}
	
	return 0;
}