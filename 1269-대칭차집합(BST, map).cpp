#include<iostream>
#include<map>

using namespace std;

int A, B;
map<int, int> mp;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> A >> B;

	int sum = 0, num;

	for (int i = 0; i < A+B; i++) {
		cin >> num;
		mp[num]++;
	}
	
	for (auto it : mp) {
		if (it.second == 1)sum++;
	}
	
	cout << sum;
	return 0;
}