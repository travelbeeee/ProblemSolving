/*
  구현
  
*/
#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<string> board) {

    int answer = 0;
    while (1) {
        // 삭제하기
        bool isChanged = false;
        bool isDeleted[30][30] = {};
        for (int i = 0; i < m - 1; i++)
            for (int j = 0; j < n - 1; j++)
                if (board[i][j] != '.' && board[i][j] == board[i][j + 1] &&
                    board[i][j] == board[i + 1][j] &&
                    board[i][j] == board[i + 1][j + 1]) {
                    isDeleted[i][j] = isDeleted[i][j + 1] = isDeleted[i + 1][j] = isDeleted[i + 1][j + 1] = true;
                }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isDeleted[i][j]) {
                    answer++;
                    board[i][j] = '.';
                    isChanged = true;
                }
        // 내리기
        for (int j = 0; j < n; j++) {
            int i = m - 1;
            while (1) {
                bool finished = true;
                for (int k = i; k >= 0; k--)
                    if (board[k][j] != '.') finished = false;
                if (finished) break;
                if (board[i][j] == '.') {
                    for (int k = i; k > 0; k--)
                        board[k][j] = board[k - 1][j];
                    board[0][j] = '.';
                }
                else
                    i--;
            }
        }
        if (!isChanged) break;
    }
    return answer;
}
