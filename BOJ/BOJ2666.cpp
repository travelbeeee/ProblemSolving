/*
	브루트포스
*/
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 99999999;

int N, K, x, y, ans = INF;
int closetNum[20];

void moveCloset(int closet, int nmove, int leftCloset, int rightCloset) {
	if (nmove >= ans) return;
	if (closet == K) {
		ans = min(ans, nmove);
		return;
	}
	if (rightCloset <= closetNum[closet]) {
		moveCloset(closet + 1, nmove + (closetNum[closet] - rightCloset), leftCloset, closetNum[closet]);
	}
	else if (closetNum[closet] <= leftCloset) {
		moveCloset(closet + 1, nmove + (leftCloset - closetNum[closet]), closetNum[closet], rightCloset);
	}
	else {
		moveCloset(closet + 1, nmove + (closetNum[closet] - leftCloset), closetNum[closet], rightCloset);
		moveCloset(closet + 1, nmove + (rightCloset - closetNum[closet]), leftCloset, closetNum[closet]);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> x >> y >> K;
	for (int i = 0; i < K; i++)
		cin >> closetNum[i];

	moveCloset(0, 0, min(x, y), max(x, y));

	cout << ans << '\n';

	return 0;
}
