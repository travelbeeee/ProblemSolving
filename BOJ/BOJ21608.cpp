/*
  
*/
#include<iostream>
#include<queue>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

int N, room[20][20];
int friendsList[401][4];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

void setStudent(int s) {
	// 학생 s를 배치할 자리를 찾자!
	// 인접한 학생이 가장 많은 칸 -> 비어있는 칸이 가장 많은 칸 --> 행의 번호가 작은 칸 --> 열의 번호가 작은 칸
	priority_queue<pair<pair<int, int>, pair<int, int>>> pq;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (room[i][j]) continue; // 이미 학생 배치되어있음
			int friendCnt = 0, emptyCnt = 0;
			for (int k = 0; k < 4; k++) {
				int nextX = i + dx[k], nextY = j + dy[k];
				if (!isInside(nextX, nextY)) continue;
				if (room[nextX][nextY] == 0) emptyCnt++;
				else {
					for (int l = 0; l < 4; l++)
						if (room[nextX][nextY] == friendsList[s][l]) friendCnt++;
				}
			}
			pq.push({ {friendCnt, emptyCnt}, {-i, -j} });
		}
	}
	room[-pq.top().second.first][-pq.top().second.second] = s;
	return;
}

// 인접한 칸에 좋아하는 학생이 몇 명 있는지 반환
int getCloserFriends(int x, int y) { 
	int cnt = 0;
	int s = room[x][y];
	for (int i = 0; i < 4; i++) {
		int nextX = x + dx[i], nextY = y + dy[i];
		if (!isInside(nextX, nextY)) continue;
		for (int j = 0; j < 4; j++)
			if (room[nextX][nextY] == friendsList[s][j]) cnt++;
	}
	return cnt;
}

// 만족도를 반환
int getAns(void) {
	int res = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			int cnt = getCloserFriends(i, j);
			if (cnt == 4) res += 1000;
			else if (cnt == 3) res += 100;
			else if (cnt == 2) res += 10;
			else if (cnt == 1) res += 1;
		}
	return res;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0, s, a, b, c, d; i < N * N; i++) {
		cin >> s;
		for (int j = 0; j < 4; j++) cin >> friendsList[s][j];
		setStudent(s);
	}
	cout << getAns() << '\n';

	return 0;
}
