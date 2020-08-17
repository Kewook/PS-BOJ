/*
순열 : 1부터 N까지의 숫자 중에서 중복을 허락하지 않고 모든 수를 포함해야한다. 누락도 인정안함.
수열과 순열 차이 완벽하게 할것.
따라서 최대한으로 나올수 있는 숫자를 파악하기 위해 10보다 작게 입력이 됐다면 1~9까지밖에 없는것이고
만약 아니라면 두자리수가 포함되어 있음 따라서 10이란 1부터 10을 의미하고 (max_len -10)/2는 나머지 두자리수의 최대 수를 의미한다.
*/
#include<iostream>
#include<cstring>
#include<string>

using namespace std;
string str;
int ans[100];
int cnt = 0, max_len;
bool check[100];

void sol(int idx) {
	if (idx >= str.size()) {
		for (int i = 0; i < cnt; i++) {
			cout << ans[i] << " ";
		}
		exit(0);
	}
	
	//한개 끊어줌
	if (str[idx] == '0') {
		int num = ans[cnt - 1] * 10;
		if (!check[num]) {
			check[num] = true;
			ans[cnt - 1] *= 10;
			sol(idx + 1);
			check[num] = false;
		}
	}
	if (str[idx] != '0') {
		int num = str[idx] - '0';
		if (!check[num]) {
			ans[cnt++] = num;
			check[num] = true;
			sol(idx + 1);
			check[num] = false;
			cnt--;
		}
	}
	//두개씩

	if (idx + 1 < str.size()) {
		int num1 = (str[idx] - '0') * 10, num2 = str[idx + 1] - '0';
		if (num1 + num2 <= max_len) {
			if (!check[num1 + num2]) {
				ans[cnt++] = num1 + num2;
				check[num1 + num2] = true;
				sol(idx + 2);
				check[num1 + num2] = false;
				cnt--;
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	
	
	cin >> str;
	memset(check, false, 100);
	if (str.size() < 10)max_len = str.size();
	else max_len = 10 + (str.size() - 10) / 2;

	sol(0);

	return 0;
}