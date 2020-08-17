/*
intput
5
8 12 24 36 48

여러가지 수에서 gcd를 구하기 위해서는 유클리드호제법을 사용해서 앞의 최대공약수와 그다음 수와 함께 최대공약수를 구하면 마지막에 나오는 값이 모든수의 최대공약수다.
naive하게 접근했을때는 숫자를 하나씩 빼주며 매번 최대공약수를 구하는 방법이있는데 이방법은 N * (N-1 * log(a+b))가 되기 때문에 O(N^2)의 시간복잡도로 TLE가 나오게 된다.

임의의 수(ar[idx])를 없앴을때 최대공약수를 구하는 방법은 gcd(맨오른쪽~idx+1 , 맨왼쪽~idx-1)이 된다.
따라서 ltor rtol의 배열을 미리 만들어주고 하나씩 빼주며 O(N)의 시간복잡도로 마무리 할 수있다.

아래 예시를 보면 더 이해하기 쉽다.

idx  | 1  2   3   4   5  |
ar   | 8  12  24  36  48 |
ltor | 8  4   4   4   4  |
rtol | 4  12  12  12  48 |
*/
#include<iostream>
#include<algorithm>

using namespace std;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

int N, ar[1000001], ltor[1000002], rtol[1000002];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++)cin >> ar[i];
	
	ltor[1] = ar[1];
	rtol[N] = ar[N];

	for (int i = 2; i <= N; i++) {
		ltor[i] = gcd(max(ltor[i - 1], ar[i]), min(ltor[i - 1], ar[i]));
		rtol[N - i + 1] = gcd(max(rtol[N - i + 2], ar[N - i + 1]), min(rtol[N - i + 2], ar[N - i + 1]));
	}

	int ans = ltor[N], k = -1;
	
	if (ans < rtol[2])ans = rtol[2], k = ar[1];
	if (ans < ltor[N - 1])ans = ltor[N - 1], k = ar[N];

	for (int i = 2; i < N; i++) {
		int next = gcd(max(ltor[i - 1], rtol[i + 1]), min(ltor[i - 1], rtol[i + 1]));
		if (ans < next)ans = next, k = ar[i];
	}

	if (k == -1)cout << -1;
	else cout << ans << " " << k;

	return 0;
}

/*
아래는 세그먼트트리를 이용한 방식으로
각 구간별 gcd를 미리 구축하고 숫자 한개씩 수정하고 루트노드의 값이 얼마인지 확인하는 방법이다.
update의 시간복잡도가 O(logN)이므로 O(NlogN)시간복잡도로 해결할 수있다.
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

int N, ar[1000001], ans, k;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

struct SegmentTree {
	vector<int> segment;

	SegmentTree(int n) {
		int h = (int)ceil(log2(n));
		int size = (int)pow(2, h + 1);
		segment.resize(size);
		construct(0, n - 1, 1);
	}

	int construct(int nl, int nr, int node) {
		if (nl == nr)return segment[node] = ar[nl];
		int mid = (nl + nr) / 2;
		
		int l = construct(nl, mid, node * 2);
		int r = construct(mid + 1, nr, node * 2 + 1);
		return segment[node] = gcd(max(l, r), min(l, r));
	}

	int update(int idx, int val, int nl, int nr, int node) {
		if (idx < nl || nr < idx)return segment[node];
		if (nl == nr)return segment[node] = val;
		
		int mid = (nl + nr) / 2;
		int l = update(idx, val, nl, mid, node * 2);
		int r = update(idx, val, mid + 1, nr, node * 2 + 1);
        
        //leaf 노드를 0으로 수정했을때 divide by zero 런타임에러를 피하기 위함.
		if (l == 0 || r == 0)return max(l, r);
		return segment[node] = gcd(max(l, r), min(l, r));
	}

	int find() {
		return segment[1];
	}
};

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)cin >> ar[i];
	
	SegmentTree sTree(N);
	ans = sTree.find(), k = -1;
	
	for (int i = 0; i < N; i++) {
		sTree.update(i, 0, 0, N - 1, 1);
		if (ans < sTree.find())ans = sTree.find(), k = ar[i];
		sTree.update(i, ar[i], 0, N - 1, 1);
	}
	
	if (k == -1)cout << -1;
	else cout << ans << " " << k;

	return 0;
}