/*
    BFS 탐색

    가로상태 일때는 왼쪽 칸을기준으로 표현
    세로상태 일때는 위 칸을 기준으로 표현

    1) 4가지 방향으로 로봇을 이동
    2) 로봇을 4가지 방식으로 회전
     가로상태일때 4가지 회전 / 세로상태일때 4가지 회전이 가능하다
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct robot {
    int x1, y1, len, isCol;
};

bool isInside(int x, int y, int N) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

int solution(vector<vector<int>> board) {
    const int INF = 99999999;
    const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };

    queue<robot> q;
    int answer = INF, N = board.size();
    int dp[100][100][2];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dp[i][j][0] = dp[i][j][1] = INF;

    q.push({ 0, 0, 0, 0 });
    dp[0][0][0] = 0;

    while (!q.empty()) {
        int curX = q.front().x1;
        int curY = q.front().y1;
        int curL = q.front().len;
        bool isCol = q.front().isCol;
        q.pop();


        if (isCol && curX == N - 2 && curY == N - 1) {
            answer = min(answer, curL);
            continue;
        }
        if (!isCol && curX == N - 1 && curY == N - 2) {
            answer = min(answer, curL);
            continue;
        }
        if (dp[curX][curY][isCol] < curL) continue;

        // 4가지 방향으로 이동
        int curX2 = curX + isCol, curY2 = curY + !isCol;
        for (int dir = 0; dir < 4; dir++) {
            int nextX = curX + dx[dir], nextY = curY + dy[dir];
            int nextX2 = curX2 + dx[dir], nextY2 = curY2 + dy[dir];
            if (!isInside(nextX, nextY, N) || board[nextX][nextY]) continue; //밖이거나 벽
            if (!isInside(nextX2, nextY2, N) || board[nextX2][nextY2]) continue;
            if (curL + 1 < dp[nextX][nextY][isCol]) {
                dp[nextX][nextY][isCol] = curL + 1;
                q.push({ nextX, nextY, curL + 1, isCol });
            }
        }
        // 가로일 때 회전
        if (!isCol) {
            if (isInside(curX + 1, curY, N) && isInside(curX + 1, curY + 1, N)
                && !board[curX + 1][curY] && !board[curX + 1][curY + 1]) {
                if (curL + 1 < dp[curX][curY + 1][1]) {
                    dp[curX][curY + 1][1] = curL + 1;
                    q.push({ curX, curY + 1, curL + 1, true });
                }
                if (curL + 1 < dp[curX][curY][1]) {{
                        dp[curX][curY][1] = curL + 1;
                        q.push({ curX, curY, curL + 1, true });
                    }
                }
            }
            if (isInside(curX - 1, curY, N) && isInside(curX - 1, curY + 1, N)
                && !board[curX - 1][curY] && !board[curX - 1][curY + 1]) {
                if (curL + 1 < dp[curX - 1][curY][1]) {
                    dp[curX - 1][curY][1] = curL + 1;
                    q.push({ curX - 1, curY, curL + 1, true });
                }
                if (curL + 1 < dp[curX - 1][curY + 1][1]) {
                    dp[curX - 1][curY + 1][1] = curL + 1;
                    q.push({ curX - 1, curY + 1, curL + 1, true });
                }
            }
        }
        else { //세로일 때 회전
            // 우측으로 회전
            if (isInside(curX, curY + 1, N) && isInside(curX + 1, curY + 1, N) &&
                !board[curX][curY + 1] && !board[curX + 1][curY + 1]) {
                if (curL + 1 < dp[curX][curY][0]) {
                    dp[curX][curY][0] = curL + 1;
                    q.push({ curX, curY, curL + 1, false });
                }
                if (curL + 1 < dp[curX + 1][curY][0]) {
                    dp[curX + 1][curY][0] = curL + 1;
                    q.push({ curX + 1, curY, curL + 1, false });
                }
            }
            // 좌측으로 회전
            if (isInside(curX, curY - 1, N) && isInside(curX + 1, curY - 1, N) &&
                !board[curX][curY - 1] && !board[curX + 1][curY - 1]) {
                if (curL + 1 < dp[curX][curY - 1][0]) {
                    dp[curX][curY - 1][0] = curL + 1;
                    q.push({ curX, curY - 1, curL + 1, false });
                }
                if (curL + 1 < dp[curX + 1][curY - 1][0]) {
                    dp[curX + 1][curY - 1][0] = curL + 1;
                    q.push({ curX + 1, curY - 1, curL + 1, false });
                }
            }
        }
    }
    return answer;
}
