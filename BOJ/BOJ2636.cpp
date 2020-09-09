/*
	input이 크기가 최대 가로 세로 100이므로 시간초과를 고려하지 않고 BFS 탐색으로 문제를 해결 할 수 있다.
	치즈를 녹이는 건 간단하다
	Map을 순회하다 '1'(치즈)를 만나면 치즈의 위 아래 왼쪽 오른쪽을 탐색해 '0' 이 있으면 치즈는 녹는다!
	이때, '0' 이 구멍인지 아닌지가 중요하다
	치즈 안에 갇혀있는 '0'(구멍) 이라면 치즈를 녹일 수 없다.
	--> 따라서, 우리는 '0' 들을 구멍인지 아닌지 먼저 탐색을 진행해야한다.
	--> Map의 테두리는 무조건 치즈가 올 수 없다 했으므로 '0'이 되고 따라서 우리는 map[0][0] 은 무조건 '0' 인 것을 안다.
	--> map[0][0] 에서 탐색을 시작해서 방문할 수 있는 '0'을 다 방문하자!
	--> 이때, 방문할 수 있는 '0' 들은 치즈에 갇혀있지않으므로 구멍이 아니다!

	1) Map을 순회하며 현재 치즈를 count 한다. --> 현재 Map에 치즈가 없다면 다 녹은 상태! 알고리즘 종료!
	2) map[0][0] 에서 BFS 탐색을 진행해 구멍이 아닌 '0' 들을 다 체크한다.
	3) Map을 순회하며 치즈들을 녹인다.
	4) 위의 과정들을 반복한다.
*/

#include<iostream>
#include<queue>

using namespace std;

int r, c, map[100][100];
bool isHole[100][100];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < c);
}

int getCheese(void) {
	int res = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (map[i][j] == 1) res++;
	return res;
}

void checkHole(void) {
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			isHole[i][j] = true;

	queue<pair<int, int>> q;
	bool visited[100][100] = {};

	q.push({ 0, 0 });
	isHole[0][0] = false;
	visited[0][0] = true;

	while (!q.empty()) {
		int curX = q.front().first, curY = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nextX = curX + dx[i], nextY = curY + dy[i];
			if (!isInside(nextX, nextY)) continue;
			if (visited[nextX][nextY]) continue;
			if (map[nextX][nextY] == 1) continue;
			visited[nextX][nextY] = 1;
			isHole[nextX][nextY] = false;
			q.push({ nextX, nextY });
		}
	}

	return;
}

void meltingCheese(void) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 1) { // 치즈가 녹는지 체크하자!
				for (int k = 0; k < 4; k++) {
					int nextX = i + dx[k], nextY = j + dy[k];
					if (isInside(nextX, nextY) && map[nextX][nextY] == 0 && !isHole[nextX][nextY]) {
						map[i][j] = 0;
						break;
					}
				}
			}
		}
	}
	return;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> map[i][j];

	int time = 0, cheese;
	while (1) {
		int curCheese = getCheese();
		if (!curCheese) break; // 현재 cheese가 없으면 끝!

		checkHole(); // 구멍인 '0' 아닌 '0'을 따로 체크!
		meltingCheese(); // 치즈를 녹이자

		cheese = curCheese;
		time++;
	}
	cout << time << '\n' << cheese << '\n';

	return 0;
}
