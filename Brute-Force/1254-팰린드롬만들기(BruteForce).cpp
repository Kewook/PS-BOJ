/*
문자열의 길이가 1000밖에되지 않기때문에 naive하게 접근하면 O(N^2)으로 접근이 가능하기 때문에 브루트포스로 문제해결이 가능하다.

하지만 나는 DP로 접근했고 cache는 다음과 같이 정의된다.
cache[i][j] : i~j까지가 팰린드롬인지 확인하는 boolean배열

문자열 뒤에 한개씩 문자를 추가해보며 만약 추가한 문자 길이를 제외한 그 사이가 팰린드롬이면 종료하게끔 했다.
....[팰린드롬이 가능하면 앞의 문자열과 같은 문자열 추가가능]....
*/
#include<iostream>
#include<string>

using namespace std;

string str;
bool cache[1005][1005];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> str;

	str += " ";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == str[i + 1])cache[i + 1][i] = cache[i][i + 1] = true;
		cache[i][i] = true;
	}

	for (int offset = 2; offset <= str.size() - 2; offset++) {
		for (int i = 0; i + offset < str.size() - 1; i++) {
			int j = i + offset;
			if (str[i] == str[j] && cache[i + 1][j - 1])cache[j][i] = cache[i][j] = true;
		}
	}
	
	if (cache[0][str.size() - 2])cout << str.size() - 1;
	else {
		int len = 1;
		while (true) {
			if (cache[len][str.size() - 2])break;
			len++;
		}

		cout << str.size() + len - 1;
	}
	return 0;
}