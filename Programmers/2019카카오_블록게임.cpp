/*
    5가지 모양을 제외하고는 어차피 없을 수 없음!

    Map을 위에서부터 탐색하며 5가지 모양에 해당되는 애들을
    없애면서 진행해보자!

    1) 5가지 모양 중 하나에 해당되는지 체크!
    2) 5가지 모양 중 하나에 해당된다면
        모양별로 검은 블록을 내려야되는 위치에
        블록을 내릴 수 있는지 체크!
    3) 더 이상 삭제되는 블록이 없다면 끝! 아니라면 다시 처음부터 순회하자!
    
    반례!!
    왼쪽상단부터 탐색을 한 번 만 진행한다면 1로 이루어진 블록도 삭제될 수 있는데 삭제가 안된다!!
    --> 더 이상 삭제할 블록이 없을때까지 탐색 진행!
    00000
    10020
    12220
    11000
    00000
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int dx[5][4] = {
    {0, 1, 1, 1},
    {0, 1, 1, 1},
    {0, 1, 2, 2},
    {0, 1, 2, 2,},
    {0, 1, 1, 1}
};

const int dy[5][4] = {
    {0, -1, 0, 1},
    {0, 0, 1, 2},
    {0, 0, 0, -1},
    {0, 0, 0, 1},
    {0, 0, -1, -2}
};

int N;
vector<vector<int>> globalBoard;

bool isInside(int x, int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

// board[x][y] 에 검은블록을 내려 놓을 수 있는지!
bool checkCanDrop(int x, int y) {
    int r = x;
    while (0 <= r) {
        if (globalBoard[r][y]) return false;
        r--;
    }
    return true;
}

int checkShape(int i, int j) {
    for (int k = 0; k < 5; k++) {
        bool shape = true;
        for (int l = 0; l < 4; l++) {
            int nextX = i + dx[k][l], nextY = j + dy[k][l];
            if (!isInside(nextX, nextY) ||
                globalBoard[i][j] != globalBoard[nextX][nextY]) {
                shape = false;
            }
        }
        if (shape) return k;
    }
    return -1;
}

void deleteBlock(int i, int j, int k) {
    for (int l = 0; l < 4; l++) {
        int nextX = i + dx[k][l], nextY = j + dy[k][l];
        globalBoard[nextX][nextY] = 0;
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    N = board.size();
    globalBoard = board;
    while (1) {
        bool nomore = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (!globalBoard[i][j]) continue;
                // 5가지 모양 중 하나에 해당되는지 체크!
                int k = checkShape(i, j);
                if (k == 0) { // ㅗ 모양
                    if (checkCanDrop(i, j - 1) && checkCanDrop(i, j + 1)) {
                        deleteBlock(i, j, k);
                        answer++;
                        nomore = false;
                    }
                }
                if (k == 1) {
                    if (checkCanDrop(i, j + 1) && checkCanDrop(i, j + 2)) {
                        deleteBlock(i, j, k);
                        answer++;
                        nomore = false;
                    }
                }
                if (k == 2) {
                    if (checkCanDrop(i, j - 1) && checkCanDrop(i + 1, j - 1)) {
                        deleteBlock(i, j, k);
                        answer++;
                        nomore = false;
                    }
                }
                if (k == 3) {
                    if (checkCanDrop(i, j + 1) && checkCanDrop(i + 1, j + 1)) {
                        deleteBlock(i, j, k);
                        answer++;
                        nomore = false;
                    }
                }
                if (k == 4) {
                    if (checkCanDrop(i, j - 2) && checkCanDrop(i, j - 1)) {
                        deleteBlock(i, j, k);
                        answer++;
                        nomore = false;
                    }
                }
            }
        }
        if (nomore) break;
    }
   
    return answer;
}
