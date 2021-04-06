/*
  results를 기반으로 
  나를 이긴 사람과 나에게 진 사람을 count 하고
  이긴 사람 + 진 사람이 나를 제외한 모든 사람들이라면 순위가 확실한 사람이다!
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    vector<int> graph[101]; // a 가 b에게 졌으면 a -> b로 연결해주자
    for (int i = 0; i < results.size(); i++)
        graph[results[i][1]].push_back(results[i][0]);

    // winner[i] := i번 사람을 이긴 사람
    // loser[i] := i번 사람에게 진 사람
    int winner[101] = {}, loser[101] = {};
    // i번 째 사람마다 BFS 탐색을 진행! --> i번 째 사람을 이긴 사람들이 나옴
    for (int i = 1; i <= n; i++) {
        queue<int> q;
        bool visited[101]={};
        q.push(i);
        visited[i] = true;
        do {
            int cur = q.front();
            q.pop();

            for (int next : graph[cur]) {
                if(visited[next]) continue;
                winner[i]++;
                loser[next]++;
                q.push(next);
                visited[next] = true;
            }
        } while (!q.empty());
    }
    int answer = 0;
    for (int i = 1; i <= n; i++)
        if (winner[i] + loser[i] == n - 1) answer++;
    return answer;
}
