#include <stdio.h>
#include <stdlib.h>

int N, ar[1001];

int cmp(void *a, void *b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)return -1;
	else if (num1 > num2)return 1;
	else return 0;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)scanf("%d", &ar[i]);

	qsort(ar, N, sizeof(int), cmp);
	for (int i = 0; i < N; i++)printf("%d\n", ar[i]);

	return 0;
}