/*
  dp[i][j] := s[i ~ j] 가 팰린드롬인지 아닌지.
  --> 기본 셋팅으로 1글자, 2글자짜리 팰린드롬을 다 체크해놓자!
  --> 3글자(len) 부터 탐색을 시작해서,
    dp[i + 1][i + len - 1](기존팰림드롬) 에 추가로 앞 뒤 글자가 같다면 s[i] == s[i + len]
    dp[i][i + len] 도 팰린드롬!
*/
#include <string>
#include <algorithm>

using namespace std;

int solution(string s){
    int N = s.length();
  
    bool dp[2500][2500] = {};
    for (int i = 0; i < N; i++){
        dp[i][i] = true;
        if (i + 1 < N && s[i] == s[i + 1]) dp[i][i + 1] = true;
    }

    for (int len = 2; len < N; len++)
        for (int i = 0; i <= N - len; i++)
            if (s[i] == s[i + len] && dp[i + 1][i + len - 1])
                dp[i][i + len] = true;

    int answer = 1;
    for (int i = 0; i < s.length(); i++)
        for (int j = i + 1; j < s.length(); j++)
            if (dp[i][j]) answer = max(answer, (j - i) + 1);
    return answer;
}
