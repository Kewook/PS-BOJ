/*
처음에는 loop문을 i = 1~N까지 돌려주면서 mp[i]를 찾으려고 했다.
하지만 top-down 방법을 사용하면 그럴필요가 없다.
N은 이진트리로 쪼개지며 각각의 값은 계속해서 사용할 수 있으니 메모이제이션을 통해 빠르게 구하면 된다.

하지만 N의 값이 10^12이니 배열의 선언 범위를 넘어선다. N중에서 사용하지 않는 배열의 부분을 버리기 위해
map을 사용한다.
*/
#include<iostream>
#include<map>

using namespace std;

long long N;
int P, Q;
map<long long, long long> mp;

long long getNum(long long num) {
	if (mp[num])return mp[num];
	else return mp[num] = getNum(num / P) + getNum(num / Q);
}

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> P >> Q;
	mp[0] = 1;
	
	cout << getNum(N);
	return 0;
}