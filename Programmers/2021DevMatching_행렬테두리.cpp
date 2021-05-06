#include <string>
#include <vector>
#include<algorithm>

using namespace std;

int matrix[101][101];

void setMatrix(int rows, int columns) {
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= columns; j++)
            matrix[i][j] = (i - 1) * columns + j;
}

void turnMatrix(int x1, int y1, int x2, int y2) {
    // 회전시키자
    int temp = matrix[x1][y1];
    for (int i = x1; i < x2; i++)
        matrix[i][y1] = matrix[i + 1][y1];
    for (int j = y1; j < y2; j++)
        matrix[x2][j] = matrix[x2][j + 1];
    for (int i = x2; i > x1; i--)
        matrix[i][y2] = matrix[i - 1][y2];
    for (int j = y2; j > y1 + 1; j--)
        matrix[x1][j] = matrix[x1][j - 1];
    matrix[x1][y1 + 1] = temp;
}

int getMinNumber(int x1, int y1, int x2, int y2) {
    int minN = matrix[x1][y1];
    for (int j = y1; j <= y2; j++)
        minN = min(minN, min(matrix[x1][j], matrix[x2][j]));
    for (int i = x1; i <= x2; i++)
        minN = min(minN, min(matrix[i][y1], matrix[i][y2]));
    return minN;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    
    setMatrix(rows, columns);

    vector<int> answer;
    for (int i = 0; i < queries.size(); i++) {
        // (x1, y1) 부터 (x2, y2) 까지 회전시키자!
        int x1 = queries[i][0], y1 = queries[i][1];
        int x2 = queries[i][2], y2 = queries[i][3];

        turnMatrix(x1, y1, x2, y2);

        answer.push_back(getMinNumber(x1, y1, x2, y2));
    }
    return answer;
}
