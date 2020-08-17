/*
9251의 방식을 이용해서 cache값을 갱신한다.

cache값은 철저히 bottom-up방식으로 앞전의 길이에서 문자가 같을시 길이를 추가해주었기 때문에 최장 공통부분수열을 알고싶을때는 cache값을 역추적하면 가능하다.

cache[str1.size()][str2.size()]부터 시작하며 str1의 끝과 str2의 끝을 문자한개씩 비교해준다.
만약 왼쪽의 cache값 (cache[i-1][j])과 같으면 i--를 통해 str2의 문자를 한개 제외해서 비교해준다.
만약 위쪽의 cache값 (cache[i][j-1])과 같으면 j--를 통해 str1의 문자를 한개 제외해서 비교해준다.
둘다 아닐경우엔 대각선의 길이 +1이 되었다는 뜻인데 이는 현재 비교하고있는 str1과 str2의 끝문자가 같다는 얘기다.

i--는 문자열2의 끝문자를 하나 제외해서 비교하겠다는 뜻이고
j--는 문자열1의 끝문자를 하나 제외해서 비교하겠다는 뜻이다.
아래 표를 보면 이해가 쉽다.

ex)
str1 == ACAYKP
str2 == CAPCAK일때,

  C A P C A K -
A 0 0 0 0 0 0 0
C 0 0 1 1 1 1 1
A 0 1 1 1 2 2 2
Y 0 1 2 2 2 3 3
K 0 1 2 2 2 3 3
P 0 1 2 2 2 3 4
- 0 1 2 3 3 3 4
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

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
	
	int idx1 = str1.size(), idx2 = str2.size();
	while (idx1 != 0 && idx2 != 0) {
		if (cache[idx1][idx2] == cache[idx1 - 1][idx2])idx1--;
		else if (cache[idx1][idx2] == cache[idx1][idx2 - 1])idx2--;
		else ans.push_back(str1[idx1 - 1]), idx1--, idx2--;
	}

	for (int i = ans.size() - 1; i >= 0; i--)cout << ans[i];
	return 0;
}