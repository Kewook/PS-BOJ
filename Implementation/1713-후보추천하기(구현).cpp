/*
operator 오버라이딩 구성을 잘못해서 한번 WA받음
*/
#include<iostream>
#include<algorithm>

using namespace std;

struct Frame {
	int num, day, preq;

	bool operator < (const Frame &ipt) {
		if (preq == ipt.preq)return day > ipt.day;
		else return preq > ipt.preq;
	}
};

bool cmp(const Frame &f1, const Frame &f2) {
	return f1.num < f2.num;
}

int N, M;
Frame frame[21];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	int cnt = 0, num;
	for (int i = 1; i <= M; i++) {
		cin >> num;

		bool flag = true;
		for (int j = 0; j < cnt; j++)if (frame[j].num == num)flag = false, frame[j].preq++;

		if (flag) {
			if (cnt >= N) {
				sort(frame, frame + N);
				frame[cnt - 1] = { num, i, 1 };
			}
			else frame[cnt++] = { num, i, 1 };
		}
	}

	sort(frame, frame + N, cmp);
	for (int i = 0; i < cnt;i++)cout << frame[i].num << " ";
	return 0;
}