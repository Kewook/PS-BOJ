#include<iostream>

using namespace std;

int N, M, ar[10001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 0; i < N; i++)cin >> ar[i];

	int r = 0, l = 0, sum = 0, ans = 0;
	while (true) {
        //이 조건이 앞에 있어야 l을 N-1까지 탐색할 수 있다.
		if (sum >= M)sum -= ar[l++];
		
		else if (r >= N)break;
		else if (sum < M)sum += ar[r++];
		if (sum == M)++ans;
	}

	cout << ans;
	return 0;
}