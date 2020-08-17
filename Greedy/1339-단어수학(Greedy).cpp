/*
각 알파벳이 등장할 때마다 자리수를 기준으로 점수를 부여하고 greedy하게 답을 계산한다.
*/
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int N, preq[26];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;

	string str;
	while (N--) {
		cin >> str;
		for (int i = str.size() - 1, idx = 1; i >= 0; i--, idx *= 10)preq[str[i] - 'A'] += idx;
	}

	sort(preq, preq + 26);

	int ans = 0;
	for (int i = 25, j = 9; i >= 0; i--, j--) ans += preq[i] * j;

	cout << ans;	
	return 0;
}