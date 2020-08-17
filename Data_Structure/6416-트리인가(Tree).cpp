/*
노드번호가 주어지지 않았다.
단지 트리인지 아닌지만 파악하면 되는 문제이기 때문에 노드수와 간선수로 판단한다.

트리 : 노드수 = 간선수 + 1
중복제거를 위해 set을 사용한다.
*/
#include<iostream>
#include<set>

using namespace std;

set<int> s;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	int u, v, t = 1, cnt = 0;
	while (true) {
		cin >> u >> v;
		if (u == -1 && v == -1)break;

		if (u == 0 && v == 0) {
			if (cnt == 0 || s.size() == cnt + 1)cout << "Case " << t << " is a tree.\n";
			else cout << "Case " << t << " is not a tree.\n";
			cnt = 0;
			t++;
			s.clear();

		}
		else {
			s.insert(u);
			s.insert(v);
			++cnt;
		}
	}

	return 0;
}