/*
처음에는 먼저 일어난 순서에 관한 설명이 나오길래 위상정렬 문제인줄 알았다. 위상정렬은 선후관게가 명확하고 DAG이면 바로 사용이 가능하다.
하지만 정점간 간선이 없는경우엔 위상정렬로 그 관계를 입증하기엔 많이 애매하다.

따라서 bfs, dfs로 풀이하는 방법이 있는데 플로이드-와샬 알고리즘으로 문제가 해결가능하다.
기본적으로 플로이드 와샬 알고리즘은 음의 가중치에서도 사용이 가능하며 음의 사이클이 없어야 한다.
하지만 문제에서 "사건의 전후관계가 모순이 되는 입력은 없다"라고 주어져 있는데 이말은 즉슨, 음의 사이클이 발생하지 않는다는 얘기다. (1 --> 2 --> 3 --> 1 과같은 말도 안되는 이야기)
*/
#include<iostream>

using namespace std;

int N, M, S, cache[401][401];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;


	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
        //출력예시에 맞춰서 입력한다.
        //a가 b보다 먼저 일어났으니까 -1
		cache[a][b] = -1;
        //a가(뒤에있는것) b보다 먼저일어났으니까 1
		cache[b][a] = 1;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
                //i->j의 선행관계를 성립하기 위해 우회하는 k가 있다면 i와 j의 선행관계가 성립이 된다.
                //-1의 관계만 성립하면 1의 관계도 저장을 해야한다.
				if (cache[i][k] == -1 && cache[k][j] == -1)cache[i][j] = -1, cache[j][i] = 1;
			}
		}
	}

	cin >> S;
	for (int i = 0; i < S; i++) {
		cin >> a >> b;
		cout << cache[a][b] << "\n";
	}
	
	return 0;
}