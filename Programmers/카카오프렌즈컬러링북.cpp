/*
  단순 BFS탐색
  
*/
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool isInside(int x, int y, int m, int n) {
    return (0 <= x && x < m && 0 <= y && y < n);
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

    int number_of_area = 0;
    int max_size_of_one_area = 0;

    bool visited[100][100] = {};
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) {
            if (picture[i][j] != 0 && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({ i, j });
                visited[i][j] = true;
                int area = 1;
                while (!q.empty()) {
                    pair<int, int> cur = q.front();
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
                        if (!isInside(nextX, nextY, m, n)) continue;
                        if (visited[nextX][nextY]) continue;
                        if (picture[cur.first][cur.second] != picture[nextX][nextY]) continue;
                        q.push({ nextX, nextY });
                        visited[nextX][nextY] = true;
                        area++;
                    }
                }
                number_of_area++;
                max_size_of_one_area = max(max_size_of_one_area, area);
            }
        }
    }
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
