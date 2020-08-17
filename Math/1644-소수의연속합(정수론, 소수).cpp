/*
소수를 vector 컨테이너에 저장하지 않고 하면 더 빠르긴하다.
*/
#include<iostream>
#include<vector>

using namespace std;

int N;
bool check[4000001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	for (int i = 2; i <= N; i++) {
		if (check[i])continue;
		for (int j = i + i; j <= N; j += i) {
			if (check[j])continue;
			check[j] = true;
		}
	}
	
	vector<int> prime;
	for (int i = 2; i <= N; i++)if (!check[i])prime.push_back(i);

	int ans = 0;
	
	for (int i = 0; i < prime.size(); i++) {
		int sum = 0;
		for (int j = i; j < prime.size(); j++) {
			sum += prime[j];
			if (sum >= N) {
				if (sum == N)++ans;
				else break;
			}
		}
	}
	
	cout << ans;
	return 0;
}