/*
	초록보드 파랑보드 모두 똑같이 바라봄!
	파랑보드를 초록보드처럼 돌려서 생각!
	입력 값 중 t만 조정해주면 똑같은 함수로 처리 가능
	
	1) 블록 내리기
	2) 가득찬 행 처리하기
	3) 스페셜 행 처리하기
*/
#include<iostream>

using namespace std;

int N, t, x, y, score;
bool board[6][4][2];

void printAns(void) {
	int blocks = 0;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 4; j++){
			if (board[i][j][0]) blocks++;
			if (board[i][j][1]) blocks++;
		}
	}
	cout << score << '\n' << blocks << '\n';

	return;
}

void printBoard(void) {
	cout << "green\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++)
			cout << board[i][j][0] << ' ';
		cout << endl;
	}
	cout << "blue\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++)
			cout << board[i][j][1] << ' ';
		cout << endl;
	}
}
void dropBlock(int t, int col, int b) {
	int row = 0;
	if (t == 1) {
		while (row < 6 && !board[row][col][b])
			row++;
		// board[row][col][b] 에서 막힘
		board[row - 1][col][b] = true;
	}
	else if (t == 2) {
		while (row < 6 && (!board[row][col][b] && !board[row][col + 1][b]))
			row++;
		board[row - 1][col][b] = board[row - 1][col + 1][b] = true;
	}
	else {
		while (row < 6 && !board[row][col][b])
			row++;
		board[row - 1][col][b] = board[row - 2][col][b] = true;
	}
}

void clearRow(int b) {
	for (int i = 5; i >= 0; i--) {
		bool check = true;
		for (int j = 0; j < 4; j++)
			if (!board[i][j][b])
				check = false;
		if (check) {
			// i번째 행 위부터 다 하나씩 내리기
			for (int k = i - 1; k >= 0; k--)
				for (int j = 0; j < 4; j++)
					board[k + 1][j][b] = board[k][j][b];
			// 마지막 행 초기화
			for (int j = 0; j < 4; j++)
				board[0][j][b] = false;
			score++;
			i++;
		}
	}
}

void specialRow(int b) {
	int cnt = 0;
	for (int i = 0; i < 2; i++){
		bool check = false;
		for (int j = 0; j < 4; j++) {
			if (board[i][j][b])
				check = true;
		}
		if (check) cnt++;
	}
	// cnt만큼 아래 지우고 끌어내리자!
	while (cnt--) {
		for (int i = 4; i >= 0; i--)
			for (int j = 0; j < 4; j++)
				board[i + 1][j][b] = board[i][j][b];
		for (int j = 0; j < 4; j++)
			board[0][j][b] = false;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> t >> x >> y;
		// 블록놓기
		dropBlock(t, y, 0); //초록보드
		if (t == 2) t = 3;
		else if (t == 3) t = 2;
		dropBlock(t, x, 1); //파랑보드
		// 4개의 열이 다 채워져서 없어지는 행 체크
		clearRow(0); //초록보드
		clearRow(1); //파랑보드
		// 특수행
		specialRow(0);
		specialRow(1);
	}

	printAns();

	return 0;
}
