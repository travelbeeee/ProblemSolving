#include <string>
#include <vector>
#include <queue>

using namespace std;

bool canChange(string str, string goal) {
    int cnt = 0;
    for (int i = 0; i < str.length(); i++)
        if (str[i] != goal[i]) cnt++;
    if (cnt == 1) return true;
    return false;
}

int solution(string begin, string target, vector<string> words) {
    const int INF = 99999999;
    int dp[50] = {};
    for (int i = 0; i < words.size(); i++)
        dp[i] = INF;

    queue<pair<string, int>> q;
    q.push({ begin, 0 });
    while (!q.empty()) {
        string cur = q.front().first;
        int len = q.front().second;
        q.pop();

        if (cur == target) continue;
      
        for (int i = 0; i < words.size(); i++) {
            // cur 과 words[i]가 알파벳 하나 변환으로 가능한지!
            // 가능하다면 이미 더 작은 값으로 방문한 적 있는지!
            if (canChange(cur, words[i]) && len + 1 < dp[i]) {
                dp[i] = len + 1;
                q.push({ words[i], len + 1 });
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < words.size(); i++)
        if (words[i] == target) answer = dp[i];
    return answer;
}
