/*
	Backtracking BinarySearch

	백트레킹을 이용해 가능한 모든 게임판 상태를 만들고
	게임이 끝난 상황들을 따로 모아둔다.

	입력된 값이 게임이 끝난 상황에 해당하면 valid
	아니라면 invalid 를 출력해준다.

*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

string input;
vector<string> allCases;

bool finishGame(string cur) {
	// 가로줄체크
	for (int i = 0; i < 3; i++) {
		bool checkRow = true;
		if (cur[3 * i] == '.') continue;
		for (int j = 0; j < 3; j++) {
			if (cur[3 * i] != cur[3 * i + j]) 
				checkRow = false;
		}
		if (checkRow) return true;
	}
	// 세로줄체크
	for (int j = 0; j < 3; j++) {
		bool checkCol = true;
		if (cur[j] == '.') continue;
		for (int i = 0; i < 3; i++) {
			if (cur[j] != cur[3 * i + j])
				checkCol = false;
		}
		if (checkCol) return true;
	}
	// 대각선체크
	if (cur[0] != '.' && cur[0] == cur[4] && cur[0] == cur[8]) return true;
	if (cur[2] != '.' && cur[2] == cur[4] && cur[2] == cur[6]) return true;
	
	// 이미 게임이 가득 찬 상태
	bool checkEnd = true;
	for (int i = 0; i < 9; i++)
		if (cur[i] == '.') checkEnd = false;
	return checkEnd;
}

void makeAllCases(string cur, bool first) {
	if (finishGame(cur)) {
		allCases.push_back(cur);
		return;
	}

	for (int i = 0; i < 9; i++) {
		if (cur[i] == '.' && first) {
			cur[i] = 'X';
			makeAllCases(cur, !first);
			cur[i] = '.';
		}
		else if (cur[i] == '.' && !first) {
			cur[i] = 'O';
			makeAllCases(cur, !first);
			cur[i] = '.';
		}
	}
}

bool binarySearch(string str) {
	int left = 0, right = (int)allCases.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (allCases[mid] == str) {
			return true;
		}
		else if (allCases[mid] < str) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	makeAllCases(".........", true);

	sort(allCases.begin(), allCases.end());
	allCases.erase(unique(allCases.begin(), allCases.end()), allCases.end());

	while (1) {
		cin >> input;
		if (input == "end") break;
		if (binarySearch(input)) cout << "valid\n";
		else cout << "invalid\n";
	}

	return 0;
}
