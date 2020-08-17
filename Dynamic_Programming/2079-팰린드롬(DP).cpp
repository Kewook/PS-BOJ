/*
1509번문제와 동일.
*/
#include<iostream>
#include<string>

using namespace std;

string str;
int result[2002];
bool cache[2002][2002];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> str;
	str = " " + str;
	
	for (int i = 1; i < str.size(); i++)cache[i][i] = true;
	for (int i = 1; i < str.size(); i++)if (str[i] == str[i + 1])cache[i][i + 1] = cache[i + 1][i] = true;

	for (int i = 2; i < str.size() - 1; i++) {
		for (int j = 1; j < str.size() - i; j++) {
			if (str[j] == str[j + i] && cache[j + 1][j + i - 1])cache[j][j + i] = cache[j + i][j] = true;
		}
	}

	for (int i = 1; i < str.size(); i++) {
		for (int j = 1; j <= i; j++) {
			if (cache[j][i]) {
				if (result[i] == 0 || result[i] > result[j - 1] + 1)result[i] = result[j - 1] + 1;
			}
		}
	}
	cout << result[str.size() - 1];
}