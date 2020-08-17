/*
모든 수는 소수의 곱으로 나타낼 수 있는 전제하에 실행.

소인수분해를 통해 모든수의 최대공약수를 구할 수 있다.
8 : 2*2*2
24 : 2*2*2*3
9 : 3*3

규칙을 해석하면 임의의 두수를 뽑아 각 수에 소수를 곱하고 나눠주는 행위라는 것을 알수있다.
따라서 각 수를 소인수분해하고 그 수의 소수를 다른수에게 전달하여 나올 수 있는 가장 큰 최대공약수를 구하고 최소 몇번의 이동을 통해 얻을 수 있는지를 알면 된다.

처음에는 메모리를 생각하지 않고 풀었다가 메모리초과가 났다.
*/

/*
처음 AC 코드
240ms로 AC
*/
#include<iostream>
#include<cstring>
#include<cmath>

#define SIZE 1000000

using namespace std;

int N, ar[101], prime[SIZE + 1], gcd[SIZE + 1], test[SIZE + 1];
bool check[SIZE + 1];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 2; i <= SIZE; i++) {
		if (check[i])continue;
		for (int j = i * i; j <= SIZE; j += i) {
			if (check[j])continue;
			check[j] = true;
		}
	}

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> ar[i];

		int num = ar[i];
		for (int j = num; j >= 2; j--) {
			if (num == 1)break;
			if (check[j])continue;
			while (!(num % j)) {
				++prime[j];
				num /= j;
			}
		}
	}

	int ans = 1;
	for (int i = 2; i <= SIZE; i++) {
		if (prime[i] >= N) {
			gcd[i] = prime[i] / N;
			ans *= (pow(i, gcd[i]));
		}
	}

	int change = 0;
	for (int i = 0; i < N; i++) {
		int num = ar[i];

		memset(test, 0, sizeof(test));
		for (int j = num; j >= 2; j--) {
			if (num == 1)break;
			if (check[j])continue;
			while (!(num%j)) {
				++test[j];
				num /= j;
			}
		}
		for (int j = 2; j <= SIZE; j++) if (gcd[j] && test[j] < gcd[j])change += (gcd[j] - test[j]);
	}

	cout << ans << " " << change;
	return 0;
}


/*
두번째 제출코드
40ms로 AC
*/

#include<iostream>
#include<vector>
#include<cmath>

#define SIZE 1000000

using namespace std;

vector<int> prime, plist[101];
int N, pnum[SIZE + 1];
bool check[SIZE + 1];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 2; i <= SIZE; i++) {
		if (check[i])continue;
		for (int j = i + i; j <= SIZE; j += i) {
			if (check[j])continue;
			check[j] = true;
		}
	}

	cin >> N;
	for (int i = 2; i <= SIZE; i++)if (!check[i])prime.push_back(i);
	for (int i = 0; i < N; i++)plist[i].resize(prime.size(), 0);


	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;

		for (int j = 0; j < prime.size(); j++) {
			if (num == 1)break;
			while (!(num % prime[j])) {
				++pnum[prime[j]];
				++plist[i][j];
				num /= prime[j];
			}
		}
	}

	int gcd = 1, change = 0;
	for (int i = 0; i < prime.size(); i++) {
		int offset = pnum[prime[i]] / N;

		if (offset) {
			gcd *= pow(prime[i], offset);
			for (int j = 0; j < N; j++) {
				if (plist[j][i] < offset)change += (offset - plist[j][i]);
			}
		}
	}

	cout << gcd << " " << change;
	return 0;
}

/*
마지막 코드
12ms로 AC
*/

#include<iostream>
#include<cmath>

#define SIZE 1000000

using namespace std;

int N, ar[100], dived[SIZE + 1], gcd, change;
bool check[SIZE + 1];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++)cin >> ar[i];
	
	gcd = 1;
	for (int p = 2; p <= SIZE; p++) {
		if (!check[p]) {
			int cnt = 0;

			for (int i = 0; i < N; i++) {
				dived[i] = 0;

				if (ar[i] == 1)continue;
				while (!(ar[i] % p)) {
					++dived[i];
					ar[i] /= p;
				}
				cnt += dived[i];
			}
			
			int offset = cnt / N;
			if (offset) {
				gcd *= pow(p, offset);
				for (int i = 0; i < N; i++) if (dived[i] < offset)change += (offset - dived[i]);
			}

			if (p <= 1000)for (int i = p * p; i <= SIZE; i += p)check[i] = true;
		}
	}

	cout << gcd << " " << change;
	return 0;
}