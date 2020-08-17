/*
처음에는 2중 loop문을 이용해서 한글자와 매치되는 글자가 있는지 찾고 만약 찾는 와중에 이미 check된게 있으면 좋은단어가 아닌식으로 진행함
반례 :
1
BABBAB
--> 스택을 이용하면 바로 풀수있다.
*/
#include<iostream>
#include<string>
#include<stack>

using namespace std;

int N, ans;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	ans = 0;

	for (int t = 0; t < N; t++) {
		string str;
		cin >> str;

		stack<char> s;

		for (int i = 0; i < str.size(); i++) {
			if (s.empty())s.push(str[i]);
			else if (s.top() == str[i])s.pop();
			else s.push(str[i]);
		}
		if (s.empty())++ans;
	}
	
	cout << ans;
	return 0;
}