/*
	4 x 4 Board 판을 입력받는다.

	-백트레킹
	1) Board판의 모든 지점에서 시작해서 상하좌우대각선으로 겹치지 않게 이동해서 만들 수 있는 모든 단어를 만들어본다.

	-이진탐색
	2) 만들어진 단어를 처음에 입력받은 단어 사전에서 탐색을 하는데 Binary Search를 이용한다.
	--> 기존에 단어 사전을 미리 sorting 해 놓는다.

	3) 이진탐색에서 탐색 결과가 실패라면 넘어가고, 성공이라면 가장 긴 단어와 score와 단어 count를 갱신한다.
	이때, 다른 지점에서 시작했더라도 같은 단어를 만들어서 찾은 경우라면 한 번만 count 해야되므로
	isSelected bool 배열을 이용해 단어 사전에서 탐색에 성공한 단어들은 체크해둔다.

	4) 같은 과정을 반복한다.
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

int w, b;
int scores[9] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };
int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 }, dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

string dictionary[300000];

int cnt, score;
bool isSelected[300000];
bool visited[4][4];
string board[4];
string longWord;

bool isInside(int x, int y) {
	return (0 <= x && x < 4 && 0 <= y && y < 4);
}

int binary_search(string word) {
	int left = 0, right = w - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (dictionary[mid] == word) return mid;
		else if (dictionary[mid] < word) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

void makeWord(int x, int y, string word) {
	if (int(word.length()) >= 9) return;
	if (word.length() >= 1) {
		// binarySearch로 찾기
		int ind = binary_search(word);
		if (ind != -1) {
			if (word.length() > longWord.length()) longWord = word;
			else if (word.length() == longWord.length() && word < longWord) longWord = word;
			if (!isSelected[ind]) {
				isSelected[ind] = 1;
				cnt++;
				score += scores[word.length()];
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		int nextX = x + dx[i], nextY = y + dy[i];
		if (!isInside(nextX, nextY)) continue;
		if (visited[nextX][nextY]) continue;

		visited[nextX][nextY] = 1;
		word.push_back(board[nextX][nextY]);
		makeWord(nextX, nextY, word);
		word.pop_back();
		visited[nextX][nextY] = 0;
	}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> w;
	for (int i = 0; i < w; i++)
		cin >> dictionary[i];

	sort(dictionary, dictionary + w);

	cin >> b;
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < 4; j++)
			cin >> board[j];

		memset(isSelected, 0, sizeof(isSelected));
		longWord = "";
		cnt = 0;
		score = 0;

		string word;
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++){
				word.push_back(board[j][k]);
				visited[j][k] = 1;
				makeWord(j, k, word);
				visited[j][k] = 0;
				word.pop_back();
			}
		cout << score << ' ' << longWord << ' ' << cnt << '\n';
	}
}
