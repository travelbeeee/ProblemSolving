/*
    탈 수 있는 항공권 그냥 다 타보자!!
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> route;

void DFS(string cur, string res, vector<bool> visited, vector<vector<string>> tickets) {
    // 탈 수 있는 항공권 다 탄 케이스!
    if (res.length() == 3 * ((int)tickets.size() + 1)) {
        route.push_back(res);
        return;
    }
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i][0] == cur && !visited[i]) {
            visited[i] = true;
            DFS(tickets[i][1], res + tickets[i][1], visited, tickets);
            visited[i] = false;
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<bool> visited(tickets.size(), false);
    
    DFS("ICN", "ICN", visited, tickets);
    
    sort(route.begin(), route.end());
    
    vector<string> answer;
    for (int i = 0; i < (route[0].length() / 3); i++){
        answer.push_back(route[0].substr(3 * i, 3));
    }
    return answer;
}
