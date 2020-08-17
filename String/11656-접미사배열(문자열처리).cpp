#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

vector<string> ans;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	string str;
	cin >> str;

	for (int i = 0; i < str.size(); i++) ans.push_back(str.substr(i, str.size() - i));
	sort(ans.begin(), ans.end());

	for (auto &iter : ans) cout << iter << "\n";
	return 0;
}