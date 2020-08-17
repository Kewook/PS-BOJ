/*
top-down방식
cache[a][b] : a~b까지 합치는데 드는 최소비용

범위를 점점 줄여가며 비교해준다. 어떤 범위 s와 e가 있다고 했을때 그중에 임의의 값 idx기준으로 왼쪽과 오른쪽을 탐색하면 최소비용을 찾을수 있다.
이 말은 즉슨 s와 e사이의 임의의값 idx를 기준으로 각각 양옆의 사례를 더해주면 된다.
idx를 선정하는 기준은 완전탐색을 기반으로 탐색하며 가지치기를 줄이기 위해 cache배열을 사용한다.
더이상 범위를 줄일수 없을때(s ==e || s+1 == e)를 기저사례로 둔다.

이렇게 했을 때, 596ms로 AC를 받는다.
==> 스택에 주소를 넣고빼는 과정에서 시간이 오래걸림
*/
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int T, K, cost[501], cache[501][501], sum[501];

int sol(int s, int e) {
	if (s == e)return cache[s][e] = 0;
	if (s + 1 == e)return cache[s][e] = cost[s] + cost[e];

	int &ref = cache[s][e];

	if (ref != 0x3f3f3f3f)return ref;
	
	for (int idx = s; idx < e; idx++) {
		int left = sol(s, idx);
		int right = sol(idx + 1, e);
		ref = min(ref, left + right);
	}
    //합하면 비용이 발생하니 s~e까지의 누적합을 더해준다.
	return ref += sum[e] - sum[s - 1];
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;

	while(T--){
		memset(cache, 0x3f, sizeof(cache));

		cin >> K;
		for (int i = 1; i <= K; i++) {
			cin >> cost[i];
			sum[i] = sum[i - 1] + cost[i];
		}
		cout << sol(1, K) << "\n";
	}

	return 0;
}

/*
bottom-up방식

cache[a][b] : a~b페이지를 합했을때의 최소비용
위와 동일한 방법으로 cache[a][b]는 a와 b사이의 임의의값 idx를 기준으로 양옆의 값을 합한값이 된다.(a <= idx < b)
따라서 a와 b의 차이를 1부터 K-1까지 차례로 늘려주고 그 사이의 idx값을 완전탐색한다.
bottom-up방식의 특성상 차이가 a~b보다 적은것들은 이미 구해져있다.

이렇게 구현했을 때 144ms로 AC받음
*/
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int T, K, cost[501], cache[501][501], sum[501];



int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;

	while(T--){
		cin >> K;
		for (int i = 1; i <= K; i++) {
			cin >> cost[i];
			sum[i] = sum[i - 1] + cost[i];
		}
		
		for (int offset = 1; offset < K; offset++) {
			for (int i = 1; i <= K - offset; i++) {
				int j = i + offset;
				cache[i][j] = INF;
				for (int idx = i; idx < j; idx++) {
					cache[i][j] = min(cache[i][j], cache[i][idx] + cache[idx + 1][j] + sum[j] - sum[i - 1]);
				}
			}
		}
		cout << cache[1][K] << "\n";
	}

	return 0;
}

/*
bottop-up 방식 + Knuth optimization

Knuth optimization : 동적계획법을 사용하는 배열이 다음과 같은 성질을 유지할 때 활용할 수 있는 최적화 기법
1. DP가 다음과 같은 형식을 유지해야 함 : (i < k < j) DP[i][j] = min(DP[i][k], DP[k][j]) + C[i][j]
2. 사각부등식 : C[a][c] + C[b][d] <= C[a][d] + C[b][c] (a <= b <= c <= d)
3. 단조성 : C[b][c] <= C[a][d] (a <= b <= c <= d)

이를 적용하기 위해 cache배열을 다음과 같이 수정한다.
cache[i][j] : i+1부터 j까지의 페이지를 합했을때 얻을 수 있는 최소비용(i < k < j를 유지하기 위함)

그리고 num[i][j]를 다음과 같이 정의해준다.
num[i][j] : DP[i][j]를 최소값으로 유지해주는 인덱스
이렇게 되면 num[i][j]는 다음과 같은 성질을 유지한다.

num[i][j-1] <= num[i][j] <= num[i+1][j]
==>
K가 7일때
1  2  3  4   5   6  7
<--num[i][j-1]--->
 <-- num[i][j] --->
   <--num[i+1][j]--->

num[i][j]를 정의해주면 위의 bottom-up방식이 k를 찾기위해 N의 소요시간을 유지하는 반면 num[i][j-1] ~ num[i+1][j]까지의 k값은 매우 범위가 좁기때문에 O(N^2)안에 해결가능하다.

그리고 sum[i][j]가 사각부등식과 단조성을 유지하는지 확인한다.
1. 사각부등식
 sum[a][c] : a+b+c
 sum[b][d] : b+c+d
 = a+b+b+c+c+d
 
 sum[a][d] : a+b+c+d
 sum[b][c] : b+c
 = a+b+b+c+c+d 이기때문에 사각부등식을 만족한다.

2. 단조성
 sum[b][c] <= sum[a][d]는 b+c <= a+b+c+d 이기때문에 성립하는게 자명하다.
 
따라서 다음과 같이 구현할 수 있다.

Knuth optimization 을 적용할경우 8ms로 AC를 받을수 있다.
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int T, K, cost[501], cache[501][501], sum[501], num[501][501];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;

	while(T--){
		cin >> K;
		for (int i = 1; i <= K; i++) {
			cin >> cost[i];
			sum[i] = sum[i - 1] + cost[i];
		}
		
        //num[i-1][i] == i인이유는 DP[i-1][i]는 i~i까지의 최소비용을 뜻하기 때문에 i로 초기화해야한다.
		for (int i = 1; i <= K; i++)num[i - 1][i] = i;

        //offset이 2부터 시작하는 이유는 DP[i][j]가 i+1~j 까지의 최소비용이기때문
		for (int offset = 2; offset <= K; offset++) {
            //따라서 i도 0부터 시작한다.
			for (int i = 0; i <= K - offset; i++) {
				int j = i + offset;
				cache[i][j] = INF;

				for (int idx = num[i][j-1]; idx <= num[i+1][j]; idx++) {
					int temp = cache[i][idx] + cache[idx][j] + sum[j] - sum[i];
					if (cache[i][j] > temp) {
						cache[i][j] = temp;
						num[i][j] = idx;
					}
				}
			}
		}
		cout << cache[0][K] << "\n";
	}

	return 0;
}