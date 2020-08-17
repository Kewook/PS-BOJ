#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

int N, M, root[10], ar[10];
bool check[10];
vector<string> ans;
set<string> st;

void sol(int idx, int cnt) {
	if (cnt == M) {
		string str;
		
		for (int i = 0; i < M; i++) {
			str += to_string(root[i]);
			str += " ";
		}
		
		if (st.find(str) == st.end()) {
			st.insert(str);
			ans.push_back(str);
		}
		return;
	}

	for (int i = idx; i < N; i++) {
		if (check[i])continue;
		check[i] = true;
		root[cnt] = ar[i];
		sol(i, cnt + 1);
		check[i] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;

	for (int i = 0; i < N; i++)cin >> ar[i];
	sort(ar, ar + N);
	
	sol(0, 0);

	for (auto s : ans)cout << s << "\n";
	return 0;
}