/*
Tree Dp 문제
naive하게 접근했을때
트리 순회 N * 최소개수 고르는 경우의수 N * 최소개수가 M일때 NCM
N^2이상이 되기때문에 무조건 시간초과가 나온다.

아이디어는 다음과 같다.
임의의 노드가 얼리어답터일때 그와 연결된 다른 노드는 얼리어답터가 되도되고 아니어도 된다.
만약 얼리어답터가 아니라 할때, 그와 연결된 다른 노드는 모드 얼리어답터야한다.

따라서 트리를 순회하면서 얼리어답터의 수를 구할 수 있다.
루트를 1로 잡고 단방향 트리가 존재한다고 생각했을때 각 노드가 얼리어답터(1)이거나 얼리어답터가 아닌(0) 경우를 모두 탐색해본다.
이때 서브트리는 각 task에서 최소 얼리어답터의 수를 return하게 된다.

cache[i][j] : j가 0이라면 i번째 노드가 얼리어답터가 아닐때 서브트리의 최소 얼리어답터 개수. 1이라면 i번째 노드가 얼리어답터라는 뜻.
sol(int pre, int curr, int state) : pre는 이전에 탐색했던 노드, curr은 탐색하는 노드, state는 pre의 상태값.

루트가 1인 단방향 트리를 미리 구성하면 sol함수를 sol(int curr, int state)로 구성할 수 있지만 N이 1M이기 때문에 시간이 더 오래걸린다.
-> 굳이 트리를 만들어줄 필요가 없다.
또한, 인접리스트로 트리를 구성해주었기 때문에, sol에서 기저사례를 추가할 필요가 없다.
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int N, cache[1000001][2];
vector<int> adj[1000001];

int sol(int pre, int curr, int state) {
	int &ret = cache[curr][state];
	if (ret != -1)return ret;

	//pre가 얼리어답터인 경우
	if (state) {
		ret = 1;
		for (int next : adj[curr]) {
			if (next == pre)continue;
			ret += min(sol(curr, next, 0), sol(curr, next, 1));
		}
		return ret;
	}
	//pre가 얼리어답터가 아닌경우
	else {
		ret = 0;
		for (int next : adj[curr]) {
			if (next == pre)continue;
			ret += sol(curr, next, 1);
		}
		return ret;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	memset(cache, -1, sizeof(cache));
	
	cout << min(sol(0, 1, 0), sol(0, 1, 1));
	return 0;
}