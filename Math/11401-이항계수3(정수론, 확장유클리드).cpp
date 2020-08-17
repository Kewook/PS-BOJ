/*
확장유클리드 문제
*/
#include<iostream>

using namespace std;

const long long MOD = 1000000007;

int N, R;
long long fac[4000001];

long long xgcd(long long a, long long b) {
	long long r, s, t, q, s1 = 1, s2 = 0, t1 = 0, t2 = 1;

	while (b) {
		r = a % b;
		q = a / b;
		s = s1 - s2 * q;
		t = t1 - t2 * q;

		s1 = s2;
		s2 = s;
		t1 = t2;
		t2 = t;
		
		a = b;
		b = r;
	}

	if (t1 < 0)t1 += MOD;
	return t1;
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> R;

	fac[1] = 1;
	for (int i = 2; i <= N; i++)fac[i] = (fac[i - 1] * i) % MOD;

    //예외케이스 처리해주는것 잊지말자.
	if (N == 1 || R == 0 || R == N) {
		cout << 1;
		return 0;
	}
	
	long long x = xgcd(MOD, (fac[N - R] * fac[R]) % MOD);
	long long ans = (fac[N] * x) % MOD;
	cout << ans;

	return 0;
}