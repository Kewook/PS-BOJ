/*
스택을 이용해서 푸는 문제
naive하게 접근하면 O(N^2)로 쉽게 풀이할수 있지만 TLE를 못피한다.

stack은 각 위치에서의 높이를 순서대로 저장하는 역할을 한다.
스택의 top의 높이보다 지금 탐색하고있는 위치(i)의 높이가 작거나 같다면 현재의 높이로 앞전의 높이를 자를 수 있기 때문에 탐색을 시작한다.
==> if(height[st.top()] >= height[i])

탐색은 i위치의 높이보다(height[i]) 스택의 top이 가리키는 위치의 높이(height[st.top()])가 더 커질때까지(자를 수 없을때 까지)진행되며 넓이의 최대값은 다음과 같이 계산된다.
현재 스택의 top이 j를 가리키고 있다고 가정할때 넓이 : (i - j) * height[j]

하지만 j 위치에 관해서 넓이를 계산하고 stack.pop()을 하면 안된다.(j가 0일 때 그다음에 계산이 난해해짐)
따라서 스택을 미리 pop시켜놓고 넓이를 다음과 같이 계산한다.
넓이 : (i - stack.top() -1) * height[j]

또한,i를 0~N-1까지 탐색하는게 아니라 N까지 탐색하는데 그 이유는
5
1 4 1 2 2
와 같은 케이스 에서 높이가 1인 너비를 모두 탐색해주어야 하고 스택에 남아있는 모든 것들을 처리해 주어야하기 때문이다.


세그먼트트리와 분할정복을 이용하는 방법도 있다.
*/
#include<iostream>
#include<stack>

using namespace std;

int N, height[100001];
stack<int> st;

	
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; i++)cin >> height[i];

	int ans = 0;
    //끝까지 검색해주기 위함.
	for (int i = 0; i <= N; i++) {
		while (!st.empty() && height[st.top()] > height[i]) {
			int width;
			int pos = st.top();
			st.pop();

            //pos가 0이라면 width를 계산해줄때 pop을 미리 안한다면 계산이 애매해진다.
			if (st.empty())width = i;
			else width = i - st.top() - 1;
			
			ans = ans < height[pos]*width ? height[pos] * width : ans;
		}
		st.push(i);
	}

	cout << ans;
	return 0;
}