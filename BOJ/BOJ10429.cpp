/*
	백트레킹

	모든 숫자 지점에서 BFS 탐색을 시작해서 M개를 지나보자.
	이때, N이 된다면 정답 출력!
*/
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, -1, 0, 1 };

int N, M;
string map[3];
vector<pair<int, int>> road;
bool visited[3][3];
bool isFinished = false;

bool isInside(int x, int y) {
	return (0 <= x && x < 3 && 0 <= y && y < 3);
}

int calculate(string s) {
	int res = s[0] - '0';
	for (int i = 2; i < s.length(); i += 2) {  // s[i] 숫자 s[i - 1] 연산
		if (s[i - 1] == '+')
			res += (s[i] - '0');
		else if (s[i - 1] == '/')
			res /= (s[i] - '0');
		else if (s[i - 1] == '-')
			res -= (s[i] - '0');
	}
	return res;
}

void backtracking(int curX, int curY, string curS) {
	if (isFinished) return;

	if (road.size() == 2 * M - 1) {
		if (calculate(curS) == N) {
			cout << "1\n";
			for (pair<int, int> cur : road)
				cout << cur.first << ' ' << cur.second << '\n';
			isFinished = true;
		}
		return;
	}

	for (int ind = 0; ind < 4; ind++) {
		int nextX = curX + dx[ind], nextY = curY + dy[ind];
		if (!isInside(nextX, nextY)) continue;
		if (visited[nextX][nextY]) continue;

		visited[nextX][nextY] = true;
		road.push_back({ nextX, nextY });
		curS.push_back(map[nextX][nextY]);
		backtracking(nextX, nextY, curS);
		curS.pop_back();
		road.pop_back();
		visited[nextX][nextY] = false;
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	cin >> map[0] >> map[1] >> map[2];

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			if (!('1' <= map[i][j] && map[i][j] <= '9')) continue;
			string s;
			s.push_back(map[i][j]);

			visited[i][j] = true;
			road.push_back({ i, j });
			backtracking(i, j, s);
			road.pop_back();
			visited[i][j] = false;

			if (isFinished) break;
		}
		if (isFinished) break;
	}
	if (!isFinished) cout << "0\n";

	return 0;
}
