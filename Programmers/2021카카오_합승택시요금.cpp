/*
  플로이드와샬
  
  S에서 시작해서 어떤 K지점을 거쳐서 K->A , K->B로 택시를 타고 이동한다고 생각하면 된다.
  K를 1 ~ N 모든 후보군에 대해서 최소 요금을 계산해보면 정답이 나온다.
  
  따라서 우리는 i에서 j로 가는 최단 요금이 필요하다.
  n이 작아서 그냥 플로이드와샬로 모든 i, j까지 최단요금을 다 구해버리면 된다!
  
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    const int INF = 99999999;
    int dist[201][201] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = INF;
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for (int i = 0; i < fares.size(); i++) {
        dist[fares[i][0]][fares[i][1]] = fares[i][2];
        dist[fares[i][1]][fares[i][0]] = fares[i][2];
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int answer = INF;
    for (int i = 1; i <= n; i++)
        answer = min(answer, dist[s][i] + dist[i][a] + dist[i][b]);
    return answer;
}


// 다시 푼 풀이
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    const int INF = 99999999;

    int cost[201][201];
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if(i != j) cost[i][j] = INF;
        }
    }

    for (vector<int> fare : fares) {
        cost[fare[0]][fare[1]] = cost[fare[1]][fare[0]] = fare[2];
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (cost[i][k] + cost[k][j] < cost[i][j])
                    cost[i][j] = cost[i][k] + cost[k][j];

    int answer = INF;
    for (int i = 1; i <= n; i++)
        answer = min(answer, cost[s][i] + cost[i][a] + cost[i][b]);

    return answer;
}
