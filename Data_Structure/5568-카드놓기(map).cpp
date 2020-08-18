/*
순열중 K개만 골라진 순열을 고르고 map을 통해 중복체크를 한다.
*/
#include<iostream>
#include<string>
#include<map>

using namespace std;

int N, K, ar[11], root[4], ans;
map<string, bool> mp;
bool check[11];


void sol(int cnt) {
	if (cnt >= K) {
		string str;
		for (int i = 0; i < K; i++)str += to_string(root[i]);
		if (!mp[str]) {
			ans++;
			mp[str] = true;
		}
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (check[i])continue;
		check[i] = true;
		root[cnt] = ar[i];
		sol(cnt + 1);
		check[i] = false;
	}
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	
	for (int i = 1; i <= N; i++)cin >> ar[i];

	sol(0);
	cout << ans;
	return 0;
}