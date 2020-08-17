#include<iostream>
#include<string>
#include<map>

using namespace std;

int N, M;
string str[100001];
map<string, int> mp;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> str[i];
		mp.insert({ str[i], i });
	}

	string q;
	for (int i = 0; i < M; i++) {
		cin >> q;
		if (q[0] >= '1' && q[0] <= '9')cout << str[atoi(q.c_str())] << "\n";
		else cout << mp[q] << "\n";
	}

	return 0;
}