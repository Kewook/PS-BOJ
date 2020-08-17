/*
단순 greedy라고 생각했는데 Disjoint-Set 분류를 보고 로직이 전혀 떠오르지 않아 참고하여 풀이했다.
-> 참고한 블로그 https://mygumi.tistory.com/245
-> Disjoint-set 문제는 척보고 알 수 없기 때문에 최대한 많이 풀어보자.

로직은 다음과 같다.
Greedy적으로 pi번 비행기가 gi번 게이트까지 도킹이 가능하다면 그 뒤에 비행기가 도킹할 수 있도록 되도록이면 gi가 큰 게이트에 도킹해야한다.
하지만 매번 도킹이 가능한지 Brute-force적으로 탐색한다면 O(N^2)의 로직이 되어 TLE를 피하지 못한다.

도킹이 가능한지 빠르게 판단하기 위해 O(lgN)의 복잡도를 가진 Disjoint-set을 사용하면 된다.
일단 비행기가 도착하면 최대한 g에 도킹시킨다. g의 부모를 find하고 그 부모가 0보다 크면 g-1번째 게이트와 g번 게이트를 Union시킨다.
이렇게 될시에 다음비행기가 g에 도착했을시 find(g)를 통해 도킹가능한 게이트중 가장 인덱스가 큰 게이트를 return하게 된다.
만약에 find(g)의 return값이 0일때, 도킹가능한 게이트가 하나도 없다는 걸 뜻하게 된다.
*/
#include<iostream>

using namespace std;

int G, P, parent[100001];

int find(int a) {
	if (parent[a] == a)return a;
	else return parent[a] = find(parent[a]);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> G >> P;
	for (int i = 1; i <= G; i++)parent[i] = i;

	int g, ans = 0;
	for (int p = 1; p <= P; p++) {
		cin >> g;
		int pg = find(g);
		if (pg) {
			++ans;
            //56789가 Union되어있는 상황에서 g가 9일때 parent[pg]는 무조건 5를 return하게 된다.
            //도킹 가능한 게이트를 parent[pg]이 가지고 있고 다시 갱신후에는 -1 인덱스 위치의 게이트를 저장해야 되기 때문에 find(pg - 1)이라 하지 않아도 된다.
			parent[pg] = pg - 1;
		}
		else break;
	}

	cout << ans;
	return 0;
}