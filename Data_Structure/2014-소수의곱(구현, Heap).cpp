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


/*
중복을 제거하는데 map을 사용하지 않는 방법
min heap을 유지하면서 heap의 top원소를 N번 꺼낸다.
꺼내면서 입력받은 소수들의 곱을 top원소와 곱해주면서 갱신해주면 가능하다.
하지만 중복이 생기는데 이 중복을 방지해주기 위해 이미 곱해줫던것을 제거해주면 가능하다.

https://mygumi.tistory.com/183 => 이 블로그에 있는 글을 참고했다.
*/
#include<iostream>
#include<functional>
#include<queue>

#define long long long
using namespace std;

int N, K, ar[101];
priority_queue<long, vector<long>, greater<long>> pq;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> ar[i];
		pq.push(ar[i]);
	}

    //N번 꺼내줘야하니 N-1번만 꺼내주면서 곱하여 갱신해준다.
	for (int t = 1; t < N; t++) {
		long top = pq.top();
		pq.pop();

		for (int i = 0; i < K; i++) {
			long next = top * ar[i];
			pq.push(next);

            //중복제거
			if (!(top % ar[i]))break;
		}
	}
    //N번째 꺼냄.
	cout << pq.top();
	return 0;
}