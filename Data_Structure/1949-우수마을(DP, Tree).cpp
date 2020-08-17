/*
2533-사회망서비스와 유사한 문제

규칙대로 점화식을 세우면 다음과 같다.
int sol(현재마을, 상태){
    if(현재 마을이 우수마을)ret += sol(다음마을이 우수마을x);
    else if(우수마을x) ret += max(sol(다음마을이 우수마을), sol(다음마을이 우수마을x));
}
이렇게 되면 규칙 3번에서 우수마을이 아니라면 인접한 마을중에서 적어도 우수마을이 한개 이상 있어야 한다는 규칙이 깨진다.
하지만 둘다 우수마을이 아닐경우 인구수를 추가하지 않기때문에 어차피 max()에서 걸러진다.
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

int N, cost[10001], cache[10001][2];
vector<int> adj[10001];

int sol(int prev, int cur, bool state) {
	int &ret = cache[cur][state];
	if (ret != -1)return ret;
	
	if(state)ret = cost[cur];
    else ret = 0;
    
	for (int next : adj[cur]) {
		if (prev == next)continue;
		if (state)ret += sol(cur, next, 0);
		else ret += max(sol(cur, next, 1), sol(cur, next, 0));
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++)cin >> cost[i];
	
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	memset(cache, -1, sizeof(cache));
	cout << max(sol(0, 1, 0), sol(0, 1, 1));
	return 0;
}