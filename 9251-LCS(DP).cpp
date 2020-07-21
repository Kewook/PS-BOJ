/*
문자열1과 문자열2의 길이를 각각 한개씩 순서대로 늘려가면서 길이를 갱신해주면 된다.
cache[i][j] : str1을 i-1까지 str2를 j-1까지 비교했을때 최장 공통 부분수열의 최대길이

cache값을 갱신하기 위해서는
str1[i] == str2[j]일경우엔 문자가 같기 때문에 각자 문자한개씩 없을때의 최대길이인 cache[i-1][j-1]보다 +1을 더해준다.
만약 문자열이 다를경우 문자가 다르기때문에 bottom-up방식을 유지하기 위해서 각 문자열에서 문자한개씩 없을때의 길이중 큰것으로 갱신해준다.
*/
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int cache[1001][1001];
string str1, str2;
vector<char> ans;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> str1 >> str2;

	for (int i = 1; i <= str1.size(); i++) {
		for (int j = 1; j <= str2.size(); j++) {
			if (str1[i - 1] == str2[j - 1])cache[i][j] = cache[i - 1][j - 1] + 1;
			else cache[i][j] = max(cache[i - 1][j], cache[i][j - 1]);
		}
	}

	cout << cache[str1.size()][str2.size()] << "\n";
	return 0;
}