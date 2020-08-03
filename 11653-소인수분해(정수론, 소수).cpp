//0ms
#include<iostream>
#include<cmath>

using namespace std;

int N;
bool check[10000001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 2; i <= sqrt(10000000); i++) {
		while (!(N%i)) {
			cout << i << "\n";
			N /= i;
		}
	}

	if (N != 1)cout << N;
	return 0;
}

//52ms

#include<iostream>
#include<cmath>

using namespace std;

int N;
bool check[10000001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	int num = N;
	for (int i = 2; i <= num; i++) {
		if (check[i])continue;

		while (!(num %i)) {
			cout << i << "\n";
			num /= i;
		}
		
		if ((long long)i*i <= 10000000)for (int j = i * i; j <= num; j += i)check[j] = true;
	}

	return 0;
}