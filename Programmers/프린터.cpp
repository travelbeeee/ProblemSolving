/*
  대기열을 의미하는 deque과
  현재 대기열에서 가장 높은 선호도를 알려주는 priority_queue를 이용하면 된다.
*/
#include <string>
#include <vector>
#include <queue>

#include<iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    priority_queue<int> pq;
    deque<int> q;
    for (int i = 0; i < priorities.size(); i++) {
        pq.push(priorities[i]);
        q.push_back(i);
    }
    int ind = 0;
    while (!pq.empty()) {
        // 현재 순서
        int cur = q.front();
        q.pop_front();
        if (priorities[cur] == pq.top()) { // 중요도가 제일 높음!
            pq.pop();
            ind++;
            if (cur == location) break;
        }
        else {
            q.push_back(cur);
        }
    }
    return ind;
}
