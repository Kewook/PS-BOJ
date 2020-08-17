/*
knapsack 문제다. 하지만 이 문제는 두군데에 올릴수 있는 점이 다름.
dp[n][sum]는 n번까지 추를 확인했을때 sum무게를 만들수있는지 없는지에 대한 boolean배열임.
여기서 주의할점은 dp[N][sum]그러니까 N까지 다 확인을 해주어야한다. (하지만 런타임안뜬게 이상함)
 ==> runtime error가 뜨지 않은 이유 : 프로그램의 Undefined behavior
 (디버깅이 중요하다)
*/


/////////////////Top-down 방식/////////////////////////////////
#include<iostream>
#include<cmath>

using namespace std;

int Nw, weight[30], Nb, ball[7];
bool cache[31][16000], check[30];

void dfs(int idx, int sum) {
	if (idx > Nw)return;
	
	if (cache[idx][sum])return;

	cache[idx][sum] = true;

    //구슬이 없는 저울에 weight[idx]를 올린다.
	dfs(idx + 1, sum + weight[idx]);
    //올리지 않는다.
	dfs(idx + 1, sum);
    //구슬이 있는 저울에 weight[idx]를 올린다.
	dfs(idx + 1, abs(sum - weight[idx]));
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> Nw;
	for (int i = 0; i < Nw; i++)cin >> weight[i];

	dfs(0,0);
	
	cin >> Nb;
	for (int i = 0; i < Nb; i++) {
		cin >> ball[i];
		if (cache[Nw][ball[i]])cout << "Y ";
		else cout << "N ";
	}
	
	return 0;
}

////////////////////bottom-up 방식//////////////////////////////////

#include<iostream>
#include<cmath>

using namespace std;

int Nw, weight[30], Nb, ball[7];
bool cache[16000], temp[16000], check[31];


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> Nw;
	cache[0] = temp[0] = true;
	for (int i = 0; i < Nw; i++) {
		cin >> weight[i];
		for (int j = 0; j <= 15000; j++) {
            //temp배열을 둔 이유는 추 1개에 대해서 이전에 가능했던 무게들을 전부 탐색하여 올려주고 빼주고 그대로 두고 하는데
            //바로바로 cache배열을 갱신하면 weight[i]에 대해 갱신됐던 새로운 무게(left or right)에 대해서 또 검사를 해줌
 
			if (cache[j]) {
				int left = abs(weight[i] - j), right = weight[i] + j;
                //왼쪽 저울에 올릴 때
				if (left >= 0 && left <= 15000)temp[left] = true;
                //오른쪽 저울에 올릴 때
				if (right >= 0 && right <= 15000)temp[right] = true;
                //아무것도 올리지 않을때.
				temp[weight[i]] = true;
			}
		}
        //cache배열 갱신.
		for (int j = 0; j <= 15000; j++)cache[j] = temp[j];
	}

	cin >> Nb;
	for (int i = 0; i < Nb; i++){
		cin >> ball[i];
		if (cache[ball[i]])cout << "Y ";
		else cout << "N ";
	}

	return 0;
}