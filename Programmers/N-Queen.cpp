#include <string>
#include <vector>

using namespace std;

int answer;
bool visited[12][12];

bool isCanPutQueen(int row, int col, int n) {
    // visited[row][col] 에 Queen을 놓을 수 있는지!
    // 위아래 체크
    for (int i = 0; i < n; i++)
        if (visited[i][col] && i != row) return false;
    // 위 좌, 우측 대각선 체크
    for (int i = 0; i < row; i++){
        if (col - (row - i) >= 0 && visited[i][col - (row - i)]) return false;
        if (col + (row - i) < n && visited[i][col + (row - i)]) return false;
    }
    // 아래 좌, 우측 대각선 체크
    for (int i = row + 1; i < n; i++) {
        if (col - (i - row) >= 0 && visited[i][col - (i - row)]) return false;
        if (col + (i - row) < n && visited[i][col + (row - i)]) return false;
    }
    return true;
}
void backtracking(int row, int n) {
    if (row == n) {
        answer++;
        return;
    }
    for (int j = 0; j < n; j++) {
        if (isCanPutQueen(row, j, n)) { // visited[row][j] 에 Queen을 놓을 수 있다면!
            visited[row][j] = true;
            backtracking(row + 1, n);
            visited[row][j] = false;
        }
    }
}

int solution(int n) {
    backtracking(0, n);
    
    return answer;
}
