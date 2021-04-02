/*
  visited[x][y][z][w] = (x,y)에서 (z,w)로 이동한 적이 있는지 없는지
  visited[x][y][z][w] = visited[z][w][x][y] 가 보장되어야한다.
*/
#include <string>

using namespace std;

bool isInside(int x, int y) {
    return (-5 <= x && x <= 5 && -5 <= y && y <= 5);
}

int solution(string dirs) {
    int answer = 0, sX = 0, sY = 0;
    bool visited[11][11][11][11] = {}; 
    for (int i = 0; i < dirs.length(); i++) {
        if (dirs[i] == 'U') {
            int nextX = sX, nextY = sY + 1;
            if (!isInside(nextX, nextY)) continue;
            answer = answer + !visited[sX + 5][sY + 5][nextX + 5][nextY + 5];
            visited[sX + 5][sY + 5][nextX + 5][nextY + 5] = true;
            visited[nextX + 5][nextY + 5][sX + 5][sY + 5] = true;
            sX = nextX, sY = nextY;
        }
        else if (dirs[i] == 'D') {
            int nextX = sX, nextY = sY - 1;
            if (!isInside(nextX, nextY)) continue;
            answer = answer + !visited[sX + 5][sY + 5][nextX + 5][nextY + 5];
            visited[sX + 5][sY + 5][nextX + 5][nextY + 5] = true;
            visited[nextX + 5][nextY + 5][sX + 5][sY + 5] = true;
            sX = nextX, sY = nextY;
        }
        else if (dirs[i] == 'R') {
            int nextX = sX + 1, nextY = sY;
            if (!isInside(nextX, nextY)) continue;
            answer = answer + !visited[sX + 5][sY + 5][nextX + 5][nextY + 5];
            visited[sX + 5][sY + 5][nextX + 5][nextY + 5] = true;
            visited[nextX + 5][nextY + 5][sX + 5][sY + 5] = true;
            sX = nextX, sY = nextY;
        }
        else {
            int nextX = sX - 1, nextY = sY;
            if (!isInside(nextX, nextY)) continue;
            answer = answer + !visited[sX + 5][sY + 5][nextX + 5][nextY + 5];
            visited[sX + 5][sY + 5][nextX + 5][nextY + 5] = true;
            visited[nextX + 5][nextY + 5][sX + 5][sY + 5] = true;
            sX = nextX, sY = nextY;
        }
    }
    return answer;
}
