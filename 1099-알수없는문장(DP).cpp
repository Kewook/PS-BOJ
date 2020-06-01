/*
dp[i]는 0~i-1까지 자리중 만들수 있는 비용중 최소비용

i = 0~str.size()만큼 루프문을 돌려주며
j = i자리부터 거꾸로 검사해주는게 관건이다.
j 를 0부터 i까지 오름차순으로 dp를 갱신하면 1~5자리중 3~5자리는 만들수 있는데 1~2자리까지는 만들수 없는 경우를 검사해주지 못한다.
따라서 j는 i부터 내림차순으로 검사해줘야함.

*/
#include<iostream>
#include<string>

const int INF = 987654321;

using namespace std;

int dp[51], N, cnt[51][26];
string str, word[51];

bool isTrue(int num, int *temp) {
	for (int i = 0; i < 26; i++) {
		if (cnt[num][i] != temp[i])return false;
	}
	return true;
}

int min(int a, int b) { return a < b ? a : b; }

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> str;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> word[i];
		for (int j = 0; j < word[i].size(); j++) cnt[i][word[i][j] - 'a']++;
	}
	
    //dp배열 초기화
	for (int i = 0; i <= str.size(); i++)dp[i] = INF;
	
	dp[0] = 0;
	for (int i = 0; i < str.size(); i++) {
		int temp[26] = {};
        //i부터 0까지 내림차순
		for (int j = i; j >= 0; j--) {
			temp[str[j] - 'a']++;
			
            //단어를 하나하나 끼워맞출게 있는지 확인.
			for (int z = 0; z < N; z++) {
				if (isTrue(z, temp)) {
                    //가능하면 비용이 얼만지 계산해서 dp 갱신
					int cost = 0;
					for (int k = j; k <= i; k++) if (str[k] != word[z][k - j])cost++;
                    //만약 앞부분이 INF로 못만들면(dp[j]가 INF일때) 어차피 갱신이 되지 않는다.
					dp[i + 1] = min(dp[i + 1], dp[j] + cost);
				}
			}
		}
	}

	if (dp[str.size()] == INF)cout << -1;
	else cout << dp[str.size()];

	return 0;
}