/*
  
*/
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    int N = prices.size();
    stack<pair<int, int>> s;
    vector<int> answer(N, 0);
    for (int i = 0; i < N; i++) {
        if (s.empty() || s.top().first <= prices[i]) {
            s.push({ prices[i], i });
        }
        else { // s.top().first > prices[i] --> 가격이 떨어짐!
            while (!s.empty() && s.top().first > prices[i]) {
                answer[s.top().second] = (i - s.top().second);
                s.pop();
            }
            s.push({ prices[i], i });
        }
    }
    return answer;
}
