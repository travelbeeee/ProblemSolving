/*
    N명의 사람을 끝난 심사대에 하나씩 Greedy하게 배정하더라도
    10^9 명의 사람이므로 시간초과가 발생한다
    --> 끝나는 시간을 기준으로 이분 탐색을 진행하자!
    --> K분에 끝난다고 하면 심사하는데 M분이 걸리는 심사관은 K / M 명을 처리할 수 있다.
    --> N 명을 다 처리할 수 있는 최소 시간을 찾자.
*/
#include <string>
#include <vector>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;

    long long N = n;
    long long left = 1, right = 1000000000000000000;
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long cnt = 0;
        for (int i = 0; i < times.size(); i++)
            cnt += mid / times[i];
        if (cnt >= N) { // 지금 시간으로 충분히 처리 가능!
            right = mid - 1;
            answer = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}
