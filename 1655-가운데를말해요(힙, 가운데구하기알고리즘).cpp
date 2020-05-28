#include<iostream>
#include<functional>
#include<algorithm>
#include<queue>

using namespace std;

int N;

//중갑값구하기 알고리즘

priority_queue<int, vector<int>, less<int>> maxheap;
priority_queue<int, vector<int>, greater<int>> minheap;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;

		if (maxheap.size() >= minheap.size() + 1) {
			minheap.push(num);
		}
		else maxheap.push(num);

		if (minheap.size() > 0 && maxheap.top() > minheap.top()) {
			int min_top = minheap.top(), max_top = maxheap.top();
			maxheap.pop(); minheap.pop();
			maxheap.push(min_top); minheap.push(max_top);
		}

		cout << maxheap.top() << "\n";
	}
	return 0;
}