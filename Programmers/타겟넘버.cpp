/*
  백트레킹을 이용해 2^20개의 모든 조합 쌍을 확인해본다.
*/
#include <string>
#include <vector>

using namespace std;


void backtracking(int cur, int goal, int target, int* answer, vector<bool> op, vector<int> numbers) {
    if (cur == goal) {
        int res = 0;
        for (int i = 0; i < goal; i++)
            if (op[i]) res += numbers[i];
            else res -= numbers[i];
        if (res == target) *answer = (*answer) + 1;
        return;
    }
    op[cur] = false;
    backtracking(cur + 1, goal, target, answer, op, numbers);
    op[cur] = true;
    backtracking(cur + 1, goal, target, answer, op, numbers);
}

int solution(vector<int> numbers, int target) {
    int N = numbers.size();
    int answer = 0;
    vector<bool> op(N, false);

    backtracking(0, numbers.size(), target , &answer, op, numbers);

    return answer;
}
