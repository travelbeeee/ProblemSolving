/*
  스코빌 지수가 낮은 음식부터 섞어본다
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int> pq; // 스코빌 지수가 낮을수록 우선순위!
    for (int i = 0; i < scoville.size(); i++)
        pq.push(-scoville[i]);
    while (!pq.empty()) {
        if (K <= -pq.top()) break;
        
        int minScoville = -pq.top();
        pq.pop();
        if (pq.empty()) break;
        int secondMinScoville = -pq.top();
        pq.pop();

        pq.push(-(minScoville + secondMinScoville * 2));

        answer++;
    }

    if (pq.empty()) answer = -1;

    return answer;
}
