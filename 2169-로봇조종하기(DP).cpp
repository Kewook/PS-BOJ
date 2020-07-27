///////// top-down ///////////

/*
일단 branch factor가 3이고 노드의 개수가 N*M이기 때문에 naive하게 접근했을때 O(3^(N*M))으로 TLE가 나온다.
위로 갈 수 없는 조건이 있기 때문에 사이클이 생기지 않는 조건이 생겨 DP를 사용할수 있다.

cache[i][j][dir] : i,j 위치에 dir방향으로 들어왔을때 얻을수있는 최대값.

cache를 ypos와 xpos로만 분리한게 아니라 방향에따라서 3차원으로 분리해준 이유는 위로 갈수 없기 때문에 들어온 방향에 따라서 갈수 있는 방향이 달라진다.
예를들어 다음과 같은 예시가있다하면
3 3
10 20 30
10 20 30
10 20 30
이 예시에서는 탐색방향이 ㄹ 방향으로 되어야만 최대값이 나올 수 있다.
들어온 방향에 비해서 갈수있는 방향이 다르기 때문에 chace[2][2]에는 (1,2)에서 바로 내려와서 오른쪽과 아래로 탐색한 60 + 20이 저장되어 있다.
이와같은 이유로 메모이제이션을 통해 ㄹ모양을 다 탐색하지 못하고 다른값이 저장된다.

cache를 2차원으로 구성하고 탐색하면 다음과 같은 좌표로 탐색한다.
1 1
2 1
3 1
3 2
3 3

2 2
3 2
2 3
3 3

1 2
2 2
1 3
2 3
output = 120

만약 4방향으로 모두 갈 수 있었다면 사이클이 생기기 때문에 다익스트라 알고리즘을 사용해서 해결해야 한다.
비슷한 문제로 1937-욕심쟁이판다 문제가 있는데 이 문제는 value가 더 높은 곳으로만 이동해야 하기 때문에 사이클이 생기지 않는 조건이 생긴다.
반면에 4485-녹색옷입은애가젤다지 문제는 4방향으로 이동하고 DAG 형식이 아니기 때문에 DP를 적용하지 못한다. 따라서 다익스트라 알고리즘을 적용해야한다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int N, M, cache[1001][1001][3], ar[1001][1001];
int dy[] = { 1,0,0 }, dx[] = { 0,-1,1 };
bool check[1001][1001];

int sol(int ypos, int xpos, int dir) {
	if (ypos == N && xpos == M)return ar[N][M];

	int &ret = cache[ypos][xpos][dir];
	if (ret != -INF)return ret;
	
	check[ypos][xpos] = true;
	for (int i = 0; i < 3; i++) {
		int ny = ypos + dy[i], nx = xpos + dx[i];
		if (ny < 1 || nx < 1 || ny > N || nx > M)continue;
		if (check[ny][nx])continue;

		ret = max(ret, sol(ny, nx, i) + ar[ypos][xpos]);
	}
	check[ypos][xpos] = false;
	return ret;	
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> ar[i][j];
			cache[i][j][0] = cache[i][j][1] = cache[i][j][2] = -INF;
		}
	}

	cout << sol(1, 1, 0);
	return 0;
}

//////// bottup-up /////////

/*
bottop-up 방식을 사용하기엔 오른쪽에서 왼쪽으로 오는 경우가 생기기 때문에 index증감을 이용해서 cache값을 갱신하기가 힘들다.

index를 오름차순으로하고 따라서 오른쪽에서 왼쪽으로 오는 경우를 대비해서 왼쪽에서부터와 오른쪽에서부터의 누적합을 저장하여 값을 비교한다.
psum[0][i] : 갱신하고있는 row에서 왼쪽에서부터의 누적합
psum[1][i] : 갱신하고있는 row에서 오른쪽에서부터의 누적합

또한 psum과 위에서 오는 값을 비교를 해주어야 한다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int N, M, cache[1001][1001], ar[1001][1001], psum[2][1001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> ar[i][j];
		}
	}

    //init
    //첫번째 row는 출발점이 속해있으니 오른쪽으로밖에 못움직인다.
	cache[1][1] = ar[1][1];
	for (int i = 2; i <= M; i++)cache[1][i] = cache[1][i - 1] + ar[1][i];
	
	for (int i = 2; i <= N; i++) {	
        //위의 값을 비교해주기 위해 위에서 내려온 값을 다 저장해준다.
		for (int j = 1; j <= M; j++)psum[0][j] = psum[1][j] = cache[i - 1][j] + ar[i][j];

        //각각 누적합을 이용해서 위에서 오는것과 왼쪽 혹은 오른쪽에서 오는 누적합을 비교해준다.
		for (int j = 2; j <= M; j++)psum[0][j] = max(psum[0][j], psum[0][j - 1] + ar[i][j]);
		for (int j = M-1; j >= 0; j--)psum[1][j] = max(psum[1][j], psum[1][j + 1] + ar[i][j]);
        
        //cache 갱신
		for (int j = 1; j <= M; j++)cache[i][j] = max(psum[0][j], psum[1][j]);
	}

	cout << cache[N][M];
	return 0;
}