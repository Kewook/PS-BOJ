/*
kanpsack문제 심화

담을 수 있는 물건의 개수가 여러개다. 각 물건을 1개 단위로 나누면 범위가 100만이 넘어선다.
이를 줄이기 위해 각 물건을 1, 2, 4, 8, 16...의 2의 거듭제곱으로 물건묶음을 만들어낸다(물건을 쪼갬). 
예를들어 K가 5일때 이를 2, 1 물건으로 묶고 나머지 3개를 묶어준다.

그리고 평범하게 01 knapsack 문제처럼 풀면된다.
*/

////// bottom-up ///////
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Info {
	int cost, value;
};

int N, M, cache[10001];
vector<Info> v;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	
	int V, C, K;
	for (int i = 0; i < N; i++) {
		cin >> V >> C >> K;
		for (int val = 1; K > 0; val *= 2) {
			int num = min(val, K);
			v.push_back({ V*num, C*num });
			K -= num;
		}
	}


	for (int i = 0; i < v.size(); i++) {
		for (int j = M; j >= v[i].cost; j--) {
			cache[j] = max(cache[j], cache[j - v[i].cost] + v[i].value);
		}
	}

	cout << cache[M];
	return 0;
}


/////// top-down //////
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

struct Info {
	int cost, value;
};

int N, M, cache[2000][10001];
vector<Info> v;

int sol(int idx, int cost) {
	if (idx >= v.size())return 0;
	
	int &ref = cache[idx][cost];

	if (ref != -1) return ref;

	if (v[idx].cost > cost)return sol(idx + 1, cost);
	else return ref = max(sol(idx + 1, cost), sol(idx + 1, cost - v[idx].cost) + v[idx].value);
	
}
int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	memset(cache, -1, sizeof(cache));

	int V, C, K;
	for (int i = 0; i < N; i++) {
		cin >> V >> C >> K;
		for (int val = 1; K > 0; val *= 2) {
			int num = min(val, K);
			v.push_back({ V*num, C*num });
			K -= num;
		}
	}

	cout << sol(0, M);
	return 0;
}