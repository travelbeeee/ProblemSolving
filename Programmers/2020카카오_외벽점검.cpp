/*
    1) weak 배열을 2배로 늘리면 원형 해결
    -> weak {1, 5, 6, 10}
    --> weak {1, 5, 6, 10, 13, 17, 18, 22}
    
    2) weak 배열에서 k개씩 연속된 부분을 dist로 덮으면됨
    --> backtracking
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

void backtracking(int cnt, int ind, vector<bool>* useDist, vector<int>& dist, vector<int>& weak, int l, int r, int* answer) {
    if (ind > r) {
        *answer = min(*answer, cnt);
        return;
    }

    for (int i = 0; i < dist.size(); i++) {
        if (useDist->at(i)) continue;
        
        // dist[i] 만큼 weak[ind] 부터 이동!
        int newInd = ind;
        while (weak[newInd] <= weak[ind] + dist[i]) {
            newInd++;
        }
        useDist->at(i) = true;
        backtracking(cnt + 1, newInd, useDist, dist, weak, l, r, answer);
        useDist->at(i) = false;
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    int K = weak.size();
    for (int i = 0; i < K; i++)
        weak.push_back(weak[i] + n);

    int answer = 99999999;
    for (int i = 0; i < K; i++) {
        // weak[i] 부터 weak[i + K - 1]까지 dist로 덮덮
        vector<bool> useDist(dist.size(), false);
        backtracking(0, i, &useDist, dist, weak, i, i + K - 1, &answer);
    }

    if (answer == 99999999) answer = -1;
    return answer;
}
