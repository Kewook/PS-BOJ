/*
Greedy하고 이분탐색 개념을 섞으면 된다.

가장 긴 통나무의 길이가 전체 case에서 최소가 되게 하려면 
앞에서부터 순차적으로 자를 수 있는 통나무의 길이를 살펴본다.  자를수 있는 위치의 누적합이 특정사이즈보다 넘게 되면 잘라주는데 그 특정사이즈를 이분탐색으로 찾아낸다. 
그리고 C번만큼 자르고 남은 통나무가 특정길이보다 크면 다시 이분탐색을하고 아니면 그 남은 길이를 return 해주면 된다.
남은 길이가 가장 큰 이유는 특정 사이즈만큼 잘라주면 그리디적으로 맨 마지막에 가장 큰 사이즈의 통나무가 남게 된다.

하지만 그 길이가 같을 때 맨 처음의 위치를 구하라 했으니 앞에서부터가 아니라 뒤에서부터 순차적으로 탐색한다.
*/
#include<iostream>
#include<algorithm>

using namespace std;

//len[i] == i번째 와 i-1번째 위치의 길이 차이
int L, K, C, cut[10005], len[10005];

int isPossible(int size) {
	int length = 0, cnt = 0;
	for (int i = K + 1; i >= 1; i--) {
        //현재 추가할 통나무 조각의 길이가 size보다 크니 return -1
		if (len[i] > size)return -1;
		
        //남은 길이에서 현재 보는 사이즈를 더해준다.
		length += len[i];
        //더해준뒤 사이즈보다 크면 그 전의 위치를 잘라준다.
		if (length > size) {
			++cnt;
            //그전의 위치를 잘라줫으니 length엔 현재위치와 현재위치 -1의 길이만큼 남게 된다.
			length = len[i];
		}
		if (cnt == C) {
            //자를수있을만큼 잘랐는데 아직도 남아있는게 size보다 크면 size는 답이 아니다.
			if (cut[i] > size)return -1;
			else return cut[i];
		}
	}
    // 아직도 더 자를 수 있으면 첫번째 위치 return
	return cut[1];
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);

	cin >> L >> K >> C;
	
	cut[K + 1] = L;
	for (int i = 1; i <= K; i++) cin >> cut[i];
    //len을 구하기 전에 정렬 필수
	sort(cut + 1, cut + K + 1);

	for (int i = 1; i <= K + 1; i++)len[i] = cut[i] - cut[i - 1];

	int l = 1, r = L;
	
	int ans, pos;
	while (l < r) {
		int mid = (l + r) / 2;

		int p = isPossible(mid);
		if (p >= 0) {
			ans = mid;
			pos = p;
			r = mid;
		}
		else l = mid + 1;
	}

	cout << ans << " " << pos;
	return 0;
}