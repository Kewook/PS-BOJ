/*
소수를 분수로 만드는 방법
(순환소수를 포함한 모든 부분) - (순환소수를 제외한 부분) / (순환소수만큼 9붙이고 비순환소수만큼 0붙이기)
ex)
1.1(123) ==> (11123 - 11) / (9990)

long long형으로 선언을 해야한다. 그렇지 않으면 divide by 0의 케이스가 생겨 런타임에러가 발생함.
*/
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

long long gcd(long long a, long long b) {
	return a % b ? gcd(b, a%b) : b;
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	while (T--) {
		string str;
		cin >> str;

		string s1, s2;
		bool flag = false;

		for (int i = 2; i < str.size(); i++) {
			if (str[i] == '(' || str[i] == ')') {
				flag = true;
				continue;
			}
			s1 += str[i];
			if (!flag)s2 += str[i];
		}

		long long c, p, num1, num2 = 0;
		num1 = stol(s1);
		if (s2.size())num2 = stol(s2);

		//순환소수가 있을경우 분모
		if (flag) {
			string temp;
			for (int i = 0; i < s1.size() - s2.size(); i++)temp += '9';
			for (int i = 0; i < s2.size(); i++)temp += '0';
			p = stol(temp);
		}
		//순환소수가 없을경우 분모
		else p = (long long)pow(10, s2.size());

        //비순환소수만 있는경우
		if (!flag) c = num1;
        //순환만 있는경우 or 둘다 포함한경우
		else c = num1 - num2;
		
		long long div = gcd(p, c);
		cout << c / div << "/" << p / div << "\n";
	}

	return 0;
}