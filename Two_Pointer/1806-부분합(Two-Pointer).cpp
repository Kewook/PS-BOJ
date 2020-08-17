/*
2003-수들의합2 문제와 비교해봐야한다.
*/
#include<iostream>

using namespace std;

int N, S, ar[100001];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> S;
	for (int i = 0; i < N; i++)cin >> ar[i];
	
	int l = 0, r = 0, ans = 100001, sum = 0;
	while (true) {
        //수들의 합이 정확히 S가 아니라 S만 넘으면 되기 때문에 계속해서 짧은 길이가 갱신될수 있기 때문에 ans갱신을 여기서 해준다.
		if (sum >= S) {
			sum -= ar[l++];
			ans = ans > r - l + 1 ? r - l + 1 : ans;
		}
		
        //else가 빠질경우엔 r==N에 걸려있는 상태에서 l이 N-1인 끝까지 탐색하지 못한다.
		else if (r == N)break;
        //else가 빠지면 인덱스 참조 오류남.
		else sum += ar[r++];

        //수들의 합2와 비교해서 여기서에서 ans를 갱신해주지 않아도 되는점은 어차피 l은 r보다 뒤에있고 r이 N이 아니어서 sum을 갱신하면 20라인에서 다시 검사를 한다.
	}

	if (ans == 100001)cout << 0;
	else cout << ans;
	
	return 0;
}