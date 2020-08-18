/*
처음에는 그리디라고 생각했다. 하지만 10 - 25로 봐도 앞의 액수와 뒤 액수가 배수관계가 성립하지 않아 그리디로 접근할 수 없다.

풀이법을 보고 좀 새롭다고 느꼈다.
       1
      10
      25
--------
    1|00
   10|00
   25|00
--------
 1|00|00
10|00|00
25|00|00

동전을 세개씩 끊어서 본다면 각각 배수가 성립하는 것을 알 수 있다.

두자리씩 끊어서 동전을 지불하면 된다. 또한 다른 두자리는 각자 다른 두자리에 영향을 끼치지 않는다.
두자리씩 끊어서 동전의 개수를 계산하면 되는데 예를들어 12345678원의 비용을 내기 위해 맨 아래서부터 두자리씩 끊으면 다음과 같다.
처음 두자리인 12만 본다면 1000000, 10000000, 25000000의 동전이 아니라 두자리를 추가한 동전을 지불하여 낼 수 있다는 뜻이다(Greedy)

따라서 cache를 다음과 같이 정의한다.
(0 < i < 100)cache[i] : 1, 10, 25 동전으로 i원을 지불할 때 쓰이는 최소 동전 수

그리고 두자리씩 끊어보면 된다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

int cache[100], coin[3] = { 1,10,25 }, T;
long long cost;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 1; i < 100; i++) {
		cache[i] = 100;
		for (int j = 0; j < 3; j++) {
			if (i - coin[j] >= 0)cache[i] = min(cache[i], cache[i - coin[j]] + 1);
		}
	}

	cin >> T;
	while (T--) {
		cin >> cost;

		int ans = 0;
		while (cost) {
			ans += cache[cost % 100];
			cost /= 100;
		}
		cout << ans << "\n";
	}

	return 0;
}