/*
	단순구현

	1) 주어진 크기에 맞춰 Map을 다 회전한다
	2) 모든 Map의 지점마다 인접한 지점을 방문해 얼음이 있는 칸이 3개 이상인지 체크
	3) 3개 이상이라면 얼음을 녹인다.

*/
#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>

using namespace std;

int N, Q, map[64][64], r;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int ansSum, ansSize;

bool isInside(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < r);
}

void changeMap(int x, int y, int L) { //(x, y) 를 왼쪽상단으로 생각하고 L크기만큼 회전
	int tempMap[64][64] = {};
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			tempMap[i][j] = map[x + L - 1 - j][y + i];
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			map[x + i][y + j] = tempMap[i][j];
}

void fireStorm(int L) {
	// Map 회전
	for (int i = 0; i < r; i += L)
		for (int j = 0; j < r; j += L)
			changeMap(i, j, L);
	// 얼음 녹이기
	bool isMelted[64][64] = {};
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			if (!map[i][j]) continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nextX = i + dx[k], nextY = j + dy[k];
				if (!isInside(nextX, nextY)) continue;
				if (map[nextX][nextY] == 0) continue;
				cnt++;
			}
			if (cnt < 3) isMelted[i][j] = true;
		}
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < r; j++)
			if (isMelted[i][j]) map[i][j]--;
}

void getAnswer(void) {
	for (int i = 0; i < r; i++)
		for (int j = 0; j < r; j++)
			ansSum += map[i][j];

	bool isVisited[64][64] = {};
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			if (!map[i][j]) continue;
			if (isVisited[i][j]) continue;
			queue<pair<int, int>> q;
			q.push({ i, j });
			int cnt = 1;
			isVisited[i][j] = true;
			while (!q.empty()) {
				pair<int, int> cur = q.front();
				q.pop();
				for (int k = 0; k < 4; k++) {
					int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
					if (!isInside(nextX, nextY)) continue;
					if (isVisited[nextX][nextY]) continue;
					if (!map[nextX][nextY]) continue;
					isVisited[nextX][nextY] = true;
					cnt++;
					q.push({ nextX, nextY });
				}
			}
			ansSize = max(ansSize, cnt);
		}
	}
}


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> Q;
	r = (int)pow(2, N);

	for (int i = 0; i < r; i++)
		for (int j = 0; j < r; j++)
			cin >> map[i][j];

	for (int i = 0, L; i < Q; i++) {
		cin >> L;
		fireStorm((int)pow(2, L));
	}
	
	getAnswer();

	cout << ansSum << '\n' << ansSize;

	return 0;
}
