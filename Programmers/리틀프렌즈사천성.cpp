/*
    BFS

    1) 알파벳별로 시작지점과 목표지점을 저장한다.
    2) A부터 시작해서 시작지점에서 목표지점으로 방향 전환을 최소환으로 해서 BFS 탐색을 진행한다.
        2-1) 방향 전환을 1회 이하로 BFS 탐색 가능
            --> answer에 추가하고 alphabet과 board 를 reset 하고, isFinished = false로 만든다.
        2-2) 방향 전환 2회 이상 탐색 가능 혹은 탐색 불가능
            --> 넘어간다.
    
    # 주의사항!
    예를 들어, A부터 시작해서 BFS 탐색을 진행하다가 'C' 가 지워짐!
    --> 그럼 다시 A부터 시작해야됨!
    'C' 에서 이어서 'D' 로 계속 탐색을 진행하면 바뀐 board 상태에서 알파벳 순으로가 아니라 다른 순서로 진행하게됨.
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int INF = 99999999;
const int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
int visited[100][100][4]; // visited[i][j][k] := (i, j) 지점에 k 방향으로 도착했을 때 최소 방향전환 횟수

void init(int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 4; k++)
                visited[i][j][k] = INF;
}

bool isInside(int x, int y, int m, int n) {
    return (0 <= x && x < m && 0 <= y && y < n);
}

string solution(int m, int n, vector<string> board) {
    // A ~ Z
    vector<pair<int, int>> alphabet[26];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if ('A' <= board[i][j] && board[i][j] <= 'Z') alphabet[board[i][j] - 'A'].push_back({ i, j });

    int cnt = 0;
    for (int i = 0; i < 26; i++) if (!alphabet[i].empty()) cnt++;

    string answer = "";
    while (1) {
        bool isFinished = true;
        for (int i = 0; i < 26; i++) {
            if (alphabet[i].empty()) continue;

            init(m, n); // visited 배열 초기화

            // BFS탐색진행!
            queue<pair<pair<int, int>, pair<int, int>>> q;
            for (int k = 0; k < 4; k++) {
                visited[alphabet[i][0].first][alphabet[i][0].second][k] = 0;
                q.push({ {alphabet[i][0].first, alphabet[i][0].second}, {k, 0} });
            }

            char goal = board[alphabet[i][0].first][alphabet[i][0].second];
            while (!q.empty()) {
                pair<int, int> cur = q.front().first;
                int curD = q.front().second.first;
                int curC = q.front().second.second;
                q.pop();

                if (cur.first == alphabet[i][1].first && cur.second == alphabet[i][1].second) continue;

                for (int k = 0; k < 4; k++) {
                    int nextX = cur.first + dx[k], nextY = cur.second + dy[k];
                    if (!isInside(nextX, nextY, m, n)) continue;
                    if (!(board[nextX][nextY] == '.' || board[nextX][nextY] == goal)) continue;
                    if (k == curD && curC < visited[nextX][nextY][k]) {
                        visited[nextX][nextY][k] = curC;
                        q.push({ {nextX, nextY}, {k, curC} });
                    }
                    if (k != curD && curC + 1 < visited[nextX][nextY][k]) {
                        visited[nextX][nextY][k] = curC + 1;
                        q.push({ {nextX, nextY}, {k, curC + 1} });
                    }
                }
            }
            for (int k = 0; k < 4; k++) {
                if (visited[alphabet[i][1].first][alphabet[i][1].second][k] <= 1) {
                    board[alphabet[i][0].first][alphabet[i][0].second] = board[alphabet[i][1].first][alphabet[i][1].second] = '.';
                    alphabet[i].pop_back();
                    alphabet[i].pop_back();
                    answer.push_back(goal);
                    isFinished = false;
                    i = 26;
                    break;
                }
            }
        }
        if (isFinished) break;
    }

    if (answer.length() != cnt) answer = "IMPOSSIBLE";
    
    return answer;
}
