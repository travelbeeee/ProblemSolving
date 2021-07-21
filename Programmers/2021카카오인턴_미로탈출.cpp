/*
    DP / Bitmasking / BFS

    1) 트랩이 최대 10개이므로 1 ~ 10까지 번호를 부여한 후, 비트마스킹을 이용한 DP+BFS 탐색을 진행한다.
    2) 
    중요한 것은 내가 지금 밟고 있는 곳과 다음에 밟을 곳의 상태이다.
    트랩이 몇 개 발동했냐에 따라 A -> B로 가는 길을 이용할 수 있는지, B -> A로 가는 길을 이용할 수 있는지가 결정된다.
        thisTrap 현재 내가 밟고 있는 곳이 트랩이고 발동했는지
        nextTrap 다음에 내가 밟을 곳이 트랩이고 발동했는지
        --> 한 쪽만 true일 경우에는 원래 주어진 roads 의 반대 길을 이용할 수 있고, 둘다 true 혹은 false일 경우에는 원래 주어진 길을 이용할 수 있다.
        --> XOR 연산을 이용하고, 원래 주어진 길은 false, 반대 길을 true로 새롭게 길을 표현해주자 (vector<pair<int, pair<int, bool>>> map 에 표현)
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    const int INF = 99999999;
    int trapN = 1;
    int trapNum[1001] = {};
    int dp[1001][1 << 11];
    vector<pair<int, pair<int, bool>>> map[1001];

    for (int trap : traps) {
        trapNum[trap] = trapN++;
    }
    for (int i = 0; i < roads.size(); i++) {
        map[roads[i][0]].push_back({ roads[i][1], { roads[i][2], false} }); // 정방향
        map[roads[i][1]].push_back({ roads[i][0], { roads[i][2], true} }); // 역방향
    }

    for (int node = 1; node <= n; node++)
        for (int status = 0; status < (1 << 11); status++)
            dp[node][status] = INF;

    queue<pair<int, pair<int, int>>> q;
    q.push({ start, { 0, 0} });
    dp[start][0] = 0;
    while (!q.empty()) {
        int node = q.front().first;
        int status = q.front().second.first;
        int cost = q.front().second.second;
        q.pop();

        if (dp[node][status] < cost) continue;
        if (node == end) continue;

        for (pair<int, pair<int, int>> next : map[node]) {
            int nextNode = next.first;
            int nextCost = cost + next.second.first;
            bool reversed = next.second.second;
            int nextStatus = status;

            bool thisTrap = status & (1 << trapNum[node]);
            bool nextTrap = status & (1 << trapNum[nextNode]);
            if ((thisTrap ^ nextTrap) && !reversed) // 역방향이어야되는데 정방향인 케이스
                continue;
            if (!(thisTrap ^ nextTrap) && reversed) // 정방향이어야되는데 역방향인 케이스
                continue;
            if (trapNum[nextNode])
                nextStatus = status ^ (1 << trapNum[nextNode]);
            if (nextCost < dp[nextNode][nextStatus]) {
                dp[nextNode][nextStatus] = nextCost;
                q.push({ nextNode, {nextStatus, nextCost} });
            }
        }
    }
    int answer = INF;
    for (int j = 0; j < (1 << 11); j++)
        answer = min(answer, dp[end][j]);
    return answer;
}
