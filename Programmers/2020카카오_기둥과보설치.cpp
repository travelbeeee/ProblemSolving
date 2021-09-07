/*
  설치는 문제에서 나온 조건대로 설치가 가능한지 파악하면 된다.
  canBuildRow := 보 설치가 가능한지
  canBuildCol := 기둥 설치가 가능한지
  
  삭제는 삭제를 하고 나머지 모든 보와 기둥들이 문제에서 나온 설치 조건을 만족하고있는지 체크하면 된다.
  
  # 기둥을 삭제할 때는 위에 있는 기둥, 양 옆에 달려있는 보 3가지
  # 보를 삭제할 때는 양 옆 기둥, 양 옆 보 4가지
  # 총 7가지만 체크하면 된다고 생각했는데 모든 보와 기둥을 체크하지 않으면 틀렸습니다를 받는다....!
  
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool row[105][105] = {}, col[105][105] = {}; // 보, 기둥

void init(void) {
    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 105; j++)
            row[i][j] = col[i][j] = false;
}

bool canBuildRow(int x, int y) {
    if (col[x][y - 1] || col[x + 1][y - 1] || (row[x - 1][y] && row[x + 1][y])) return true;
    return false;
}

bool canBuildCol(int x, int y) {
    if (y == 2 || row[x - 1][y] || row[x][y] || col[x][y - 1]) return true;
    return false;
}

bool checkAll(int n) {
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++){
            if (row[i][j] && !canBuildRow(i, j)) return false;
            if (col[i][j] && !canBuildCol(i, j)) return false;
        }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    init();

    for (int i = 0; i < build_frame.size(); i++) {
        int x = build_frame[i][0], y = build_frame[i][1], isRow = build_frame[i][2], isBuilt = build_frame[i][3];
        x += 2, y += 2; // 2 ~ N + 2 까지 사용!
        if (isBuilt) { //설치
            if (isRow && canBuildRow(x, y)) // 보 설치
                    row[x][y] = true;
            if (!isRow && canBuildCol(x, y))// 기둥 설치
                    col[x][y] = true;
        }
        else { //삭제
            if (isRow) { // 보 삭제 --> 삭제하고 나머지 다 조사하자
                row[x][y] = false;
                if (!checkAll(n)) row[x][y] = true;
            }
            else { // 기둥 삭제
                col[x][y] = false;
                if (!checkAll(n)) col[x][y] = true;
            }
        }
    }
    vector<vector<int>> answer;
    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 105; j++) {
            if (row[i][j]) {
                answer.push_back({ i - 2, j - 2, 1 });
            }
            if (col[i][j]) {
                answer.push_back({ i - 2, j - 2, 0 });
            }
        }
    sort(answer.begin(), answer.end());

    return answer;
}

// 다시 푼 풀이
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void init(vector<vector<vector<bool>>>* isPut, int n) {
    vector<vector<bool>> rows;
    vector<vector<bool>> cols;
    for (int i = 0; i <= n; i++) {
        vector<bool> row(n + 1, false);
        vector<bool> col(n + 1, false);
        rows.push_back(row);
        cols.push_back(col);
    }
    isPut->push_back(cols);
    isPut->push_back(rows);
}

bool isInside(int x, int y, int n) {
    return (0 <= x && x <= n && 0 <= y && y <= n);
}

bool isPossiblePut(vector<vector<vector<bool>>>& isPut, int x, int y, int n, bool isRow) {
    vector<vector<bool>> rows = isPut[1];
    vector<vector<bool>> cols = isPut[0];
    if (isRow) {
        if (isInside(x, y - 1, n) && cols.at(x).at(y - 1)) return true;
        if (isInside(x + 1, y - 1, n) && cols.at(x + 1).at(y - 1)) return true;
        if (isInside(x - 1, y, n) && isInside(x + 1, y, n) && rows.at(x - 1).at(y) && rows.at(x + 1).at(y)) return true;
        return false;
    }
    else {
        if (y == 0) return true;
        if (isInside(x - 1, y, n) && rows.at(x - 1).at(y)) return true;
        if (rows.at(x).at(y)) return true;
        if (isInside(x, y - 1, n) && cols.at(x).at(y - 1)) return true;
        return false;
    }
}

bool isPossibleRemove(vector<vector<vector<bool>>>* isPut, int x, int y, int n, bool isRow) {
    isPut->at(isRow).at(x).at(y) = false;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (!isPut->at(i).at(j).at(k)) continue;
                if (!isPossiblePut(*isPut, j, k, n, i)) {
                    isPut->at(isRow).at(x).at(y) = true;
                    return false;
                }
            }
        }
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<vector<bool>>> isPut;

    init(&isPut, n);

    for (vector<int> build : build_frame) {
        if (build[3] == 1) { // 설치
            if (isPossiblePut(isPut, build[0], build[1], n, build[2])){
                isPut[build[2]][build[0]][build[1]] = true;
            }
        }
        else { // 삭제
            if (isPossibleRemove(&isPut, build[0], build[1], n, build[2])) {
                isPut[build[2]][build[0]][build[1]] = false;
            }
        }
    }

    vector<vector<int>> answer;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (isPut[i][j][k]) {
                    answer.push_back({ j, k, i });
                }
            }
        }
    }
    sort(answer.begin(), answer.end());

    return answer;
}
