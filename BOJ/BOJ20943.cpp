/*
  크기가 큰 색종이부터 차례대로 판에 붙여보자.
  1) 크기가 6인 색종이 --> 6인 색종이만큼 판이 필요
  2) 크기가 5인 색종이 --> 5인 색종이만큼 판이 필요 + 크기가 1인 색종이를 11개씩 더 붙일 수 있음
  3) 크기가 4인 색종이 --> 4인 색종이만큼 판이 필요
    --> 남는 공간에 크기가 2인 색종이를 채우자
    --> 그러고 남는 공간에 크기가 1인 색종이를 채우자
  4) 크기가3 인 색종이 --> 판 하나에 크기가 3인 색종이를 4개씩 붙일 수 있음 + 남는 공간에 크기가 2인 색종이와 1인 색종이를 추가로 붙이자.
    --> 마찬가지로 크기가 2인 색종이부터 채우고 남는 자리에 1인 색종이를 붙이자.
  5) 크기가 2인 색종이 --> 판 하나에 크기가 2인 색종이를 9개씩 붙일 수 있음
    --> 남는 공간에 크기가 1인 색종이를 붙이자.
  6) 크기가 1인 색종이 --> 판 하나에 36개씩 붙일 수 있음.
*/
#include<iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int paper[7];
	for (int i = 1; i <= 6; i++)
		cin >> paper[i];

	int ans = 0;
	if (paper[6] > 0) { // 6cm 1개 -> 판을 다 써야됨
		ans += paper[6];
		paper[6] = 0;
	}
	if (paper[5] > 0) { // 5cm 1개 + 1cm 11개
		ans += paper[5];
		paper[1] -= 11 * paper[5];
		paper[5] = 0;
	}
	if (paper[4] > 0) { // 4cm 1개 + 2cm 5개 / 4cm 1개  + 2cm 4개 + 1cm 4개 ...
		ans += paper[4];
		if (paper[2] < 5 * paper[4] ) { // 2cm로 다 채우고 남는 칸은 1cm로 채우자
			paper[1] -= (5 * paper[4] - paper[2]) * 4;
			paper[2] = 0;
		}
		else {
			paper[2] -= 5 * paper[4];
		}
		paper[4] = 0;
	}
	if (paper[3] > 0) {
		ans += paper[3] / 4;
		if (paper[3] % 4 != 0) {
			ans++;
			/* 
			 * paper[3] % 4 --> 1 라면 2cm 5개 1cm 7개
			 * paper[3] % 4 --> 2 라면 2cm 3개 1cm 6개
			 * paper[3] % 4 --> 3 라면 2cm 1개 1cm 5개 
			*/
			int maxOne[4] = { 0, 7, 6, 5 };
			int maxTwo[4] = { 0, 5, 3, 1 };
			for (int m = 1; m <= 3; m++) {
				if (paper[3] % 4 == m) {
					if (paper[2] < maxTwo[m]) {
						paper[1] -= (maxOne[m] + 4 * (maxTwo[m] - paper[2]));
						paper[2] = 0;
					}
					else if (paper[2] >= maxTwo[m]) {
						paper[2] -= maxTwo[m];
						paper[1] -= maxOne[m];
					}
				}
			}
		}
		paper[3] = 0;
	}
	if (paper[2] > 0) {
		ans += paper[2] / 9;
		if (paper[2] % 9 != 0) {
			ans++;
			paper[1] -= 4 * (9 - (paper[2] % 9));
		}
	}
	if (paper[1] > 0) {
		ans += paper[1] / 36;
		ans += ((paper[1] % 36) != 0);
	}

	cout << ans << '\n';

	return 0;
}
