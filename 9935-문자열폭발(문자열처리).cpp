/*
단어의 최대길이가 1000000이기 때문에 아래의 반례에서는 1000000 * 500000의 시간복잡도가 필요하다.
반례)
AAAAA...ABBBBBBB....BBB
AB

1. 스택을 이용하면 바로 풀수있다. 252ms
2. 폭발 문자열의 끝문자와 같은 문자가 나올때 그 앞에 연속된 문자들이 폭발 문자열과 같다면 폭발시켜준다. 32ms
*/
#include<iostream>
#include<string>

using namespace std;

char ans[1000001];
int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);


	string str, bomb;
	cin >> str >> bomb;

	int idx = 0;
	for (int i = 0; i < str.size(); i++) {
		ans[idx] = str[i];

		if (str[i] == bomb[bomb.size() - 1]) {
			int nidx = idx - 1;
			for (int j = bomb.size() - 2; (j >= 0 && nidx >= 0); j--, nidx--) if (bomb[j] != ans[nidx])break;
			if (idx - bomb.size() == nidx) {
				idx = idx - bomb.size() + 1;
				continue;
			}
		}
		idx++;
	}

	if (!idx)cout << "FRULA";
	else for (int i = 0; i < idx; i++)cout << ans[i];
	
	return 0;
}