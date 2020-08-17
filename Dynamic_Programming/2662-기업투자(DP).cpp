/*
top-down방식

cache[i][j] : i번째 회사까지 투자했을때 남은 투자액이 j만원 있을 때 얻을 수 있는 최대 이익
knapsack 문제와 똑같이 풀면 되기때문에 최대금액을 구하는것은 쉬웠으나 각 회사에 투자하는 금액을 추적하는게 어려웠다.

처음에는 추적을 위한 배열인 root[]를 1차원으로 두어 최대값이 갱신될 때마다 root[idx] = i로 갱신해주었다.
하지만 이런경우에는 앞의 상태는 무시한 최대값만 저장이 되기때문에 추적이 불가능하다.
예를들어 총 최대값이 100이라하고 1번 회사에 투자하는 금액이 12라고 해보자. 그러면 1번 회사에 투자하고 남은 88만원의 돈으로 2~M까지 투자를 해야되는데
root[2]에는 1번회사 투자한금액은 무시하고 2~M까지 투자했을때 얻는 최대금액만 남게 된다.
==> root를 2차원으로 구분해주자

root[i][j] : i번 회사에 j만원 있을 때 얻을 수 있는 최대이익이 갱신되었을때 i번 회사에 투자한 금액.
이렇게 구분하면 역으로 추적이 가능하다.

또한 처음에 기저사례를 if(!remain) return 0; 으로 잡아주었는데 이렇게 되면 모든 경우에 대해서 검사를 하지 않기 때문에 정답이 나오지 않게 된다.
따라서 모든 회사에 대해서 0원이라도 투자할 수 있는 경우를 생각해줘야 하기때문에 기저 사례를 if(idx > M)return 0;으로 잡아주자.
=> knapsack 표본이다!
*/
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int N, M, cache[21][301], payback[21][301], root[21][301];

int sol(int idx, int remain) {
	if (idx > M)return 0;

	int &ret = cache[idx][remain];
	if (ret != -1)return ret;

	for (int i = remain; i >= 0; i--) {
		int test = sol(idx + 1, remain - i) + payback[idx][i];
		if (ret < test) {
			ret = test;
			root[idx][remain] = i;
		}
	}
	return ret;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int cost;
	for (int i = 0; i < N; i++) {
		cin >> cost;
		for (int j = 1; j <= M; j++) {
			cin >> payback[j][cost];
		}
	}

	memset(cache, -1, sizeof(cache));

	cout << sol(1, N) << "\n";
	for (int i = 1; i <= M; i++) {
		cout << root[i][N] << " ";
		N -= root[i][N];
	}
	return 0;
}


/*
bottom-up방식 

cache[i][j] : 1~i번째 회사까지 j만원을 가지고 투자했을 때 얻을 수 있는 최대이익.
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

int N, M, cache[21][301], payback[21][301], root[21][301];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int cost;
	for (int i = 0; i < N; i++) {
		cin >> cost;
		for (int j = 1; j <= M; j++) {
			cin >> payback[j][cost];
		}
	}

	for (int i = 1; i <= M; i++) {
        //bottom-up 특성상 다음 task를 위해서 모든 cost를 탐색해주어야한다.
		for (int cost = 0; cost <= N; cost++) {
            //i회사에 j만원을 썻다는 가정.    
			for (int j = 0; j <= cost; j++) {
				int val = cache[i - 1][cost - j] + payback[i][j];
				if (cache[i][cost] < val) {
					cache[i][cost] = val;
					root[i][cost] = j;
				}
			}
		}
	}

	cout << cache[M][N] << "\n";

    //top-down과는 다르게 역으로 탐색해주어야 한다.
	vector<int> path;
	for (int i = M; i; i--) {
		path.push_back(root[i][N]);
		N -= root[i][N];
	}
	
	for (int i = path.size() - 1; i >= 0; i--) 	cout << path[i] << " ";
	return 0;
}