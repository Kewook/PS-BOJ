/*
1000C50 = 100891344545564193334812497256 > long long 범위
따라서 10^308의 표현범위를 가진 double을 사용한다.

ans = (1<= i <= M)sum(color[i] C K) / sum(color) C K
*/
#include<iostream>

using namespace std;

int M, color[50], K, sum;
double ans, cache[2503][2503];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 0; i < 2502; i++)cache[i][0] = cache[i][i] = 1;
	for (int i = 0; i <= 2502; i++) {
		for (int j = 1; j <= i; j++) {
			cache[i][j] = cache[i - 1][j] + cache[i - 1][j - 1];
		}
	}

	cin >> M;

	sum = 0;
	for (int i = 0; i < M; i++) {
		cin >> color[i];
		sum += color[i];
	}

	cin >> K;
	for (int i = 0; i < M; i++) ans += cache[color[i]][K];
	cout << fixed;
	cout.precision(19);
	cout << ans / cache[sum][K];
	
	return 0;
}

/*
하지만 각각의 조약돌이 나올확률을 하나씩 게산해서 답을 구하는 방법도 있다.

예를들어 
N = 200
M = 50
K = 3에서 50의 컬러가 40개 있다고 가정하면

이 50의 조약돌에 대한확률은
40/200 * 39/199 * 38/198 * .... * 1/161이 된다.
*/

#include<iostream>

using namespace std;

int M, color[50], K, sum;
double ans;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> M;

	sum = 0;
	for (int i = 0; i < M; i++) {
		cin >> color[i];
		sum += color[i];
	}

	cin >> K;

	for (int i = 0; i < M; i++) {
        //조약돌의 개수보다 더 많은 조약돌을 뽑을 순 없다.
		if (color[i] < K)continue;

		double temp = 1.0;
        //j < K인 이유는 divide by zero를 피하기 위함.
		for (int j = 0; j < K; j++) {
			temp *= (double)(color[i] - j) / (sum - j);
		}
		ans += temp;
	}

	cout << fixed;
	cout.precision(19);
	cout << ans;
	
	return 0;
}