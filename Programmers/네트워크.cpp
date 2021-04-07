#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    bool visited[200] = {};
    for (int i = 0; i < n; i++) {
        if (!visited[i]) { // 아직 방문 안했으면 최대한 타고 방문해보자!
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();

                for (int j = 0; j < n; j++) {
                    if (computers[cur][j] && !visited[j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
            answer++;
        }
    }
    return answer;
}
