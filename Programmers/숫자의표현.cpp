/*
  완전탐색  완전탐색
*/
#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    // i에서 시작해서 더해가기!
    for (int i = 1; i <= n; i++) {
        int s = 0;
        for (int j = i; ; j++) {
            s += j;
            if (s == n) answer++;
            if (s >= n) break;
        }
    }
    return answer;
}
