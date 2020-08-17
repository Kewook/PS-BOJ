#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	while (true) {
		string str;
		stack<char> s;

		getline(cin, str);
		if (str == ".")break;

		bool flag = true;

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '(' || str[i] == '{' || str[i] == '[')s.push(str[i]);
			else if ((str[i] == ')' || str[i] == '}' || str[i] == ']') && s.empty()) flag = false;
			else if (str[i] == ')') {
				if (s.top() != '(')	flag = false;
				else s.pop();
			}
			else if (str[i] == '}') {
				if (s.top() != '{') flag = false;
				else s.pop();
			}
			else if (str[i] == ']') {
				if (s.top() != '[') flag = false;
				else s.pop();
			}
			if (!flag)break;
		}
		if (!s.empty() || !flag) cout << "no\n";
		else if (flag) cout << "yes\n";
	}

	return 0;
}