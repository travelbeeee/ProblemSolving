/*
	단순할 확률 = 1 - 단순하지않을 확률
*/
#include<iostream>
#include<cmath>

using namespace std;

int N, dir[4];
double dirP[4];
double notSimpleP = 0.0;
bool visited[50][50] = {};

int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };

void DFS(int x, int y, int move, double p) {
	if (move == N) { // N번의 이동을 마무리
		return;
	}

	for (int d = 0; d < 4; d++) {
		int nextX = x + dx[d], nextY = y + dy[d];
		if (visited[nextX][nextY]) { // move + 1 번 째 이동에서 단순X
			notSimpleP += p * dirP[d];
			continue;
		}
		visited[nextX][nextY] = true;
		DFS(nextX, nextY, move + 1, p * dirP[d]);
		visited[nextX][nextY] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < 4; i++)
		cin >> dir[i];
	for (int i = 0; i < 4; i++)
		dirP[i] = (1.0 * dir[i]) / 100;

	visited[25][25] = true;
	DFS(25, 25, 0, 1.0);
	
	cout << fixed;
	cout.precision(9);
	cout << (1 - notSimpleP) << '\n';

	return 0;
}
