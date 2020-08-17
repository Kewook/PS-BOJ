/*
cache[i][j][k][z] : 상근이가 (i,j)위치에 k방향으로 들어왔을때 방향전환이 가능한지에 대한여부 k
k = 0이면 북쪽, 1이면 동쪽
z = 0이면 불가, 1이면 가능

따라서 4가지의 경우에 대해 모두 생각해줘야 한다.
처음으로 방향전환이 가능한지에 대한 여부로 생각해주면

방향전환이 가능할때
- 들어왔던 방향(k)의 위치에서 들어왔던 방향이 k와 같을 때 방향전환이 가능한 경우와 불가능한 경우를 모두 더해준다.
-> 들어왔던 방향이 서로 다른데 전환이 가능하면 (i,j)에 위치하긴하지만 방향전환이 불가해진다.

방향전환이 불가할때
- 들어왔던 방향(k)의 위치에서 들어왔던 방향이 다르고 방향전환이 가능한경우
*/
#include<iostream>

using namespace std;

const int MOD = 100000;
int W, H, cache[101][101][2][2];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> W >> H;
	
	for (int i = 2; i <= W; i++)cache[1][i][1][1] = 1;
	for (int i = 2; i <= H; i++)cache[i][1][0][1] = 1;

	for (int i = 2; i <= H; i++) {
		for (int j = 2; j <= W; j++) {
			cache[i][j][0][1] = (cache[i - 1][j][0][0] + cache[i - 1][j][0][1]) % MOD;
			cache[i][j][1][1] = (cache[i][j - 1][1][0] + cache[i][j - 1][1][1]) % MOD;
			cache[i][j][0][0] = cache[i - 1][j][1][1] % MOD;
			cache[i][j][1][0] = cache[i][j - 1][0][1] % MOD;
		}
	}
	
	cout << (cache[H][W][1][0] + cache[H][W][1][1] + cache[H][W][0][1] + cache[H][W][0][0]) % MOD;
	return 0;
}