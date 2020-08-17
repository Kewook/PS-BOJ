#include<iostream>

using namespace std;

int gcd(int a, int b) {
	return a % b ? gcd(b, a%b) : b;
}

int p1, p2, c1, c2, c, p;

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> c1 >> p1 >> c2 >> p2;
	
	p = p1 * p2; c = p1 * c2 + p2 * c1;

	int div;
	div = c < p ? gcd(p, c) : gcd(c, p);
	
	cout << c / div << " " << p / div;	
	return 0;
}