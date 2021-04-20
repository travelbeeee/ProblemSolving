/*
  남은 작업량의 제곱 값을 낮추려면, 가장 높은 작업량을 일해야된다!
  --> priority_queue 를 이용해서 가장 높은 작업량을 요하는 일을 1시간씩 일하자!
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    priority_queue<int> pq;
    for (int i = 0; i < works.size(); i++)
        pq.push(works[i]);
    
    for (int i = 0; i < n; i++) {
        int top = pq.top();
        pq.pop();
        if (top > 0) top--;
        pq.push(top);
    }

    long long answer = 0;
    while (!pq.empty()) {
        int top = pq.top();
        pq.pop();
        answer += (top * top);
    }
    return answer;
}
