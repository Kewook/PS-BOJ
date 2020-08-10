/*
너무 복잡하게 생각했다.
모든 case중에서 가장 늦게 오는 아이와 가장 빨리나가는 아이의 시간만 빼면된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

typedef struct Pair {
	int start, end;
}Pair;

Pair p[100000];

bool cmp(const Pair &p1, const Pair &p2) {
	if (p1.end < p2.end) {
		return true;
	}
	else return false;
}

bool cmp2(const Pair &p1, const Pair &p2) {
	if (p1.start > p2.start) {
		return true;
	}
	else return false;
}

int main() {
	int n, s, e;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &p[i].start, &p[i].end);
	}

	sort(p, p + n, cmp);
	s = p[0].end;

	sort(p, p + n, cmp2);
	e = p[0].start;

	if (e - s < 0)printf("0");
	else printf("%d", e - s);
	
	return 0;
}