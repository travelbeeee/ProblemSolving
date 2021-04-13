#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    if (n > s) // 불가능한경우!
        answer.push_back(-1);
    else {
        int q = s / n, r = s % n;
        for (int i = 0; i < n; i++)
            answer.push_back(q);
        for (int i = 0; i < r; i++)
            answer[n - 1 - i]++;
    }
    return answer;
}
