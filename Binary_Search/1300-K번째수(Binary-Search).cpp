/*
K번째 숫자라는 건 자신을 포함해서 자기보다 작은 숫자가 K개 있어야한다.
따라서 임의의 숫자 mid를 택해서 2차원 배열에서 그 숫자보다 작은 숫자의 수를 세는게 관건이다.
문제 특성상 K번째에 있는 수는 K라는 수보다 작거나 같음이 보장된다.

2차원 배열에서 mid보다 작거나 같은 숫자를 빠르게 찾는것은 조건을 전개하면 가능하다.
ar[i][j]는 i*j인데 i*j <= mid인지 확인하기 위해서는 양변을 i로 나눠주면 가능하다.
따라서 1~N행을 순회하며 mid/i값을 더해주자.
하지만 N이 1000이 넘어가면 1000*1000/2가 되는데 이는 N보다 커지므로(j가 N보다 커질리가 없음) min(mid / i, N)을통해 확인한다. 
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, K;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	int l = 1, r = K, ans;

    //lower_bound를 구해주면 가능하다.
	while (l < r) {
		int mid = (l + r) / 2;

		long long cnt = 0;
		for (int i = 1; i <= N; i++) cnt += min(mid / i, N);

		if (cnt >= K)r = mid;
		else l = mid + 1;
	}

	cout << r;
	return 0;
}