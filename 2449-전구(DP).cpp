/*
cache[i][j] : i부터 j번째 전구까지 똑같이 만드는데 드는 최소비용
11066번 파일합치기와 비슷하게 풀이하면 된다.

비용을 추가할때 맨앞의 전구색과 똑같이 만들어준다 생각하면 된다.
*/

/////////     top-down    /////////////
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int N, K, cache[201][201], info[201];

int sol(int s, int e) {
	int &ret = cache[s][e];

	if (s == e)return ret = 0;
	if (ret != -1)return ret;
	
	ret = INF;
    //s~e까지 진행하며 (s,i)구간과 (i+1,e)구간의 색이 다르다면 비용이 1추가된다.
	for (int i = s; i < e; i++) ret = min(ret, sol(s, i) + sol(i + 1, e) + (info[s] != info[i + 1]));
	return ret;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 1; i <= N; i++)cin >> info[i];

	memset(cache, -1, sizeof(cache));
	cout << sol(1, N);

	return 0;
	
}


/////////     bottom-up    /////////////
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int N, K, cache[201][201], info[201];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 1; i <= N; i++) cin >> info[i];

	for (int i = 1; i < N; i++)cache[i][i + 1] = (info[i] != info[i + 1]);


	for (int offset = 2; offset <= N - 1; offset++) {
		for (int i = 1; i + offset <= N; i++) {
			int j = i + offset;
			cache[i][j] = INF;
			for (int k = i; k < j; k++) {
				cache[i][j] = min(cache[i][j], cache[i][k] + cache[k + 1][j] + (info[i] != info[k + 1]));
			}
		}
	}
	
	cout << cache[1][N];
	return 0;
}