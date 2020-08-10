/*
적어도 M을 가져가야한다 그 톱의 길이 H에서 가장 큰 최대값 H를 찾고있으니 upper_bound -1의 값이 된다.
*/

#include<iostream>

using namespace std;

int N, M, ar[1000001];

int upper_bound(int l, int r) {
	
	while (l < r) {
		int mid = (l + r) / 2;
		
		long long sum = 0;
		for (int i = 0; i < N; i++)if (ar[i] > mid)sum += ar[i] - mid;
		
        //중간값이 원하는 값보다 작았음 == mid ~ r까지는 없으니 r을 줄이자
        //원하는 값보다 작았으면 톱의 길이를 낮춰야하므로 r을 줄이는게 맞다.
		if (M > sum)r = mid;
		else l = mid + 1;
	}
    //l >= r인상태로 끝나고 r에는 원하는값보다 처음으로 큰 값이 저장
	return r;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N >> M;
	for (int i = 0; i < N; i++)cin >> ar[i];

    //그거 보다 한단계 낮춰야한다.
	cout << upper_bound(0, 2000000001) - 1;
	
	return 0;
}


/*
lower bound : 내가 원하는 값 이상이 처음으로 나오는 지점.
*/

int lower_bound(int l, int r, int target){
    while(l < r){
        int mid = (l + r)/2;
        
        //내가 원하는 값이나 그값보다 크면 h에 중간값 저장
        if(ar[mid] <= target)h = mid;
        else l = mid + 1;
    }
    return h;
}


/*
upper-bound : 내가 원하는 값을 "초과" 하는 값이 처음으로 나오는 지점.
*/

int upper_bound(int l, int r){
    while(l < r){
        int mid = (l + r)/2;
        //내가 원하는값이 target이 아닌값이니 부등호가 안들어가는게 맞다.
        if(ar[mid] < target)h = mid;
        else l = mid + 1;
    }
    return h;
}

