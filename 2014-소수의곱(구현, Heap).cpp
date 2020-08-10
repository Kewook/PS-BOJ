#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>
#include<map>

using namespace std;

int ar[105];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int k, n;
	cin >> k >> n;
	//정답은 integer범위지만 계산하는 과정에서 걸러지는 integer보다 더 큰 수는 long long범위다.
	priority_queue<long long, vector<long long>, greater<long long>> pq;
	map<long long, bool> m;
	
	for (int i = 0; i < k; i++) {
		cin >> ar[i];
	}

	sort(ar, ar + k);
	
	pq.push(1);
	int maxnum = ar[k - 1];

	for (int i = 0; i < n; i++) {
		long long mul = pq.top();
		pq.pop();

		for (int j = 0; j < k; j++) {
			long long num = mul * ar[j];
			
			//pq의 맨앞에 있는 수 mul에 대하여 ar에 담겨있는 수를 곱해준다.
			//이때 구하려는 n보다 넘어갈수가 있다. 그리고 이 수들이 지금 가장 큰 수보다 작을 수도 있고 클 수도 있다.
			//만약 더 커버리면 들어가봤자 소용이 없는 수임. 따라서 그냥 버린다.
			if (pq.size() > n && maxnum < num)continue;
			
			if (!m[num]) {
				m[num] = true;
				maxnum = maxnum < num ? num : maxnum;
				pq.push(num);
			}
			
		}
	}
	cout << pq.top();

	return 0;
}