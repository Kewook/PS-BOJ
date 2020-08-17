/*
틀린이유, 해맨이유 : sol을 재귀호출하는 부분에서 sol(idx, cnt + 1)을 해주었는데 이렇게 하면 구해줬던것도 여러번 구해주니 시간초과가 된다.
기본적인 조합문제(Combination)도 못풀었다. 다음 sol부분은 완벽하게 숙지하자.
*/
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int n, ar[22][22];
int ans = 10e8;
bool check[22];

void sol(int idx, int cnt) {
	if (cnt == n / 2) {
		int	num = n / 2;

		int link_team[11], start_team[11];
		int start = 0, link = 0;
		int s_idx = 0, l_idx = 0;
		

		for (int i = 0; i < n; i++) {
			if (check[i])start_team[s_idx++] = i;
			else link_team[l_idx++] = i;
		}


		for (int i = 0; i < num; i++) {
			for (int j = i + 1; j < num; j++) {
				start += ar[start_team[i]][start_team[j]];
				start += ar[start_team[j]][start_team[i]];
				link += ar[link_team[i]][link_team[j]];
				link += ar[link_team[j]][link_team[i]];
			}	
		}

		int temp = abs(start - link);
		if (ans > temp)ans = temp;
		return;
	}
	
	for (int i = idx + 1 ; i < n; i++) {
		if (check[i] == false) {
			check[i] = true;
			sol(i, cnt + 1);
			check[i] = false;
		}
	}
	
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	memset(check, false, 21);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ar[i][j];
		}
	}

	sol(0, 0);
	cout << ans;
	
}