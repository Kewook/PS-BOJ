/*
G = (r * r) - (l * l)
처음에는 r과 l의 범위가 무한일거라 생각했다.
그냥 투포인터로 모든 범위를 구해주면 되는데 "종료조건"을 잘찾아야 한다는 점이 관건이 됐다.

이 문제의 투포인터는 다음과 같이 동작한다.
1. 만약 diff(r^2 - l^2)가 G보다 같거나 크다면 l을 늘려서 G에 맞게끔 줄여준다.
2. 만약 diff가 G보다 작다면 r을 늘려줘서 범위를 늘려준다.
3. diff가 여전히 G보다 크다면 범위를 줄여야 하는데 l과 r이 인접해있다면 종료해준다. (R을 늘려봤자 당연히 diff가 커지는데 그러면 다시 l을 줄여야하는데 이렇게 되면 무한히 동작함)

몸무게는 당연히 자연수니까 l 과 r을 1로 초기화 해야한다.
*/
#include<iostream>

using namespace std;

int G;
long long l, r;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> G;
	
	l = r = 1;
	bool flag = false;
	while (true) {
		long long diff = (r*r) - (l*l);
		if (l + 1 == r && diff > G)break;
		if (diff >= G)l++;
		else r++;
		if (diff == G) {
			flag = true;
			cout << r << "\n";
		}
	}

	if (!flag)cout << -1;
	return 0;
}