/*
세그먼트트리의 find부분을 조금 응용하면 가능하다.
순위는 자기보다 앞선 자들의 합이 될수 있으니 이를 이용하면 된다.
*/
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

const int MAX = 1000001;
int N;

struct SegmentTree {
	vector<long long> segment;

	SegmentTree(int N) {
		int h = (int)ceil(log2(N));
		int size = (int)pow(2, h + 1);
		segment.resize(size);
	}

	long long find(int left, int right, int node, int seq) {
        //seq에 해당하는 사탕 찾았으니 그 index를 return
		if (left == right)return left;
		
		int mid = left + right >> 1;
        //왼쪽의 사탕개수 합이 seq보다 크다면 원하는 답이 왼쪽에 있다.
		if (segment[node * 2] >= seq)return find(left, mid, node * 2, seq);
        //아니면 오른쪽에 있다. 이때 누적합을 빼주어야하니 왼쪽 사탕수의 합을 빼준다.
		else return find(mid + 1, right, node * 2 + 1, seq - segment[node * 2]);
	}

	long long update(int idx, int val, int left, int right, int node) {
		if (idx < left || right < idx)return segment[node];
		if (left == right)return segment[node] += val;
		
		int mid = left + right >> 1;
		return segment[node] = update(idx, val, left, mid, node * 2) + update(idx, val, mid + 1, right, node * 2 + 1);
	}
};


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	SegmentTree sTree(MAX);

	int a, b, c;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		if (a == 1) {
			int ans = sTree.find(1, MAX, 1, b);
			cout << ans << "\n";
            //사탕을 한개 꺼내줬으니
			sTree.update(ans, -1, 1, MAX, 1);
		}
		else {
			cin >> c;
			sTree.update(b, c, 1, MAX, 1);
		}
	}
	
	return 0;
}