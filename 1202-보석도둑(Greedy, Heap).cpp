/*
작은가방에 들어갈 수 있는 보석 중 가치가 가장 큰 보석을 집어넣는게 답이다.
그 가치가 가장 큰 보석은 다음에 작은가방보다 더 큰가방에도 들어갈 수 있기 때문에 최대한 작은가방에 최대한 큰 가치의 보석을 넣어야한다. == Greedy

가방을 크기순으로 오름차순 정렬하고 보석을 크기별로 오름차순으로 정렬된 상태라고 생각해보자
가방 하나에 들어갈 수 있는 모든 보석들을 비교해서 그 중에 가장 큰 걸 그가방에 넣어주면 되는데 힙으로 가치가 가장 큰 보석을 빠르게 골라준다.
*/
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

struct Jew {
	int weight, val;
	
	bool operator < (const Jew &ipt) {
		return weight < ipt.weight;
	}
};

int N, K, bag[300001];
Jew jew[300001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++)cin >> jew[i].weight >> jew[i].val;
	for (int i = 0; i < K; i++)cin >> bag[i];

	sort(jew, jew + N);
	sort(bag, bag + K);

	long long ans = 0;
	priority_queue<int> pq;
	for (int i = 0, j = 0; i < K; i++) {
		while (j < N && jew[j].weight <= bag[i])pq.push(jew[j++].val);
        //아무것도 못넣을 수 있으니 힙이 비어있지 않을때만 수행한다.
		if (!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}

	cout << ans;
	return 0;
}