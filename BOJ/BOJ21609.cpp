/*
	구현...!!!

	1) BFS탐색을 진행하며, pq에 (그룹크기, 무지개블록개수, 기준행, 기준열) 을 넣자.
	--> pq에서 제일 앞에 있는 값을 꺼내서 (기준행, 기준열)에서 다시 BFS 탐색하며 삭제하면된다.
	--> 이때, 무지개블록을 서로 다른 일반 블록에서 BFS탐색하며 같이 쓸 수 있으므로,
		BFS탐색용 bfsVisited와 이미 탐색한 일반 블록용 visited 배열을 2개 쓴다

	2) 시계회전과 중력은 단순 구현해준다.
*/

#include<iostream>
#include<queue>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, M, ans;
int map[20][20]; // -1 검은블록, 0 무지개블록, 1 ~ M 블록, -2 Empty 

void printMap(void) {
	cout << "Map출력!\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << map[i][j] << "   ";
		cout << '\n';
	}
}

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < N);
}

bool deleteLargestBlockGroup(void) {
	priority_queue<pair<pair<int, int>, pair<int, int>>> pq;
	bool visited[20][20] = {};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j] > 0) {
				queue<pair<int, int>> q;
				int groupSize = 1, rainbowBlock = 0, minR = i, minC = j;
				bool bfsVisited[20][20] = {};

				visited[i][j] = true;
				bfsVisited[i][j] = true;
				q.push({ i, j });
				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
						if (!isInside(nextX, nextY)) continue;
						if (map[nextX][nextY] == -1) continue;
						if (bfsVisited[nextX][nextY]) continue;

						if (map[nextX][nextY] == 0) { // 무지개블록
							bfsVisited[nextX][nextY] = true;
							rainbowBlock++, groupSize++;
							q.push({ nextX, nextY });
						}
						if (map[nextX][nextY] == map[i][j]) {
							visited[nextX][nextY] = true;
							bfsVisited[nextX][nextY] = true;
							groupSize++;
							q.push({ nextX, nextY });
							if (nextX < minR) {
								minR = nextX, minC = nextY;
							}
							else if (nextX == minR) {
								if (nextY < minC) {
									minR = nextX, minC = nextY;
								}
							}
						}
					}
				}
				if (groupSize >= 2)
					pq.push({ {groupSize, rainbowBlock}, {minR, minC} });
			}
		}
	}
	if (pq.empty()) return false;

	int sX = pq.top().second.first, sY = pq.top().second.second;
	int blockC = map[sX][sY];
	ans += pq.top().first.first * pq.top().first.first;
	pq.pop();

	queue<pair<int, int>> q;
	bool bfsVisited[20][20] = {};
	q.push({ sX, sY });
	bfsVisited[sX][sY] = true;
	map[sX][sY] = -2;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (bfsVisited[nextX][nextY]) continue;
			if (map[nextX][nextY] == blockC || map[nextX][nextY] == 0) {
				bfsVisited[nextX][nextY] = true;
				map[nextX][nextY] = -2;
				q.push({ nextX, nextY });
			}
		}
	}
	return true;

}

void doGravity(void) {
	for (int j = 0; j < N; j++) {
		int i = N - 1;
		while (i >= 0) {
			if (map[i][j] >= 0) {
				int tempI = i + 1, tempM = map[i][j];
				while (tempI < N) {
					if (map[tempI][j] != -2) break;
					tempI++;
				}
				tempI--;
				map[i][j] = -2;
				map[tempI][j] = tempM;
			}
			i--;
		}
	}
}

void turnCounterClockWise(void) {
	int tempMap[20][20];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			tempMap[i][j] = map[j][N - 1 - i];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = tempMap[i][j];
}


int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	
	while (1) {
		if (!deleteLargestBlockGroup()) break;

		doGravity();

		turnCounterClockWise();

		doGravity();
	}
	cout << ans << '\n';
}
