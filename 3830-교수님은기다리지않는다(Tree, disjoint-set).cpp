/*
처음에 생각했던 방법은 naive하게 트리를 구성하려했지만 그렇게하면 메모리와 시간초과가 발생한다.

핵심은 트리를 구성하여 a와 b의 차이값을 알고싶으면 sum(root~b) - sum(root~a)를 해주면 된다.
같은 트리가 아닌것을 구분하기 위해 disjoint-set을 사용해 그룹을 구성해준다.
*/
#include<iostream>
#include<vector>

using namespace std;

struct Tree {
	int node, cost;
};

struct Query {
	int a, b;
	bool flag;
};

int N, M, parent[100005];
vector<Tree> adj[100005];
vector<Query> qr;
bool check[100005];
long long dist[100005];

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

void dfs(int node, long long cost) {
	dist[node] = cost;
	
	for (auto next : adj[node]) {
		if (check[next.node])continue;
		check[next.node] = true;
		dfs(next.node, cost + next.cost);
	}
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	while (true) {
		cin >> N >> M;
		if (N == 0 && M == 0)break;
		
		//init
		qr.clear();
		for (int i = 1; i <= N; i++) {
			adj[i].clear();
			parent[i] = i;
			check[i] = false;
		}

		char q;
		int a, b, c;
		for (int i = 0; i < M; i++) {
			cin >> q >> a >> b;
			int pa = find(a), pb = find(b);

			if (q == '!') {
				cin >> c;
				
				//root로부터 거리 차이를 구하기 때문에 같은 그룹이라면 간선을 추가해줄 필요가 없다.
				if (pa != pb) {
					parent[pb] = pa;
					adj[a].push_back({ b,c });
					adj[b].push_back({ a,-c });
				}
			}
            //현재까지 구해진 결과에대해서 쿼리를 구하는것이지만 같은그룹일때 매번 dfs를 수행하기엔 너무 비효율적이기 때문에 질문을 저장해둔다.
			else pa != pb ? qr.push_back({ a,b, false }) : qr.push_back({ a,b,true });
		}

        //트리를 순회하면서 루트로부터 dist를 구해준다
        //시작이 1인 노드만 해주는게 아니라 모든 트리를 구해줘야하기 때문에 각 노드를 기점으로 순회한다.
		for (int i = 1; i <= N; i++)if (!check[i])dfs(i, 0);

		for (auto q : qr) {
			if (!q.flag)cout << "UNKNOWN\n";
			else cout << dist[q.b] - dist[q.a] << "\n";
		}
	}
	
	
	return 0;
}