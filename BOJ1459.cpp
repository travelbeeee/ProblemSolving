/*
	BOJ 1459 걷기문제
	가로1번 + 세로1번 == 대각선1번
	가로2번 == 세로2번 == 대각선2번 이므로 
	대각선, 가로/세로 이동 cost를 비교해서 움직인다!
*/
#include<iostream>
#include<algorithm>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	long long X, Y, W, S;
	cin >> X >> Y >> W >> S;

	// 오른쪽2번 = 왼쪽2번 = 대각선2번
	// 오른쪽1번 왼쪽1번 = 대각선1번
	// --> 2 * W 랑 S랑 비교하고 2 * W 랑 2 * S 랑 비교해보자.
	if (2 * W < S) { // 뭘해도 대각선이 손해
		cout << (X + Y) * W;
	}
	else if (2 * W < 2 * S) {
		cout << min(X, Y) * S + ((X + Y) - 2 * min(X, Y)) * W;
	}
	else { // 2 * S <= 2 * W --> 대각선으로 이동하는게 무조건 좋다! 대각선으로 최대한 이동하고 짝수만큼이동하고 남은 홀수는 W로 이동!
		cout << min(X, Y) * S + ((Y - min(X, Y)) / 2) * (2 * S) + ((Y - min(X, Y)) % 2) * W + ((X - min(X, Y)) / 2) * (2 * S) + ((X - min(X, Y)) % 2) * W;
	}
	return 0;
}