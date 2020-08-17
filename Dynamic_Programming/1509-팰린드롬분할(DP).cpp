/*
1. cache[i][j] = str[i] ~ str[j]가 팰린드롬인지 알려주는 boolean배열
2. 자기자신과 바로 옆에있는 문자끼리는 바로 비교가능하니 초기화함.
3. 차이가 2씩 나는 문자부터 str.size()-2씩 나는 문자까지 cache를 갱신한다.
 --> 첫번째 문자와 마지막 문자가 같다면 첫번째 문자와 마지막 문자를 제외한 가운데 문자열이 팰린드롬이면 그 부분문자열은 팰린드롬이다.
 --> abccba에서 첫번째 a와 마지막 a가 같고 가운데 부분문자열이 팰린드롬이므로 이 문자열은 팰린드롬이다.
4. result[i]는 i번째 문자까지 팰린드롬의 최소 개수임.
 --> result[i]가 0일때 한번도 비교하지 않은것임.
 --> cache[j][i]가 true이고 j-1번째의 최소개수가 현재 result[i]보다 작으면 새로 갱신해준다.
*/
#include<iostream>
#include<string>

using namespace std;

string str;
int result[2502];
bool cache[2502][2502];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> str;
	str = " " + str;
	
	for (int i = 1; i < str.size(); i++)cache[i][i] = true;
	for (int i = 1; i < str.size(); i++)if (str[i] == str[i + 1])cache[i][i + 1] = cache[i + 1][i] = true;

	for (int i = 2; i < str.size() - 1; i++) {
		for (int j = 1; j < str.size() - i; j++) {
			if (str[j] == str[j + i] && cache[j + 1][j + i - 1])cache[j][j + i] = cache[j + i][j] = true;
		}
	}

	for (int i = 1; i < str.size(); i++) {
		for (int j = 1; j <= i; j++) {
			if (cache[j][i]) {
				if (result[i] == 0 || result[i] > result[j - 1] + 1)result[i] = result[j - 1] + 1;
			}
		}
	}
	cout << result[str.size() - 1];
}