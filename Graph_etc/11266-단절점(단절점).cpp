#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int V, E, num, ans, order[10001];
vector<int> adj[10001];
bool isCut[10001];

int dfs(int node, int parent = -1) {
    //order에 방문순서를 저장한다.
    //ret : node의 자식노드가 방문할 수 있는 정점중 방문 순서가 가장 작은(빠른) 정점의 번호
	int ret = order[node] = ++num, child = 0;
	
	for (int next : adj[node]) {
		if(parent == next)continue;
        //node의 child가 node의 방문 순서보다 더 빨리 도착한 정점을 갈 수 없으면 node는 단절점이다. == 이 정점을 거치지 않으면 다음 정점으로 가는 길이 없다
        //이 규칙을 위해서 만약 방문이 됐으면 ret에 가장 빠른 순서를 저장한다.
        //node의 직속 child가 다시 node를 호출할 땐 prev에 저장이 되는게 아니기 때문에 prev 체크를 할 필요가 없다.
		if (order[next]) {
			ret = min(ret, order[next]);
			continue;
		}
        
        //여기에 child++을 해주는 이유는
        //이미 방문이 된 노드는 자식이긴 하지만 다른 자식을 통해서 방문이 가능하기 때문에 단절점이 아니게 된다.
        //ex) 원 형식으로 사이클이 있는 그래프
        ++child;
        //prev : 자식 노드가 방문 할 수 있는 정점 번호중 가장 작은것.
		int prev = dfs(next, false);
        //역시 ret에 작은 값을 저장해야함.
		ret = min(ret, prev);
        //node가 root가 아닐 시 자식노드가 방문 할 수 있는 정점번호 중 가장 작은게 지금 방문한 순서보다 무조건 같거나 크다면 단절점이다.
		//>=에서 등호가 사라지면 단절점을 단절점이 아니라고 판단할 수있게 된다.
		//2-3-4-2라는 사이클에서 2번 노드 기준으로 단절점을 검사할때 4번노드까지 갔다가 ret값을 2번노드와 연결되어있으니 2라고 return하게 되는데 이때 등호가 사라지면 단절점임을 판단할 수 없다.
		if (parent != -1 && prev >= order[node]) isCut[node] = true;
	}
    //node가 root인데 자식이 두개 이상이면 단절점임.
	if (parent == -1 && child >= 2)isCut[node] = true;

    //node가 방문 할 수있는 정점번호중 가장 작은 정점번호 return
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;
	
	int u, v;
	for (int i = 0; i < E; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

    //문제에서 모든 그래프가 연결이 아닐 수도 있다고 했으니 각정점에서 출발해줘야 한다.
	for (int i = 1; i <= V; i++)if (!order[i])dfs(i);
    
    //ans를 34번 라인에서 늘려주면 자식이 4개인 단절점이 4개의 자식 모두 방문한 순서보다 크거나 같으면 문제가 생긴다.
    for (int i = 1; i <= V; i++)if (isCut[i])++ans;
	cout << ans << "\n";
	for (int i = 1; i <= V; i++)if (isCut[i])cout << i << " ";

	return 0;
}