/*
확장 유클리드 알고리즘을 이용해서 문제풀이를한다.
*/
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int K, C;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

long long xgcd(int a, int b) {
	long long r, q, s, t, s1 = 1, s2 = 0, t1 = 0, t2 = 1;

    //K가 C보다 크다는 조건이 없다.
	bool flag = false;
	if (a < b) {
		swap(a, b);
		flag = true;
	}

	
	while (b) {		
		q = a / b;
		r = a % b;
		s = s1 - s2 * q;
		t = t1 - t2 * q;

		s1 = s2;
		s2 = s;
		t1 = t2;
		t2 = t;
		a = b;
		b = r;
	}
	
    //t1으로 값이 이동되어있는거 주의
	if (flag) {
		while (t1 < 0)t1 += K;
		return t1;
	}
	else {
		while(s1 < 0)s1 += K;
		return s1;
	}
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;

	while (t--) {
		cin >> K >> C;
		
		long long ans;
		if (gcd(K, C) != 1) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		else if (C == 1) {
            //K + 1이 10억을 넘어갈때 사탕봉지가 10억 이상개 필요하므로
			if (K + 1 > 1e9)cout << "IMPOSSIBLE\n";
            //아니면 그냥 K+1봉지가 필요
			else cout << K + 1 << "\n";
			continue;
		}
		else if(K == 1){
            //줄 사람이 한명이면 무조건 사탕봉지 하나면 된다. (사탕봉지에 들어있는 수 - 1 만큼 한사람에게 주면된다.) 
			cout << 1 << "\n";
			continue;
		}
		else ans = xgcd(C, K);
		
		if (ans > 1e9)cout << "IMPOSSIBLE\n";
		else cout << ans << "\n";
	}
	return 0;
}