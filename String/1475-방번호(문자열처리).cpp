/*
ceil에 값을 넘겨줄때는 실수형으로 넘겨주어야한다
형변환 필수
*/
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int cnt[10];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	string str;
	cin >> str;
	
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '6')cnt[9]++;
		else cnt[str[i] - '0']++;
	}

	int ans = 0;
	for (int i = 0; i <= 8; i++) ans = ans < cnt[i] ? cnt[i] : ans;
	ans = ans < ceil((float)cnt[9] / 2) ? ceil((float)cnt[9] / 2) : ans;

	cout << ans;
	return 0;
}