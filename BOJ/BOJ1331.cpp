#include<iostream>

using namespace std;

string input;
pair<int, int> start, curP, nextP;
bool visited[6][6];
bool invalid;
int dx[8] = { 1, 1, -1, -1, 2, 2, -2, -2 }, dy[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

pair<int, int> convert(string cur) {
	return { cur[0] - 'A', cur[1] - '1' };
}

bool isCanGo(pair<int, int> A, pair<int, int> B) {
	for (int i = 0; i < 8; i++)
		if (A.first + dx[i] == B.first && A.second + dy[i] == B.second)
			return true;
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> input;

	start = curP = convert(input);
	visited[curP.first][curP.second] = true;
	for (int i = 1; i < 36; i++) {
		cin >> input;
		// nextP가 이미 방문한적이 없는지
		// curP 에서 nextP로 가능한지 확인하자!
		nextP = convert(input);
		if (visited[nextP.first][nextP.second]) invalid = true;
		if (!isCanGo(curP, nextP)) invalid = true;
		curP = nextP;
		visited[nextP.first][nextP.second] = true;
	}
	if (!isCanGo(nextP, start)) invalid = true;

	if (invalid) cout << "Invalid\n";
	else cout << "Valid\n";

	return 0;
}
