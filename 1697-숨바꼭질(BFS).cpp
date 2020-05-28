/*
메모리초과
오답이유 : 큐에 동일한 값이 너무 많이 들어간다. bfs를 해준다면 무조건 visited를 해주어야 동일한값이 안들어감.
*/
/*
#include<iostream>
#include<queue>

using namespace std;

int bfs(int n, int k) {
	queue<int> q;
	q.push(n);
	int cnt = 0;

	while (!q.empty()) {
		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			int num = q.front();
			if (num == k)return cnt;
			q.pop();

			if (num - 1 >= 0) {
				q.push(num - 1);
			}
			if (num + 1 <= 100000) {
				q.push(num + 1);
			}
			if (num * 2 <= 100000) {
				q.push(num * 2);
			}
		}
		cnt++;
	}
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	printf("%d", bfs(n, k));

	return 0;
}
*/

#include<iostream>
#include<cstring>
#include<queue>
#define SIZE 100000

using namespace std;
bool visited[100001];

int bfs(int n, int k) {
	queue<int> q;
	q.push(n);
	int cnt = 0;

	while (!q.empty()) {
		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			int num = q.front();
			if (num == k)return cnt;
			q.pop();

			if (num - 1 >= 0 && !visited[num - 1]) {
				visited[num - 1] = true;
				q.push(num - 1);
			}
			if (num + 1 <= SIZE && !visited[num + 1]) {
				visited[num + 1] = true;
				q.push(num + 1);
			}
			if (num * 2 <= SIZE && !visited[num * 2]) {
				visited[num * 2] = true;
				q.push(num * 2);
			}
		}
		cnt++;
	}
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	memset(visited, false, SIZE+1);
	printf("%d", bfs(n, k));

	return 0;
}
