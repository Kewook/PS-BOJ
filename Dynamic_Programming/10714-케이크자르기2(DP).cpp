/*
cache[l][r] = 현재 남아있는 케이크의 조각의 인덱스가 l~r이라 할때 JOI가 먹을수 있는 케이크의 최고합

logic 
1. 시작은 JOI가 임의의 조각을 가져간다. == 1~N까지 완탐
2. ioi는 양옆의 조각중 더 큰 조각을 가져가야 한다.
3. joi는 양옆의 조각 둘중 아무거나 가져갈수 있으니 둘중 더 큰 값을 가지는 case를 가져간다.

=> A의 인덱스는 0부터 시작해야 moldular 연산이 쉬워진다.
=> l과 r이 각각 left와 right 방향으로 이어지니 이미 골랐던 조각을 고를일이 없어진다.
=> joi()에서만 메모이제이션 부분을 사용하면 된다. 애초애 cache는 JOI가 가져가는 조각의 합이 저장되는 배열이기도 하고 ioi에서 어차피 다른 경우에서 갱신이 되기 때문이다.
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

int N, A[2001];
long long cache[2001][2001];

long long ioi(int l, int r);
long long joi(int l, int r);

int right(int a) { return (a + 1) % N; }
int left(int a) { return (a - 1 + N) % N; }

long long ioi(int l, int r) {
	if (r == l)return 0;
	if (A[l] < A[r])return joi(l, right(r));
	else return joi(left(l), r);
}

long long joi(int l, int r) {
	long long &ret = cache[l][r];
	if (r == l)return ret = A[l];
	if (ret != -1)return ret;

	long long test1 = ioi(l, right(r)) + A[r];
	long long test2 = ioi(left(l), r) + A[l];

	return ret = max(test1, test2);
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)cin >> A[i];

	memset(cache, -1, sizeof(cache));

	long long ans = 0;
	for (int i = 0; i < N; i++) ans = max(ans, ioi(left(i), right(i)) + A[i]);

	cout << ans;
	return 0;
}