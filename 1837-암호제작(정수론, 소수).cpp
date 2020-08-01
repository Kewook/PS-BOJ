/*
P의 길이가 100이 넘으니 long long자료형으로도 불가능해서 string 객체를 이용한다.

만약 P가 K보다 작은 수로 나누었을때 나눠떨어지면 BAD를 출력하고 아니면 GOOD을 출력한다.
GOOD를 바로 출력하는 이유는 모든 수는 소수의 곱으로 표현이 가능하는 전제를 기준으로 설명이 가능하다.
*/
#include<iostream>
#include<string>

using namespace std;

string P;
int K;
bool check[1000001];

//나눠떨어지는지 확인하는 함수 반복문
bool divstr(int div) {
	int remain = 0;

	for (int i = 0; i < P.size(); i++) {
		remain *= 10;
		remain += P[i] - '0';
		remain %= div;
	}
	return remain == 0 ? true : false;
}

//재귀문
bool divstr_recur(int idx, int rem, int div) {
	if (idx >= P.size()) {
		if (rem)return false;
		else return true;
	}
	return divstr(idx + 1, (rem * 10 + P[idx] - '0') % div, div);
	
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);


	cin >> P >> K;

	for (int i = 2; i <= K; i++) {
		if (check[i])continue;
		for (long long j = (long long)i * i; j <= K; j += i) {
			if (check[j])continue;
			check[j] = true;
		}
	}

	for (int i = 2; i < K; i++) {
		if (check[i])continue;
		if (divstr(i)) {
			cout << "BAD " << i << "\n";
			return 0;
		}
	}

	cout << "GOOD";

	return 0;
}