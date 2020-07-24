/*
세그먼트트리 기본문제
*/
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int N, M, K;
long long ar[1000001];

struct SegmentTree {
	vector<long long> segment;
	
	SegmentTree(int n) {
        //log()는 밑이 e인 값을 return 한다
		int h = (int)ceil(log(n) / log(2));
        //노드의 개수만큼 사이즈를 할당한다.
		int size = (int)pow(2, h + 1);
		segment.resize(size);
        //초기 세그먼트트리 구성
		construct(0, n - 1, 1);
	}

	long long construct(int nl, int nr, int node) {
        //leaf node까지 갔을경우 그 값을 저장한다.
		if (nl == nr)return segment[node] = ar[nl];
		int mid = (nl + nr) / 2;
        //왼쪽과 오른쪽으로 나눠 재귀적으로 segmentTree 를 구성한다.
		return segment[node] = construct(nl, mid, node * 2) + construct(mid + 1, nr, node * 2 + 1);
	}

	long long find(int left, int right, int nl, int nr, int node) {
        //지금 찾고있는구간인 nl~nr이 완전히 찾으려는 구간인 left~right에 포함되지 않을때
		if (nr < left || right < nl)return 0;
        //지금 찾고있는 구간이 찾으려는 구간에 완전히 속해있을때
		if (left <= nl && nr <= right)return segment[node];
		
		int mid = (nl + nr) / 2;
		return find(left, right, nl, mid, node * 2) + find(left, right, mid + 1, nr, node * 2 + 1);
	}

	long long update(int idx, int val, int nl, int nr, int node) {
        //수정하려는 ar의 index값이 지금 찾는 구간인 nl~nr사이 없을때 그냥 segment값을 return 해야 구간합이 수정이 된다.
		if (idx < nl || nr < idx)return segment[node];
        //nl과 nr이 같아졌다는것은 idx에 해당하는 segment index를 찾았다는 얘기
		if (nl == nr)return segment[node] = val;
        
		int mid = (nl + nr) / 2;
		return segment[node] = update(idx, val, nl, mid, node * 2) + update(idx, val, mid + 1, nr, node * 2 + 1);
	}
};

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)cin >> ar[i];

	
	SegmentTree stree(N);

	int a, b, c;
	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1)stree.update(b - 1, c, 0, N - 1, 1);
		else cout << stree.find(b - 1 , c - 1, 0, N - 1, 1) << "\n";
	}

	return 0;
}