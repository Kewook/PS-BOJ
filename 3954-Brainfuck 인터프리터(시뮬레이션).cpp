/*
(Brain fuuuuuuuuuuuuuuuuuuuuuck)
char 범위는 127까지인데 255를 저장하면;
76번 라인때문에 71% 테케에서 계속 틀림
*/
#include<iostream>
#include<string>
#include<stack>
#include<cstring>

#define MAX 50000000

using namespace std;

string op, input;
int sm, sc, si, loop[4100], ar[100005];
stack<int> s;

void init() {
	for (int i = 0; i < sc; i++) {
		if (op[i] == '[')s.push(i);
		else if (op[i] == ']') {
			int idx = s.top();
			loop[idx] = i;
			loop[i] = idx;
			s.pop();
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int idx = 0, opidx = 0, maxidx = 0, ipidx = 0;
		bool flag = false;

		cin >> sm >> sc >> si;
		cin >> op;
		cin >> input;

		memset(ar, 0, sizeof(ar));
		memset(loop, 0, sizeof(loop));

		init();

		for (int i = 0; i < MAX; i++) {
			if (opidx >= sc) {
				cout << "Terminates\n";
				flag = true;
				break;
			}
			if (op[opidx] == '+') {
				ar[idx] = (ar[idx] + 1) % 256;
			}
			else if (op[opidx] == '-') {
				ar[idx] = (ar[idx] - 1) < 0 ? 255 : ar[idx] - 1;
			}
			else if (op[opidx] == '[' && ar[idx] == 0) {
				opidx = loop[opidx];
			}
			else if (op[opidx] == ']' && ar[idx] != 0) {
				opidx = loop[opidx];
			}
			else if (op[opidx] == '<') {
				idx = idx == 0 ? sm - 1 : idx - 1;
			}
			else if (op[opidx] == '>') {
				idx = (idx + 1) % sm;
			}
			else if (op[opidx] == ',') {
				//char범위는 127까지임 무조건 integer형으로 선언
				int c;
				if (ipidx >= si) c = 255;
				else c = input[ipidx];
				ar[idx] = c;
				ipidx++;
			}

			opidx++;
			maxidx = maxidx < opidx ? opidx : maxidx;
		}

		if (!flag) {
			cout << "Loops " << loop[maxidx] << " " << maxidx << "\n";
		}
	}
	return 0;
}