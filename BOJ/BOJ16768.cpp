#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int N, K;
string map[100];

void printMap(void){
	for (int i = 0; i < N; i++)
		cout << map[i] << '\n';
}

bool isInside(int x, int y){
	return (0 <= x && x < N && 0 <= y && y < 10);
}

bool removeCells(void) {
	const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
	bool visited[100][10] = {};
	bool isFinished = true;
	for (int i = 0; i < N; i++){
		for(int j = 0; j < 10; j++){
			if (!visited[i][j] && map[i][j] != '0') {
				queue<pair<int, int>> q;
				vector<pair<int, int>> road;

				q.push({ i, j });
				road.push_back({ i, j });
				visited[i][j] = true;

				while (!q.empty()) {
					pair<int, int> cur = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
						if (!isInside(nextX, nextY)) continue;
						if (map[cur.first][cur.second] != map[nextX][nextY]) continue;
						if (visited[nextX][nextY]) continue;

						q.push({ nextX, nextY });
						road.push_back({ nextX, nextY });
						visited[nextX][nextY] = true;
					}
				}

				if (road.size() >= K) {
					for (pair<int, int> cur : road){
						map[cur.first][cur.second] = '0';
						isFinished = false;
					}
				}
			}
		}
	}
	return !isFinished;
}

void gravity(void){
	for(int j = 0; j < 10; j++){
		int i = N - 1;
		while (i >= 0) {
			if (map[i][j] == '0') {
				int len = 1000;
				for (int r = i - 1; r >= 0; r--)
					if (map[r][j] != '0') {
						len = (i - r);
						break;
					}
				// len만큼씩 땡겨오자
				for (int r = i; r - len >= 0; r--) {
					map[r][j] = map[r - len][j];
					map[r - len][j] = '0';
				}
			}
			i--;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	while (1) {
		if (!removeCells()) 
			break;

		gravity();

	}
	printMap();

	return 0;
}
