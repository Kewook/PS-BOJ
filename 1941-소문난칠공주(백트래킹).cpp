/*
십자모양은 DFS로 찾을수 없다. 따라서 25명의 학생들의 조합을 찾아낸다.
처음에는 25명의 순열을 찾는다 생각해서 25!이면 무조건 시간초과가 난다고 생각함
하지만 25C7의 경우의 수만 찾으면 되기 때문에 시간은 걱정없다.

모든 조합을 알아내고 이 학생들이 다 연결되어있는지만 검사한다.
*/
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Pos {
	int ypos, xpos;
};

char ar[5][5];
int som[7], ans;
int dy[] = { 1,-1,0,0 }, dx[] = { 0,0,1,-1 };
bool check[25];

bool isTrue() {
    //7명의 학생의 위치를 1이라하는 test배열
    //BFS돌려서 7명의 학생중 방문이 안된 자리가 있다면 연결되지 않았다는 말.
	int test[5][5];
	bool visited[5][5];
	memset(test, 0, sizeof(test));
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < 7; i++)test[som[i] / 5][som[i] % 5] = 1;
	
	queue<Pos> q;
	q.push({ som[0] / 5 , som[0] % 5 });
	visited[som[0] / 5][som[0] % 5] = true;
	
	while (!q.empty()) {
		int ypos = q.front().ypos, xpos = q.front().xpos;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = ypos + dy[i], nx = xpos + dx[i];
			if (ny < 0 || nx < 0 || ny > 4 || nx > 4)continue;
			if (visited[ny][nx] || !test[ny][nx])continue;
			visited[ny][nx] = true;
			q.push({ ny, nx });
		}
	}
	
	for (int i = 0; i < 7; i++)if (!visited[som[i] / 5][som[i] % 5])return false;
	return true;
	
}

void dfs(int idx, int cnt) {
	if (cnt == 7) {
		int count = 0;
		for (int i = 0; i < 7; i++) if (ar[som[i] / 5][som[i] % 5] == 'S')count++;
		if (count < 4)return;
		if (isTrue()) ans++;			
		return;
	}

	for (int i = idx; i < 25; i++) {
		if (check[i])continue;
		check[i] = true;
		som[cnt] = i;
		dfs(i, cnt + 1);
		check[i] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) cin >> ar[i][j];
	}
    
	ans = 0;
	dfs(0, 0);

	cout << ans;
	return 0;
}