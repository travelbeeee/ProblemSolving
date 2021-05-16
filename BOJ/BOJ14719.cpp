/*
	빗물이 고이려면 양 옆에 벽이 있어야됨!
  --> 기존에 세워진 블록 위부터 물이 고일 수 있는지 양 옆을 다 체크해본다.
  --> 물이 고일 수 있으면 그 부분도 벽으로 높여준다.
  
*/

#include<iostream>

using namespace std;

int H, W, block[500];

bool isWater(int r, int c) {
	// (r, c)에 물이 고일 수 있는가
	bool checkLeft = false, checkRight = false;
	for (int j = c - 1; j >= 0; j--) {
		if (block[j] >= r) {
			checkLeft = true;
			break;
		}
	}
	for (int j = c + 1; j < W; j++) {
		if (block[j] >= r) {
			checkRight = true;
			break;
		}
	}
	return (checkLeft && checkRight);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> H >> W;
	for (int j = 0, x; j < W; j++){
		cin >> block[j];
	}

	int ans = 0;
	for (int j = 0; j < W; j++) {
		// block[j] + 1 부터 빗물이 들어올 수 있는지 체크!
		while (isWater(block[j] + 1, j)) {
			ans++;
			block[j]++;
		}
	}
	cout << ans << '\n';

	return 0;
}
