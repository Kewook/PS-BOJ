/*
덱에 최소값의 후보들을 저장해놓고 탐색한다.
*/
#include<iostream>
#include<deque>

using namespace std;

struct Pos{
	int val, pos;
};

int N, L;
deque<Pos> dq;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L;

	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
        //덱 안의 원소들의 좌표가 탐색범위를 벗어난다면 모두 없애준다.
		while (!dq.empty() && dq.front().pos < i - L + 1)dq.pop_front();
        //덱의 맨 뒤 원소부터 차레로 입력값보다 크면 제거한다.
        //이렇게 되면 덱에서는 앞에서부터 차례로 최소값의 후보들이 오름차순으로 정렬되어있다.
		while (!dq.empty() && dq.back().val > num)dq.pop_back();
		dq.push_back({ num, i });

        //맨앞의 원소가 제일 작다.
		cout << dq.front().val << " ";
	}
	return 0;
}