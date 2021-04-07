#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int dp[500][500] = {};
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < triangle.size(); i++) {
        dp[i][0] = triangle[i][0] + dp[i - 1][0];
        dp[i][i] = triangle[i][i] + dp[i - 1][i - 1];
    }
    // i줄은 (i + 1)개의 숫자가 존재!
    for (int i = 1; i < triangle.size(); i++)
        for (int j = 1; j < i; j++)
            dp[i][j] = triangle[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j]);
    
    int answer = 0;
    for (int j = 0; j < triangle.size(); j++)
        answer = max(answer, dp[triangle.size() - 1][j]);
    return answer;
}
