/*
어떤 정수 N이 30의 배수 == (각자리숫자의 합이 3의배수 && 0이존재하지 않음)
*/
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

string str;

bool isTrue() {
	bool zero = false;
	int sum = 0;
	for (char c : str) {
		if (!(c - '0'))zero = true;
		else sum += (c - '0');
	}
	if (zero && !(sum % 3))return true;
	else return false;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> str;
	
	if (isTrue()) {
		sort(str.begin(), str.end());
		for (int i = str.size() - 1; i >= 0; i--)cout << str[i];
	}
	else cout << -1;

	return 0;
}