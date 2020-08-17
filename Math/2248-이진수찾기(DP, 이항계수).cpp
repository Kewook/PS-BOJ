/*
일단 문제이해가 안됐다.
=> L이하의 비트만 1인것을 사전순으로 나열 == N비트중 L개 이하의 1을 가진 2진수를 사전순으로 나열

따라서 N개의 비트중 L개 이하의 1이 들어갈 자리를 순서상관없이 뽑음 => 조합.
조합을 저장하는 cache[i][j]를 이항계수 특징을 이용해서 저장한다.
=> cache[i][j] = cache[i-1][j-1] + cache[i-1][j];

그 다음 사전순으로 나온 순서를 탐색해야한다. 그부분이 sol()
skip == N-1개의 비트에서 1이 L이하개 있다는 가정하에 나오는 경우의수
따라서 skip >= I의 의미는 1이 이 비트에 들어간다면 다음 비트로는 I번째에 해당하는 사전순을 만들어낼수 없다.

cache와 I는 long long형으로 선언해야한다 : I의 범위가 2^31까지 나오기때문
*/
#include<iostream>
#include<string>

using namespace std;

int N, L;
long long I, cache[33][33];

string str;

void sol(int N, int L, long long I) {
	if (N == 0)return;
	if (L == 0) {
		for (int i = 0; i < N; i++)str += '0';
		return;
	}

	long long skip = 0;
	for (int i = 0; i <= L; i++)skip += cache[N - 1][i];

	if (skip >= I) {
		str += '0';
		sol(N - 1, L, I);
	}
	else {
		str += '1';
		sol(N - 1, L - 1, I - skip);
	}
} 
int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L >> I;
	
	cache[0][0] = 1;
	for (int i = 1; i <= 32; i++) {
		cache[i][0] = 1;
		cache[i][i] = 1;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			cache[i][j] = cache[i - 1][j - 1] + cache[i - 1][j];
		}
	}
	sol(N, L, I);
	
	cout << str;
	
	return 0;
}