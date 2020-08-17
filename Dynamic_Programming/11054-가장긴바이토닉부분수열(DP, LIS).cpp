/*
lis[i] : i자리까지 가장긴증가하는 부분수열의 길이
lds[i] : i자리까지 가장긴감소하는 부분수열의 길이

lis와 lds를 구해준다음에 둘을 합하면 0~i까지 증가하는 가장긴 부분수열의 길이 + i~N까지 가장긴 감소하는 부분수열의 길이가 나온다.
출력할때 -1을 해줘야하는데 i가 두번 포함되었기 때문임.
*/
#include<iostream>

using namespace std;

int N, lis[1001], lds[1001], ar[1001];


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	
	for (int i = 0; i < N; i++) cin >> ar[i];

	for (int i = 0; i < N; i++) {
		int in = 0, de = 0;
		for (int j = 0; j < i; j++) {
			if (ar[j] < ar[i])in = lis[j] > in ? lis[j] : in;
			if (ar[N - j - 1] < ar[N - i - 1])de = lds[N - j - 1] > de ? lds[N - j - 1] : de;
		}
		lis[i] = in + 1;
		lds[N - i - 1] = de + 1;
	}
	
	int maxlen = lis[0] + lds[0];
	for (int i = 1; i < N; i++)maxlen = maxlen < lis[i] + lds[i] ? lis[i] + lds[i] : maxlen;
	
	cout << maxlen - 1;
	
}