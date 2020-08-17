/*
N과 R이 너무 크기 때문에 r! *(n-r)!을 나눠주는 대신에 곱셈의 역원을 곱해주면 된다.
*/
#include<iostream>

using namespace std;

const long long MOD = 1000000007L;

int N, R;
long long fac[1000001];

long long xgcd(long long a, long long b) {
	long long  s, t, s1 = 1, s2 = 0, t1 = 0, t2 = 1;

	while (a % b != 0) {
		s = s1 - (a / b) * s2;
		t = t1 - (a / b) * t2;

		s1 = s2;
		s2 = s;
		t1 = t2;
		t2 = t;
		
		long long temp = b;
		b = a % b;
		a = temp;
	}

	if (t2 < 0)t2 += MOD;
	return t2;
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> R;

	fac[1] = 1;
	for (int i = 2; i <= N; i++)fac[i] = (fac[i - 1] * i) % MOD;

	if (N == 1 || R == 0 || R == N) {
		cout << 1;
		return 0;
	}
	
	long long x = xgcd(MOD, (fac[N - R] * fac[R]) % MOD);
	long long ans = (fac[N] * x) % MOD;
	cout << ans;

	return 0;
}