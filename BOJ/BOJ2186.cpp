/*
	BFS + DP

	단순 BFS 탐색으로 가능한 모든 경우의 수를 탐색하면
	시간초과 혹은 메모리 초과에 직면한다.
	
	1) 100 x 100 에서 80자의 영단어를 찾는 경우의 수는
	100 x 100 Map과 80자의 영단어가 모든 한 알파벳으로 이루어진
	최악의 경우만 생각해보아도 (4 * K) ^ 80 에 가까운 경우의 수가 생김.
	2) 답에서 값의 범위가 int 라고 최대 21억에 가까운 경우의 수가
		발생할 수 있는 뉘양스


	--> DP 이용!
	Dp[i][j][l] := (i, j) 좌표에 word의 l까지 찾아서 도착한 경로의 수
	word의 뒤에서부터 찾아가며 재귀적으로 해결!

*/
#include<iostream>
#include<queue>
using namespace std;

int N, M, K;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
char map[100][101];
string word;

int dp[100][100][80];

bool isInside(int x, int y) {
	return (0 <= x && x < N && 0 <= y && y < M);
}

int getCount(int x, int y, int l) {
	if (dp[x][y][l] != -1) return dp[x][y][l];

	if (l == 0) return 1;

	dp[x][y][l] = 0;
	for (int dir = 0; dir < 4; dir++) {
		int nextX = x, nextY = y;
		for (int k = 0; k < K; k++) {
			nextX += dx[dir], nextY += dy[dir];
			if (!isInside(nextX, nextY)) break;
			if (map[nextX][nextY] == word[l - 1])
				dp[x][y][l] += getCount(nextX, nextY, l - 1);
		}
	}
	return dp[x][y][l];
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		cin >> map[i];
	cin >> word;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < word.length(); k++)
				dp[i][j][k] = -1;
	
	int ans = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == word[(int)word.length() - 1])
				ans += getCount(i, j, (int)word.length() - 1);
	
	cout << ans << '\n';

	return 0;
}
