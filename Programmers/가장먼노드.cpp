#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 99999999;

vector<int> dijkstra(int n, vector<vector<int>> edge) {
    // 노드 번호 하나씩 다운!
    vector<int> graph[20000];
    for (int i = 0; i < edge.size(); i++) {
        graph[edge[i][0] - 1].push_back(edge[i][1] - 1); 
        graph[edge[i][1] - 1].push_back(edge[i][0] - 1);
    }

    // 0번 노드부터 최단 거리를 다 구해보자!
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>> pq;
    pq.push({ 0, 0 });
    dist[0] = 0;
    while (!pq.empty()) {
        int len = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (int next : graph[cur]) {
            if (len + 1 < dist[next]) {
                dist[next] = len + 1;
                pq.push({ -(len + 1), next });
            }
        }
    }
    return dist;
}

int solution(int n, vector<vector<int>> edge) {
    vector<int> dist = dijkstra(n, edge);

    int answer = 0, maxDist = 0;
    for (int i = 0; i < n; i++)
        maxDist = max(maxDist, dist[i]);
    for (int i = 0; i < n; i++)
        if (dist[i] == maxDist) answer++;

    return answer;
}
