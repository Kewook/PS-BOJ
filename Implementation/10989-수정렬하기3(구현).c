#include <stdio.h>
#include <stdlib.h>

int N, cnt[10001];

int main() {
	scanf("%d", &N);

	int num;
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		++cnt[num];
	}

	for (int i = 1; i <= 10000; i++) {
		for (int j = 0; j < cnt[i]; j++) printf("%d\n", i);
	}

	return 0;
}