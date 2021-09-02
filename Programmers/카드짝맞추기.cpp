/*
    백트레킹 + bfs탐색

    K번 카드를 뒤집었다면, 다른 K번 카드를 찾아가는게 최소다.
    --> 어떤 카드부터 뒤집을지 미리 백트레킹으로 다 정하면 된다
    --> 최대 6 종류의 카드이므로 6! 경우의 수와 카드별로 어떤 카드먼저 뒤집을지 2가지 경우의 수가 나오므로
    --> 2^6 * 6! 경우의 수가 나오고 (r,c)부터 모두 탐색해본다.
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

int answer = 99999999;
bool visited[7][2] = {};
vector<pair<int, int>> character[7];
vector<pair<int, int>> orders;
vector<vector<int>> globalBoard;

struct box {
    int x, y, len;
};

bool isInside(int x, int y) {
    return (0 <= x && x < 4 && 0 <= y && y < 4);
}

int BFS(int sX, int sY, int eX, int eY, int s) {
    const int dx[4] = { -1, 0, 1, 0 };
    const int dy[4] = { 0, -1, 0, 1 };

    queue<box> q;
    bool visited[4][4] = {};

    q.push({ sX, sY, 0 });

    while (!q.empty()) {
        box cur = q.front();
        q.pop();

        if (cur.x == eX && cur.y == eY)
            return cur.len;

        // 커서 하나 이동
        for (int dir = 0; dir < 4; dir++) {
            int nextX = cur.x + dx[dir], nextY = cur.y + dy[dir];
            if (!isInside(nextX, nextY)) continue;
            if (visited[nextX][nextY]) continue;
            q.push({ nextX, nextY, cur.len + 1 });
        }

        // Ctrl + 커서 이동
        for (int dir = 0; dir < 4; dir++) {
            int nextX = cur.x + dx[dir], nextY = cur.y + dy[dir];
            if (!isInside(nextX, nextY)) continue;

            // 카드를 만나거나 밖으로 나갈떄까지 이동
            while (isInside(nextX, nextY)) {
                if (globalBoard[nextX][nextY] != 0 && (s & (1 << (globalBoard[nextX][nextY] - 1))) == 0) break;
                nextX += dx[dir];
                nextY += dy[dir];
            }
            if (!isInside(nextX, nextY)) { // 밖으로 나가서 깨짐
                nextX -= dx[dir];
                nextY -= dy[dir];
            }

            if (visited[nextX][nextY]) continue;

            q.push({ nextX, nextY, cur.len + 1 });
        }
    }
    return -1;
}

void findShortestRoute(int& r, int& c) {
    // (r, c)에서 시작해서 orders에 담긴 순서대로 탐색하자.
    int curX = r, curY = c, curS = 0, len = 0;

    cout << "탐색 시작\n";

    for (int i = 0; i < orders.size(); i++) {
        int nextX = character[orders[i].first][orders[i].second].first;
        int nextY = character[orders[i].first][orders[i].second].second;

        cout << curX << ' ' << curY << " 에서 " << nextX << ' ' << nextY << " 로탐색 " << BFS(curX, curY, nextX, nextY, curS) << '\n';
        len += BFS(curX, curY, nextX, nextY, curS);
        len++; // enter

        curX = nextX;
        curY = nextY;

        if (i % 2) {
            curS = (curS | (1 << (globalBoard[curX][curY] - 1)));
        }
    }
    cout << "탐색 결과 len : " << len << '\n';

    answer = min(answer, len);
}
void backtracking(int s, int goal, int& r, int& c) {
    if (s == goal) {
        findShortestRoute(r, c);
        return;
    }
    for (int i = 1; i <= 6; i++) {
        if (character[i].empty()) continue;
        if (!visited[i][0] && !visited[i][1]) {
            visited[i][0] = visited[i][1] = true;
            orders.push_back({ i, 0 });
            orders.push_back({ i, 1 });
            backtracking(s + 2, goal, r, c);
            orders.pop_back();
            orders.pop_back();

            orders.push_back({ i, 1 });
            orders.push_back({ i, 0 });
            backtracking(s + 2, goal, r, c);
            orders.pop_back();
            orders.pop_back();

            visited[i][0] = visited[i][1] = false;
        }
    }
}

int solution(vector<vector<int>> board, int r, int c) {
    int goal = 0;
    globalBoard = board;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j]) {
                character[board[i][j]].push_back({ i, j });
                goal++;
            }
        }
    }

    backtracking(0, goal, r, c);

    return answer;
}
