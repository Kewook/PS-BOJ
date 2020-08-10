/*
2042-구간합구하기 문제와 동일하다
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

int N, Q;
long long ar[100001];

struct SegmentTree {
	vector<long long> segment;

	SegmentTree(int N) {
		int h = (int)ceil(log(N) / log(2));
		int size = (int)pow(2, h + 1);
		segment.resize(size);
		construct(0, N - 1, 1);
	}

	long long construct(int nl, int nr, int node) {
		if (nl == nr)return segment[node] = ar[nl];
		int mid = (nl + nr) / 2;
		return segment[node] = construct(nl, mid, node * 2) + construct(mid + 1, nr, node * 2 + 1);
	}

	long long find(int left, int right, int nl, int nr, int node) {
		if (nr < left || right < nl)return 0;
		if (left <= nl && nr <= right)return segment[node];
		int mid = (nl + nr) / 2;
		return find(left, right, nl, mid, node * 2) + find(left, right, mid + 1, nr, node * 2 + 1);
	}

	long long update(int idx, int val, int nl, int nr, int node) {
		if (idx < nl || nr < idx)return segment[node];
		if (nl == nr)return segment[node] = val;
		int mid = (nl + nr) / 2;
		return segment[node] = update(idx, val, nl, mid, node * 2) + update(idx, val, mid + 1, nr, node * 2 + 1);
	}
};

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> Q;
	for (int i = 0; i < N; i++)cin >> ar[i];

	SegmentTree sTree(N);

	int x, y, a, b;
	for (int i = 0; i < Q; i++) {
		cin >> x >> y >> a >> b;
		if (x > y)swap(x, y);

		cout << sTree.find(x-1, y-1, 0, N - 1, 1) << "\n";
		sTree.update(a - 1, b, 0, N - 1, 1);
	}
	return 0;
}