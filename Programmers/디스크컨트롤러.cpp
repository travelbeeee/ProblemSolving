#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0, N = jobs.size();

    sort(jobs.begin(), jobs.end());

    priority_queue<pair<int, int>> waiting; // { 수행시간, 요청시점 } --> 현재 대기 중에 가장 금방 끝나는 애 부터 진행하자.
    int ind = 0, time = jobs[0][0];
    while (!(ind >= N && waiting.empty())) {
        // 현재 time에서 대기열에 넣을 수 있는 애들을 넣자!
        while (ind < N) {
            if (jobs[ind][0] <= time) {
                waiting.push({ -jobs[ind][1], jobs[ind][0] });
                ind++;
            }
            else break;
        }
        if (waiting.empty()) { // 대기열이 없음 --> 시간을 더 진행시키자
            time = jobs[ind][0];
            continue;
        }
        pair<int, int> working = waiting.top();
        waiting.pop();
        // 현재 time에서 working.first 만큼 진행!
        time += -working.first;
        answer += (time - working.second); // 대기시간만큼!
    }

    return answer / N;
}
