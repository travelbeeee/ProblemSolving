/*
    dp[i][j] := i번 째 행 j번 째 열에 도착했을 때 최대값
*/
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int> > land){
    int N = land.size();

    int dp[100000][4] = {};
    for (int j = 0; j < 4; j++)
        dp[0][j] = land[0][j];
    for (int i = 1; i < N; i++) {
        dp[i][0] = max(dp[i - 1][1], max(dp[i - 1][2], dp[i - 1][3])) + land[i][0];
        dp[i][1] = max(dp[i - 1][0], max(dp[i - 1][2], dp[i - 1][3])) + land[i][1];
        dp[i][2] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][3])) + land[i][2];
        dp[i][3] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2])) + land[i][3];
    }
    int answer = 0;
    for (int j = 0; j < 4; j++)
        answer = max(answer, dp[N - 1][j]);
    return answer;
}
