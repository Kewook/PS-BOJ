#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int N, ans;
bool check[26];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	string str;

	ans = 0;
	for (int i = 0; i < N; i++) {
		cin >> str;
		str = " " + str;
		
		bool flag = true;
		memset(check, false, sizeof(check));
		for (int j = 1; j < str.size(); j++) {
			if (str[j-1] != str[j] && check[str[j] - 'a']) {
				flag = false;
				break;
			}
			check[str[j] - 'a'] = true;
		}
		if (flag)++ans;
	}
	
	cout << ans;
	
	return 0;
}