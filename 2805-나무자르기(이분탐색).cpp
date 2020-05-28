/*
sum의 값(가능한 값)이 int의 표현 범위 21억을 넘어가면 long long형을 사용한다.

여기선 나무의 길이가 1000000000이고 나무의 개수가1000000이므로 sum이
1000000000000000‬까지 늘어날 수 있다. int의 표현범위는
2147483647(21억)
따라서 long long 표현범위가 9223372036854775807이므로 long long을 사용
*/
#include<iostream>

#define MAX 1000000000
int ar[1000000];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)scanf("%d", &ar[i]);
	int l = 0, h = MAX;

	while (l + 1 < h) {
		int mid = (l + h) / 2;
		int sum = 0;

		for (int i = 0; i < n; i++) {
			if (ar[i] > mid)sum += (ar[i] - mid);
		}
		if (sum >= m)l = mid;
		else h = mid;
	}

	printf("%d",l);
	return 0;
}