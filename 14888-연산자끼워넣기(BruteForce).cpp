/*
틀린건 아니지만 성능이 더 좋은 코드를 확인해보자.

<285ms 나온코드>
#include<iostream>
#include<cstring>

using namespace std;

int n, num[100], op[99];
int maxnum = -10e8, minnum = 10e8;
int op_idx[99];
bool check[99];

void sol(int idx) {
	
	if (idx >= n - 1) {
		int temp = num[0];
		
		for (int i = 1; i < n; i++) {
			if (op_idx[i - 1] == 0) temp += num[i];
			else if (op_idx[i - 1] == 1)temp -=  num[i];
			else if (op_idx[i - 1] == 2)temp *=  num[i];
			else if (op_idx[i - 1] == 3)temp /=  num[i];
		}

		if (temp > maxnum)maxnum = temp;
		if (temp < minnum)minnum = temp;

		return;
	}

	for (int i = 0; i < n - 1; i++) {
		if (!check[i]) {
			check[i] = true;
			op_idx[idx] = op[i];
			sol(idx + 1);
			check[i] = false;
		}
	}
	
}

int main(void) {
	ios::sync_with_stdio(0);
	
	cin >> n;

	memset(check, false, n - 1);
	for (int i = 0; i < n; i++)cin >> num[i];
	
	//0~4 차례로 +,-,*,/
	int idx = 0;
	for (int i = 0; i < 4; i++) {
		int temp;
		cin >> temp;
		for (int j = 0; j < temp; j++) {
			op[idx++] = i;
		}
	}

	sol(0);
	cout << maxnum << endl;
	cout << minnum;

	return 0;
}
*/

//0ms 나온 참고 코드
#include<iostream>
#include<cstring>

using namespace std;

int n, num[100], op[4];
int maxnum = -10e8, minnum = 10e8;

void sol(int idx, int plus, int sub, int mul, int div, int temp) {
	if (idx >= n) {
		if (temp > maxnum)maxnum = temp;
		if (temp < minnum)minnum = temp;

		return;
	}

	if (plus > 0)sol(idx + 1, plus - 1, sub, mul, div, temp + num[idx]);
	if (sub > 0)sol(idx + 1, plus, sub - 1, mul, div, temp - num[idx]);
	if (mul > 0)sol(idx + 1, plus, sub, mul - 1, div, temp * num[idx]);
	if (div > 0)sol(idx + 1, plus, sub, mul, div - 1, temp / num[idx]);
	
}

int main(void) {
	ios::sync_with_stdio(0);
	
	cin >> n;
	for (int i = 0; i < n; i++)cin >> num[i];
	
	//0~4 차례로 +,-,*,/
	for (int i = 0; i < 4; i++) cin >> op[i];

	sol(1, op[0], op[1], op[2], op[3], num[0]);

	cout << maxnum << endl;
	cout << minnum;

	return 0;
}