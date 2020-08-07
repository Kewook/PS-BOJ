/*
구현력이 좀 부족했다.
*/
#include<iostream>

using namespace std;

int N, mode;
long long fac[21], pos;
bool check[21];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

    //fac[0]을 저장해야지 마지막 자리가 정상 출력된다.
    /*
    ex)
    5
    1 118

    -> fac[0]저장 안할시 5 4 2 3만 출력
    정상출력은 5 4 2 3 1
    */
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= 20; i++) fac[i] = fac[i - 1] * i;

	cin >> N >> mode;
	
	if (mode == 1) {
		cin >> pos;

		for (int i = 1; i <= N; i++) {
            //두번째 반복문은 가장 작은 j를 찾기위함.
			for (int j = 1; j <= N; j++) {
				if (check[j])continue;
				
                //만약 찾고자하는 위치가 fac[N-i]보다 작으면 그 자리수는 현재까지의 가장 작은 수로 되어야한다. 
				if (pos <= fac[N - i]) {
					cout << j << " ";
					check[j] = true;
					break;
				}
				else pos -= fac[N - i];
			}
		}
	}

	else {
		int num;
        //제일 작은 순서 한개로 초기화해야함.
		pos = 1;
		for (int i = 1; i <= N; i++) {
			cin >> num;
			for (int j = 1; j <= N; j++) {
				if (check[j])continue;
				
                //현재자리가 들어가야할 가장 작은 자리보다 크면 그만큼 자리수를 늘려줘야함.
				if (num > j)pos += fac[N - i];
				else {
					check[j] = true;
					break;
				}
			}
		}
		cout << pos;
	}
	return 0;
}