/*
cache[i] = i번째 블록을 맨 바닥에 놓았을때 만들수 있는 최대 높이

처음에는 brick을 내림차순으로 정렬을 하고 큰 넓이에서 작은 넓이로 가게 했다.
이렇게 된다면 bottom-up방식의 논리가 어긋난다.(넓은것 위에 작은것이 올라가야하는데 index가 늘어날수록 작은것이 뒤에있음)

따라서 i를 오름차순으로 정렬했다.
여기서 중요한점은 cache를 갱신할때 j는 0부터 탐색해주어야한다.(i==3이라 할때 j를 1부터 탐색해준다면 3번째 블록이 맨 밑에 있을때 그 블록만 있는 경우를 무시하게 된다.)

*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Brick {
	int num, bottom, height, weight;

	bool operator < (const Brick &nb) {
		return bottom < nb.bottom;
	}
};

int N, cache[101];
Brick brick[101];
vector<int> root;

int max(int a, int b) { return a < b ? b : a; }

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		brick[i].num = i;
		cin >> brick[i].bottom >> brick[i].height >> brick[i].weight;
	}
	sort(brick + 1, brick + N + 1);

	//j가 1이 아닌 0부터 진행해야되는 이유는 그 블럭 하나만 사용하는 경우도 계산해야되기 때문.
	cache[1] = brick[1].height;
	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			if (brick[i].weight > brick[j].weight) {
				cache[i] = max(cache[i], cache[j] + brick[i].height);
			}
		}
	}

	int maxele = cache[1], idx = 1;
	for (int i = 2; i <= N; i++) if (maxele < cache[i])maxele = cache[i], idx = i;

	while (idx > 0) {
		if (cache[idx] == maxele)root.push_back(idx), maxele -= brick[idx].height;
		idx--;
	}

	cout << root.size() << "\n";
	for (int i = root.size() - 1; i >= 0; i--)cout << brick[root[i]].num << "\n";
	return 0;
}