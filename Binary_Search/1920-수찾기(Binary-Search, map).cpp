/*
정렬과 중복제거를 통해 이분탐색을 하면 문제를 풀수 있지만
set이나 map을 이용하면 간단하게 해결 하능하다.
*/
#include<iostream>
#include<set>

using namespace std;

int N;
set<int> st;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	int num;

	cin >> N;
	for (int i = 0; i < N; i++)cin >> num, st.insert(num);

	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		st.find(num) != st.end() ? cout << 1 : cout << 0;
		cout << " ";
	}
	
	return 0;
}