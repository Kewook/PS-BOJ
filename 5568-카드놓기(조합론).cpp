/*
모든 순열에서 K개만 고른 조합을 구해줘야한다.
map을 활용해서 중복여부를 파악한다.

4ms AC
*/

#include<iostream>
#include<string>
#include<map>

using namespace std;

int N, K, ans, num[10], root[10];
map<string, bool> mp;
bool check[10];

void sol(int idx, int cnt) {
	if (cnt == K) {
		string str;
		for (int i = 0; i < K; i++)str += to_string(num[root[i]]);

		if (!mp[str])++ans, mp[str] = true;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (check[i])continue;
		check[i] = true;
		root[cnt] = i;
		sol(i, cnt + 1);
		check[i] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++)cin >> num[i];
	
	ans = 0;
	sol(0, 0);
	cout << ans;
	return 0;
}

/*
STL의 next_permutation을 이용해서 구한 방법
672ms AC
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

int N, K, num[10], ans;
map<string, bool> mp;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++)cin >> num[i];
	sort(num, num + N);

	ans = 0;
	do{
		string str;

		for (int i = 0; i < K; i++)str += to_string(num[i]);
		if (!mp[str])++ans, mp[str] = true;
	} while (next_permutation(num, num + N));

	cout << ans;	
	return 0;
}