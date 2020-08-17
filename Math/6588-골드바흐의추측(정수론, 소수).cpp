/*

*/
#include<iostream>

using namespace std;

int N, K;
bool check[1000001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	check[1] = true;
	for (int i = 2; i <= 1000000; i++) {
		if (check[i])continue;

		for (int j = i + i; j <= 1000000; j += i) {
			if (check[j])continue;
			check[j] = true;
		}
	}

	int N;
	while (true) {
		cin >> N;
		if (N == 0)break;
		
		bool flag = false;
		for (int i = N - 1; i >= 2; i -= 2) {
			if (!check[i] && !check[N - i]) {
				cout << N << " = " << N - i << " + " << i << "\n";
				flag = true;
				break;
			}
		}
		if (!flag)cout << "Goldbach's conjecture is wrong.\n";
	}
	
	return 0;
}