#include<iostream>
#include<string>

using namespace std;

string str1, str2;

int calc(int idx) {
	int score = 0;
	for (int i = idx; i < str1.size() + idx; i++) if (str1[i - idx] != str2[i])++score;
	return score;
}


int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> str1 >> str2;
	
	if (str1 == str2)cout << calc(0);
	else {
		int min = 987654321;
		for (int i = 0; i <= str2.size() - str1.size(); i++) {
			int score = calc(i);
			min = min > score ? score : min;
		}
		cout << min;
	}

	return 0;
}