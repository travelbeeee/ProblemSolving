/*
    Union-Find 를 이용한 MST
*/
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int p[100];

void init(int n) {
    for (int i = 0; i < n; i++) p[i] = -1;
}

int find(int cur) {
    if (p[cur] < 0) return cur;
    return p[cur] = find(p[cur]);
}

void merge(int a, int b) {
    int pA = find(a), pB = find(b);
    if (pA == pB) return;
    if (p[pA] < p[pB]) {
        p[pA] += p[pB];
        p[pB] = pA;
    }
    else {
        p[pB] += p[pA];
        p[pA] = pB;
    }
}

int solution(int n, vector<vector<int>> costs) {
    init(n);

    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < costs.size(); i++){
        pq.push({ -costs[i][2], { costs[i][0], costs[i][1]}});
    }

    int answer = 0;
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int a = pq.top().second.first, b = pq.top().second.second;
        pq.pop();

        if (find(a) == find(b)) continue;
        merge(a, b);
        answer += cost;
    }
    return answer;
}
