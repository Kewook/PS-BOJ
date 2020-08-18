/*
Disjoint-set을 사용해서 집합의 크기를 빠르게 알 수 있다.
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<cstring>

using namespace std;

int T, N, parent[200001], cnt[200001];
map<string, int> mp;

int find(int a) {
	if (parent[a] == -1)return a;
	else return parent[a] = find(parent[a]);
}

int Union(int a, int b) {
	a = find(a);
	b = find(b);
	if (a != b) {
		cnt[a] += cnt[b];
		cnt[b] += cnt[a];
		parent[b] = a;
	}
	return cnt[a];
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N * 2; i++)cnt[i] = 1, parent[i] = -1;
		int cnt = 1;
		string str1, str2;

		for (int i = 1; i <= N; i++) {
			cin >> str1 >> str2;
			int a, b;
			if (!mp[str1]) {
				a = cnt;
				mp[str1] = cnt++;
			}
			else a = mp[str1];
			if (!mp[str2]) {
				b = cnt;
				mp[str2] = cnt++;
			}
			else b = mp[str2];
			cout << Union(a, b)<<"\n";
		}
	}
	
	return 0;
}