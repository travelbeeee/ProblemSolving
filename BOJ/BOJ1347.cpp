/*
	구현

	입력이 최대 50이므로 (50, 50)에서 시작해서 탐색을 진행해본다.
	탐색 결과 가장 낮은 행, 가장 높은 행부터
	가장 낮은 열, 가장 높은 열까지 직사각형이 만들어졌다고 생각하고
	탐색한 곳은 '.' 탐색 못한 곳은 '#' 이라고 생각하자.
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N;
int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, -1, 0, 1 };
string movement;
bool moved[101][101];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> movement;

	int sX = 50, sY = 50, dir = 0;
	moved[sX][sY] = true;
	for (int i = 0; i < N; i++) {
		if (movement[i] == 'R')
			dir = (dir + 1) % 4;
		else if (movement[i] == 'L')
			dir = (dir + 3) % 4;
		else
			sX = sX + dx[dir], sY = sY + dy[dir];
		moved[sX][sY] = true;
	}

	int minR = 101, maxR = -1, minC = 101, maxC = -1;
	for (int i = 0; i <= 100; i++)
		for(int j = 0; j <= 100; j++)
			if (moved[i][j]) {
				minR = min(minR, i);
				maxR = max(maxR, i);
				minC = min(minC, j);
				maxC = max(maxC, j);
			}

	for (int i = minR; i <= maxR; i++) {
		for (int j = minC; j <= maxC; j++) {
			if (moved[i][j]) cout << '.';
			else cout << '#';
		}
		cout << '\n';
	}
}
