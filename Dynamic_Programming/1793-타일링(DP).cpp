/*
문제유의사항 : N이 0일때 output은 1이다.
==> 방법의수이므로
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int N;
string cache[251] = { "1", "1", "3" };

string add(string str1, string str2) {
	string ans;

	int carry = 0;

	for (int i = str1.size() - 1, j = str2.size() - 1; i >= 0; i--, j--) {
		int sum = carry + (str1[i] - '0') + (str2[j] - '0');
		ans.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	if (str1.size() == str2.size() && carry)ans.push_back(carry + '0');

	for (int i = str2.size() - str1.size() - 1; i >= 0; i--) {
		int sum = carry + str2[i] - '0';
		ans.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 3; i <= 250; i++) cache[i] = add(cache[i - 1], add(cache[i - 2], cache[i - 2]));

	while (true) {
		cin >> N;
		if (cin.fail())break;

		cout << cache[N] << "\n";
	}
	
	return 0;
}