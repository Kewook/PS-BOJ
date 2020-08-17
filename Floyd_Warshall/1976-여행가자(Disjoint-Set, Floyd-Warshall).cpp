/*
플로이드-와샬 알고리즘을 통해서 O(N^3)만에 모든 경로를 구할 수 있다.
*/
#include<iostream>
#include<string>

using namespace std;

int N, M, root[1001], cache[201][201];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> cache[i][j];
		}
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (cache[i][k] && cache[k][j])cache[i][j] = 1;
			}
		}
	}
	
	for (int i = 0; i < M; i++)cin >> root[i];
	
	string ans = "YES";
	int prev = root[0];
	for (int i = 1; i < M; i++) {
		if (prev != root[i] && !cache[prev][root[i]]) {
			ans = "NO";
			break;
		}
		prev = root[i];
	}

	cout << ans;
	return 0;
}

/*
Disjoint-Set을 이용해서 입력루트중에 같은 부모가 아닐 시 그 루트로 갈 수 없다.
*/
#include<iostream>
#include<string>

using namespace std;

int N, M, parent[201];

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++)parent[i] = i;

	bool flag;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> flag;
			if (i >= j || !flag)continue;

			int pa = find(i), pb = find(j);
			if (pa != pb) parent[pb] = pa;
		}
	}

	int node, p;
    
	cin >> node;
	p = find(node);
	for (int i = 1; i < M; i++) {
		cin >> node;
		if (find(node) != p) {
			cout << "NO";
			return 0;
		}
	}

	cout << "YES";	
	return 0;
}