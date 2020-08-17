/*
9251문제와 유사하게 풀면된다.
*/
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int cache[101][101][101];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	string str1, str2, str3;
	cin >> str1 >> str2 >> str3;

	for (int i = 1; i <= str1.size(); i++) {
		for (int j = 1; j <= str2.size(); j++) {
			for (int k = 1; k <= str3.size(); k++) {
				if ((str1[i - 1] == str2[j - 1]) && (str1[i - 1] == str3[k - 1]))cache[i][j][k] = cache[i - 1][j - 1][k - 1] + 1;
				else cache[i][j][k] = max(cache[i - 1][j][k], max(cache[i][j - 1][k], cache[i][j][k - 1]));
			}
		}
	}

	cout << cache[str1.size()][str2.size()][str3.size()];
	return 0;
}