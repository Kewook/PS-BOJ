/*
시간초과 이유
15개 완탐하면 시간이 매우 부족할 수 있다.

낮일때 Max 초기값을 num[0]라고 주어짐 이러면 0번 플레이어가 이미 죽었는데도 계속 선택될 수 있기때문에 시간초과가 발생.
--> 초기값 설정하는거 신경쓰자.
*/
#include<iostream>

using namespace std;

int N, ans, num[21], R[21][21], mafia;
bool check[21];

void dfs(int cnt, int night) {
	if (check[mafia] || cnt == 1) {
		ans = ans < night ? night : ans;
		return;
	}

    //낮
	if (cnt % 2 == 1) {
		int idx;
		int Max = -987654321;
		for (int i = 0; i < N; i++) {
			if (Max < num[i] && !check[i])Max = num[i], idx = i;
		}

		check[idx] = true;
		dfs(cnt - 1, night);
		check[idx] = false;
	}
	
    //밤
	if (cnt % 2 == 0) {
		for (int i = 0; i < N; i++) {
			if (check[i])continue;
			check[i] = true;
			for (int j = 0; j < N; j++) {
				num[j] += R[i][j];
			}
			dfs(cnt - 1, night + 1);
			check[i] = false;
			for (int j = 0; j < N; j++) {
				num[j] -= R[i][j];
			}
		}
	}
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	ans = 0;
	cin >> N;
	
	for (int i = 0; i < N; i++)cin >> num[i];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)cin >> R[i][j];
	}
	cin >> mafia;
	
	dfs(N, 0);

	cout << ans;
	return 0;
}

////////더 유용한 풀이/////////////

/*
1. 은진이를 밤에 죽이면 가지수가 더 많아짐 이를 줄인다. => 조금 줄어듬
2. 만약에 은진이 혼자 남아있는 경우가 생기면 이 case는 가장 많이 살아남은 경우이므로 
   전역변수 flag를 두어 모든 가지수를 탐색하지 않게 해준다.
*/

#include<iostream>

using namespace std;

int N, ans, num[21], R[21][21], mafia;
bool check[21], flag;

void dfs(int cnt, int night) {
    if(flag) return;
    
	if (check[mafia] || cnt == 1) {
		ans = ans < night ? night : ans;
        if(cnt == 1)flag = true;
		return;
	}

	if (cnt % 2 == 1) {
		int idx;
		int Max = -987654321;
		for (int i = 0; i < N; i++) {
			if (Max < num[i] && !check[i])Max = num[i], idx = i;
		}

		check[idx] = true;
		dfs(cnt - 1, night);
		check[idx] = false;
	}
	
	if (cnt % 2 == 0) {
		for (int i = 0; i < N; i++) {
            if(flag) return;
			if (check[i] || i == mafia)continue;
			check[i] = true;
			for (int j = 0; j < N; j++) num[j] += R[i][j];
			dfs(cnt - 1, night + 1);
			check[i] = false;
			for (int j = 0; j < N; j++) num[j] -= R[i][j];
		}
	}
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	ans = 0;
	cin >> N;
	
	for (int i = 0; i < N; i++)cin >> num[i];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)cin >> R[i][j];
	}
	cin >> mafia;
	
	dfs(N, 0);

	cout << ans;
	return 0;
}