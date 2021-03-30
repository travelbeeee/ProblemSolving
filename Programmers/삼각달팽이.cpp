/*
  2차원 배열에 삼각 달팽이를 직접 구현해서 저장해놓는다
*/
#include <string>
#include <vector>

using namespace std;


vector<int> solution(int n) {
    int sX = 0, sY = 1000;
    int start = 1, dir = 0, level = n - 1;
    int dx[3] = { 1, 0, -1 }, dy[3] = { -1, 2, -1 };
    int map[1000][2001] = {};
    map[sX][sY] = start++;
    while (level) {
        for (int i = 0; i < level; i++) {
            sX += dx[dir], sY += dy[dir];
            map[sX][sY] = start++;
        }
        // 방향 바꿔주고 level 낮춰주고!
        dir = (dir + 1) % 3;
        if (dir == 1 && level == n - 1) continue;
        level--;
    }
    vector<int> answer;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 2001; j++)
            if (map[i][j]) {
                answer.push_back(map[i][j]);
            }
    return answer;
}
