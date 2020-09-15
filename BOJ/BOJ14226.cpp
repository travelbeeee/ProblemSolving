/*
	BFS탐색을 이용해서 정답을 구할 수 있다.

	우리는 2가지 정보가 필요
	현재 이모티콘의 갯수, 클립보드에 복사해둔 이모티콘의 갯수 

	1) 현재 화면의 이모티콘 갯수와 클립보드에 있는 갯수가 다르다면 클립보드에 새롭게 복사 가능
	2) 현재 클립보드에 있는 갯수가 0이 아니라면 현재 화면에 붙여넣기 가능
	3) 현재 화면에 이모티콘이 0개가 아니라면 하나 삭제 가능

	이렇게 3가지 동작을 수행할 수 있고, 구해야하는 이모티콘의 갯수가 S개라면
	클립보드에 S 를 넘어가는 값을 저장하는 경우는 항상 최소가 아니게 되고,
	화면에 있는 이모티콘의 갯수가 2 * S 가 넘어가는 경우도 최소가 아니게 된다.
	따라서, [0  ~ 2 * S ] [ 0 ~ S ] 에 대해서만 우리는 다뤄보면 된다.
*/
#include<iostream>
#include<queue>

using namespace std;

const int INF = 99999999;
int S;
int visited[2001][1001] = {};

bool isInside(int x, int y) {
	return (0 <= x && x <= 2 * S && 0 <= y && y <= S);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> S;

	for (int i = 0; i <= 2 * S; i++)
		for (int j = 0; j <= S; j++)
			visited[i][j] = INF;

	queue<pair<int, int>> q;

	q.push({ 1, 0 });
	visited[1][0] = 0;
	while (!q.empty()) {
		int curE = q.front().first, curC = q.front().second;
		q.pop();
		if (curE == S) {
			cout << visited[curE][curC] << '\n';
			break;
		}

		// 복사
		if (curC != curE) {
			if (isInside(curE, curE) && visited[curE][curC] + 1 < visited[curE][curE]) {
				visited[curE][curE] = visited[curE][curC] + 1;
				q.push({ curE, curE });
			}
		}
		// 붙여넣기
		if (curC != 0 && isInside(curE+curC, curC) && visited[curE][curC] + 1 < visited[curE + curC][curC]) {
			visited[curE + curC][curC] = visited[curE][curC] + 1;
			q.push({ curE + curC, curC });
		}
		// 이모티콘 삭제
		if (isInside(curE - 1, curC) && visited[curE][curC] + 1 < visited[curE - 1][curC]) {
			visited[curE - 1][curC] = visited[curE][curC] + 1;
			q.push({ curE - 1, curC });
		}
	}

	return 0;
}
