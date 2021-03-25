/*
  BFS
  
  1) 맵 밖에서 가장자리로 들어올 수 있음.
  --> 입력되는 Map 주위를 '.' 으로 한 번 감싸고 (0, 0)부터 탐색 시작!
  
  2) BFS탐색 중에 현재 keyList 에 새롭게 key가 추가되면 새롭게 다시 탐색했을 때 변화가 있을 수 있음!
  --> BFS 탐색 다시 진행!
  
  3) keyList에 새롭게 key가 추가된 것이 없다면 다음 탐색은 의미 없음
  --> BFS 
*/
#include<iostream>
#include<queue>

using namespace std;

int t, h, w;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
char map[102][102];
string key;

bool isInside(int x, int y) {
	return (0 <= x && x <= h + 1 && 0 <= y && y <= w + 1);
}

int BFS(void) {
	// (0, 0)에서 시작해서 변화가 없을 때까지 고!
	int res = 0;
	bool keyList[26] = {};
	if (key != "0")
		for (int i = 0; i < key.length(); i++)
			keyList[key[i] - 'a'] = true;

	while (1) {
		queue<pair<int, int>> q;
		bool visited[102][102] = {};
		bool isFinished = true;
		visited[0][0] = true;
		q.push({ 0, 0 });
		while (!q.empty()) {
			pair<int, int> cur = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nextX = cur.first + dx[i], nextY = cur.second + dy[i];
				if (!isInside(nextX, nextY)) continue;
				if (map[nextX][nextY] == '*') continue;
				if (visited[nextX][nextY]) continue;
				// 열쇠 !
				if ('a' <= map[nextX][nextY] && map[nextX][nextY] <= 'z') {
					visited[nextX][nextY] = true;
					if (keyList[map[nextX][nextY] - 'a'] == false){
						isFinished = false;
						keyList[map[nextX][nextY] - 'a'] = true;
					}
					q.push({ nextX, nextY });
				}
				// 문 !
				else if ('A' <= map[nextX][nextY] && map[nextX][nextY] <= 'Z') {
					if (keyList[map[nextX][nextY] - 'A']) {
						visited[nextX][nextY] = true;
						q.push({ nextX, nextY });
					}
				}
				else {
					if (map[nextX][nextY] == '$') {
						res++;
						map[nextX][nextY] = '.';
					}
					visited[nextX][nextY] = true;
					q.push({ nextX, nextY });
				}
			}
		}
		if (isFinished) break;
	}
	return res;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> t;
	while (t--) {
		cin >> h >> w;
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				cin >> map[i][j];
		cin >> key;

		for (int i = 0; i <= h + 1; i++)
			map[i][0] = map[i][w + 1] = '.';
		for (int j = 0; j <= w + 1; j++)
			map[0][j] = map[h + 1][j] = '.';

		
		cout << BFS() << '\n';
	}
	return 0;
}
