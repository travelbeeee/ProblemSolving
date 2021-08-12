#include<iostream>

using namespace std;


// K개의 바구니에 1개 , 2개 , ... , K개 공을 넣은 상황
// N - minN 만큼 여유가 있다
// (N - min) / K 만큼씩 공을 다 전체적으로 추가
// --> (N - min) - ((N - min) / K ) * K 만큼 최종 공이 남음
// 1개가 남았으면 제일 공이 많이들어간 바구니에 하나 더 넣어야됨
// 2개가 남았으면 제일 공이 많이 들어간 바구니 2개에 하나씩
// 몇개가 남았던 남았으면 제일 공이 많이 들어간 바구니부터 1개씩 추가
int putBallInBasket(int N, int K) {
	int minN = (K * (K + 1)) / 2;

	if (N < minN) return -1;

	int rest = (N - minN) - ((N - minN) / K) * K;
	if (rest) return K;
	return K - 1;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, K;
	cin >> N >> K;

	cout << putBallInBasket(N, K);

	return 0;
}
