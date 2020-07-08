/*
cache[i][t][w] : t초에 위치가 i번이고 w번 움직였을때 받을수 있는 자두의 최대개수
하지만 자두나무가 2개밖에 없으므로 움직인 횟수로 어떤 위치에 있는지 알수있게 된다. 따라서 cache를 재정의할 수 있다.

cache[t][w] : t초에 w번 움직였을때 받을 수 있는 자두의 최대개수

==> 슬라이딩 윈도우를 적용하면 메모리 사용을 좀 더 줄일수 있다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int T, W, cache[1001][32];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T >> W;
	
	int pos;
	for (int i = 1; i <= T; i++) {
		cin >> pos;
		

		for (int j = 0; j <= W; j++) {
            //한번도 움직이지 않았을때는 자두가 나무 1에 떨어지면 1을 더해준다.
			if (j == 0) {
				cache[i][j] = pos == 1 ? cache[i - 1][j] + 1 : cache[i - 1][j];
				continue;
			}

            //j번 움직여 나무 1에 위치할 때
			if (!(j % 2)) {
                //1번나무에서 자두가 떨어지면 움직이지 않는 경우에 자두를 1개 얻을수 있다.
                //cache[i][j] = max(움직이지 않은경우 +1, 움직인경우)
				if (pos == 1)cache[i][j] = max(cache[i - 1][j] + 1, cache[i - 1][j - 1]);
				else cache[i][j] = max(cache[i - 1][j - 1] + 1, cache[i - 1][j]);
			}

			else {
				if (pos == 1)cache[i][j] = max(cache[i - 1][j - 1] + 1, cache[i - 1][j]);
				else cache[i][j] = max(cache[i - 1][j] + 1, cache[i - 1][j - 1]);
			}
		}
	}
	
	int ans = 0;
	for (int i = 0; i <= W; i++) ans = max(ans, cache[T][i]);

	cout << ans;
	return 0;
}