/*
	시뮬레이션 문제
	1) map의 왼쪽 상단부터 시작해서 현재 스티커를 붙일 수 있는지 체크!
	2) 모든 부분에 현재 스티커를 붙일 수 없다면 스티커를 rotate !
	3) rotate를 4번 진행해서 원래 스티커 모양으로 돌아왔는데도 붙일 수 없다면 스티커를 버린다.
	4) 스티커를 붙일 수 있다면 스티커의 '1' 부분만 map으로 옮겨준다.
*/
#include<iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int mapRows, mapCols, stickers;
	bool map[40][40] = {};
	cin >> mapRows >> mapCols >> stickers;
	for (int sticker = 0; sticker < stickers; sticker++) {
		// 스티커 입력
		int stickerRows, stickerCols;
		bool stickerMap[10][10] = {};
		cin >> stickerRows >> stickerCols;
		for (int stickerR = 0; stickerR < stickerRows; stickerR++)
			for (int stickerC = 0; stickerC < stickerCols; stickerC++)
				cin >> stickerMap[stickerR][stickerC];

		// 4방향에 대해서 스티커를 위, 왼쪽부터 붙여보자.
		for (int rotate = 0; rotate < 4; rotate++) {
			bool success = false;
			for (int j = 0; j <= mapRows - stickerRows; j++) {
				for (int k = 0; k <= mapCols - stickerCols; k++) {
					// map의 (j,k) 에서 시작해서 스티커를 붙여보자.
					bool fail = false;
					for (int stickerR = 0; stickerR < stickerRows; stickerR++) {
						for (int stickerC = 0; stickerC < stickerCols; stickerC++) {
							if (map[j + stickerR][k + stickerC] && stickerMap[stickerR][stickerC]) { // 이미 스티커가 붙은 곳에 붙여야하는 경우
								fail = true;
								stickerR = stickerRows, stickerC = stickerCols;
							}
						}
					}
					if (!fail) {
						for (int stickerR = 0; stickerR < stickerRows; stickerR++)
							for (int stickerC = 0; stickerC < stickerCols; stickerC++)
								if (stickerMap[stickerR][stickerC]) map[j + stickerR][k + stickerC] = 1;
						j = mapRows - stickerRows + 1, k = mapCols - stickerCols + 1; //break;
						success = true;
					}
				}
			}
			if (success) break;

			// 90도 회전시키자
			bool copyStickerMap[10][10] = {};
			for(int stickerR = 0; stickerR < stickerCols; stickerR++)
				for(int stickerC = 0; stickerC < stickerRows; stickerC++)
					copyStickerMap[stickerR][stickerC] = stickerMap[stickerRows- 1 - stickerC][stickerR];
			int temp = stickerRows; // 회전하니까 row, col SWAP
			stickerRows = stickerCols;
			stickerCols = temp;
			for (int stickerR = 0; stickerR < 10; stickerR++) // 회전시킨 copyMap 복사해주기
				for (int stickerC = 0; stickerC < 10; stickerC++)
					stickerMap[stickerR][stickerC] = copyStickerMap[stickerR][stickerC];

		}
	}
	int ans = 0;
	for (int mapR = 0; mapR < mapRows; mapR++)
		for (int mapC = 0; mapC < mapCols; mapC++)
			if (map[mapR][mapC]) ans++;

	cout << ans << '\n';
}