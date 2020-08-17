/*
예외처리가 많은 문제

cache[i] = i번째 자리까지 확인했을때 만들수있는 암호 경우의수
각 자리 하나하나 확인하는데 만약 앞자리와 붙일수 있다면 이전에 나왔던 경우와 지금 만들수 있는 경우를 더해주어야 한다.
아닌경우에는 그냥 앞자리와 동일하게 해준다
=> if(붙일수있나?) cache[i] = cache[i-1] + cache[i-2];
   else cache[i] = cache[i-1];

예외처리부분
첫자리가 0으로 시작하면 무조건 0출력 (code line 30)
0일때 앞자리가 0이거나 3이상이면 잘못된 수 (code line 32)
0일때 앞자리와 붙일수 있다면 i-2번째의 값과 동일하게 해야한다.(i-1번째 앞자리와 붙여줄수 있었다면 그 수가 더해졌을것) (code line 33)
*/
#include<iostream>
#include<string>

using namespace std;

string num;
const int MOD = 1000000;
int cache[5001];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> num;
	
	if (num[0] != '0') {
		cache[0] = cache[1] = 1;
		for (int i = 2; i <= num.size(); i++) {
			if (num[i - 1] == '0' && (num[i - 2] == '0' || num[i - 2] > '2'))continue;
			else if (num[i - 1] == '0')cache[i] = cache[i - 2];
			else if (num[i-2] != '0' && (num[i - 1] - '0' + (num[i - 2] - '0') * 10) >= 1 && (num[i - 1] - '0' + (num[i - 2] - '0') * 10) <= 26)cache[i] = (cache[i - 2] + cache[i - 1]) % MOD;
			else cache[i] = cache[i - 1];
		}
	}
	
	cout << cache[num.size()];

	return 0;
}