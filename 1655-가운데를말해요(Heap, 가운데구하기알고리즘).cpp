/*
중간값 구하기 알고리즘

maxheap의 사이즈는 minheap과 같거나 1이 더 크다.
maxheap의 top은 무조건 minheap의 top보다 작은수가 들어가야한다.

이런 규칙을 가지고 진행시 maxheap의 top에는 중간값이 저장되어있다.
*/
#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>

using namespace std;

int N;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	priority_queue<int> maxheap;
	priority_queue<int, vector<int>, greater<int>> minheap;

	cin >> N;

	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;

		if (maxheap.size() >= minheap.size() + 1)minheap.push(num);
		else maxheap.push(num);

		if (minheap.size() > 0 && minheap.top() < maxheap.top()) {
			int num1 = minheap.top();
			int num2 = maxheap.top();
			minheap.pop(); maxheap.pop();
			maxheap.push(num1);
			minheap.push(num2);			
		}
		cout << maxheap.top() << "\n";
	}
	return 0;
}