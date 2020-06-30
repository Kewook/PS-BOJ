#include<iostream>
#include<string>

using namespace std;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	string str;
	cin >> str;

	for (int i = 0; i < str.size() / 2; i++) {
		int j = str.size() - i - 1;
		if (str[i] != str[j]) {
			cout << 0;
			return 0;
		}
	}

	cout << 1;
	return 0;
}