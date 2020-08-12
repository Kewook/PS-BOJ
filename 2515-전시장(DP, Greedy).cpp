/*
bottom-up방식

그리디적인 방법과 DP적인 방법을 섞어서 풀면 된다.

cache[i] : i번째 그림까지 봤을때 얻을 수 있는 최대가치
idx[i] : i번째 그림을 놓을 수 있을때 길이차가 S이상인 그림중에 제일 높은 index

cache[i] = max(그림을 놓지 않을때, 그림을 놓을때)
놓지 않을때는 그냥 cache[i-1]이다.
놓을 때는 앞에서 놓을 수 있는 그림중에서 인덱스가 제일 높은 그림의 cache값 + i번째 그림의 가치 이다

놓을 수 있는 제일 높은 인덱스의 그림의 cache값이 최대값을 보장해주는 이유는 bottom-up방식으로 항상 최대값만 쌓아올려주기 때문이다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

struct Paint {
	int height, val;

	bool operator < (const Paint &ipt) {
		return height < ipt.height;
	}
};

int N, S, cache[300001], idx[300001];
Paint paint[300001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> S;
	for (int i = 1; i <= N; i++) cin >> paint[i].height >> paint[i].val;
    //높이순으로 정렬한다.
	sort(paint + 1, paint + 1 + N);

	for (int i = 1; i <= N; i++) {
        //어차피 i그림은 i-1그림보다 높기때문에 idx[i-1]의 인덱스부터 시작함이 자명하다.
		for (idx[i] = idx[i - 1]; idx[i] < i; idx[i]++) {
            //정렬이 되어있으니 한번만이라도 S이상이 되지 않는다면 그다음은 무조건 안된다.
			if (paint[i].height - paint[idx[i]].height < S)break;
		}
        //초기값 idx[i-1]은 무조건 S이상 차이나기 때문에 1개 줄여주는게 맞다/
		idx[i]--;
	}
    
    //cache[i] = max(i를 놓지않을때, i를 놓을때)
	for (int i = 1; i <= N; i++) cache[i] = max(cache[i - 1], cache[idx[i]] + paint[i].val);

	cout << cache[N];
	return 0;
}


/*
처음엔 top-down 방식으로 어차피 앞에는 자신보다 높은 그림이 오면 무시가 되기 때문에
정렬을 한뒤에 모든 조합을 만들었지만
메모이제이션을 해도 N이 30만이기 때문에 시간초과가 났다.

아래는 TLE인 코드다.
*/

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Paint {
	int height, val;

	bool operator < (const Paint &ipt) {
		return height < ipt.height;
	}
};

int N, S, cache[300001];
Paint paint[300001];

int sol(int idx) {
	if (idx >= N) return paint[N].val;
	
	int &ret = cache[idx];
	if (ret != -1)return ret;
	
	for (int i = idx; i <= N; i++) if (paint[i].height - paint[idx].height >= S) ret = max(ret, sol(i) + paint[idx].val);
	return ret;
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> S;
	for (int i = 1; i <= N; i++) {
		cin >> paint[i].height >> paint[i].val;
	}

	memset(cache, -1, sizeof(cache));
	sort(paint + 1, paint + 1 + N);

	cout << sol(0);
	return 0;
}