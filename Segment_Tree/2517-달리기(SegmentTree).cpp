/*
내 최대 등수 : 나보다 앞서고 있는 사람보다 더 높은 실력을 가진 사람의 수 + 1
하지만 N이 50만이 넘기 때문에 O(N^2)의 완전탐색으로는 불가하다.

따라서 나보다 앞선사람 중에서 나보다 못하는 사람이 몇명이나 있는지를 저장하는 세그먼트트리를 구성한다.
세그먼트트리에서 실력0 ~ 현재 내실력까지의 구간에서 앞선사람이 몇명이나 있는지를 구하면 된다.
따라서 내 최대등수 : 내 앞에있는사람의 수 - find(0~내실력) + 1
그리고 update를 통해 내 실력으로 세그먼트트리에 다녀간 흔적?을 남긴다.
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

struct Info {
	int idx, val;
	
	bool operator < (const Info &ipt) {
		return idx < ipt.idx;
	}
};

struct SegmentTree {
	vector<int> segment;
	
	SegmentTree(int N) {
		int h = (int)ceil(log2(N));
		int size = (int)pow(2, h + 1);
		segment.resize(size);
	}
    
    //구간 누적합이 아닌것을 잘 생각하고 update를 구성하자.
	void update(int l, int r, int idx, int node) {
		if (idx < l || r < idx)return;
		segment[node]++;

		if (l != r) {
			int mid = (l + r) / 2;
			update(l, mid, idx, node * 2);
			update(mid + 1, r, idx, node * 2 + 1);
		}
	}

	int find(int l, int r, int nl, int nr, int node) {
		if (nr < l || r < nl)return 0;
		if (l <= nl && nr <= r)return segment[node];

		int mid = (nl + nr) / 2;
		return find(l, r, nl, mid, node * 2) + find(l, r, mid + 1, nr, node * 2 + 1);
	}
};

bool cmp(const Info &i1, const Info &i2) {
	return i1.val < i2.val;
}

int N;
Info info[500001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		info[i].idx = i;
		cin >> info[i].val;
	}

    //좌표 압축 : 실력이 순차적이 아니라 랜덤값이니 0~N까지의 수로 압축해주자.
	sort(info, info + N, cmp);
	for (int i = 0; i < N; i++)info[i].val = i;
    
    //압축해줬으면 다시 원상복구 시켜놓자.
	sort(info, info + N);
	
	SegmentTree segTree(N);

	for (int i = 0; i < N; i++) {
        //내 등수 : 나보다 앞에있는 사람의 수(i) - 앞에있는 사람중 나보다 못하는 사람의 수 + 1
		int ans = i - segTree.find(0, info[i].val, 0, N - 1, 1) + 1;
		cout << ans << "\n";
        //세그트리에 내 실력을 기반으로 update시킨다.
		segTree.update(0, N - 1, info[i].val, 1);
	}
	return 0;
}