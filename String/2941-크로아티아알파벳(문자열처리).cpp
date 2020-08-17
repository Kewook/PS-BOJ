#include<iostream>
#include<string>

using namespace std;

string alp[] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };
int ans;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	string str;
	cin >> str;

	ans = 0;
	for (int i = 0; i < str.size(); i++) {
		++ans;

		for (int j = 0; j < 8; j++) {
			int size = alp[j].size(), idx;
			if (i + size > str.size())continue;

			bool flag = true;
			for (idx = i; idx < i + size; idx++) if (str[idx] != alp[j][idx - i])flag = false;
			
			if (flag) {
				i = idx - 1;
				break;
			}
		}
	}
	
	cout << ans;
	return 0;
}