/*
석순과 종유석을 구분하여 정렬할 생각을 못하고 하나로 바라보려 했다.

석순과 종유석을 각각 구분해서 정렬을 한다.
높이 i에 부딪히는 석순의 개수 : 석순의 총 개수 - 높이가 i인 석순이 등장하는 처음위치
높이 i에 부딪히는 종유석의 개수 : 종유석의 총개수 - 높이가 H - i를 넘는 종유석이 등장 하는 처음위치 (높이 i에 부딪히려면 H-i보다 커야한다)
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, H, ans[200001];
vector<int> bottom, top;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> H;

	bottom.resize(N / 2), top.resize(N / 2);
	for (int i = 0; i < N / 2; i++) cin >> bottom[i] >> top[i];

	sort(bottom.begin(), bottom.end());
	sort(top.begin(), top.end());

	for (int i = 1; i <= H; i++) {
		int crash = bottom.size() - (lower_bound(bottom.begin(), bottom.end(), i) - bottom.begin());
		crash += (top.size() - (upper_bound(top.begin(), top.end(), H - i) - top.begin()));
		ans[crash]++;
	}
	
	for (int i = 0; i <= N; i++) {
		if (ans[i]) {
			cout << i << " " << ans[i];
			return 0;
		}
	}

	return 0;
}

/*
아래 방법은 prefix sum(구간합)을 이용한 방법이다.
높이를 입력받아 그 높이의 빈도수를 저장한다. 그리고 구간합으로 답을 구한다.

예를들어 3 4 5 의 높이가 있을때 4의 높이로 개똥벌레가 날아가면 3은 무시되고 4와 5에 부딪히게 된다.
따라서 H높이부터 반대로 구간합을 구하면 된다.
*/
#include<iostream>

using namespace std;

int N, H;
int bottom[500001], top[500001], psumB[500001], psumT[500001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> H;

	int b, t;
	for (int i = 0; i < N / 2; i++) {
		cin >> b >> t;
		bottom[b]++;
		top[t]++;
	}

	for (int i = H; i >= 1; i--) {
		psumB[i] = bottom[i] + psumB[i + 1];,
		psumT[i] = top[i] + psumT[i + 1];
	}

	int ans = 2000001, cnt = 1;
	for (int i = 1; i <= H; i++) {
		int crash = psumB[i] + psumT[H - i + 1];
		if (ans >= crash) {
			ans == crash ? cnt++ : cnt = 1, ans = crash;
		}
	}

	cout << ans << " " << cnt;
	return 0;
}