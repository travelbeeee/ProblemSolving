#include <string>
#include <vector>

using namespace std;

const int INF = 99999999;

int countDigit(int num) {
    int cnt = 0;
    while (num) {
        num /= 10;
        cnt++;
    }
    return cnt;
}

// aabbaccc
int compress(string s, int size) {
    int ind = 0, res = 0;
    while (ind < s.length()) {
        // ind부터 size만큼 가져온거랑 ind + size부터 size만큼 가져온거랑 비교해서 count하자
        int cnt = 1;
        while (ind + 2 * size - 1 < s.length()) {
            if (s.substr(ind, size) != s.substr(ind + size, size)) break;
            ind += size;
            cnt++;
        }
        if (cnt >= 2) {
            res += size + countDigit(cnt);
            ind += size;
        }
        else {
            res += size;
            ind += size;
        }
    }
    if (ind > s.length())
        res -= (ind - s.length());
    return res;
}

int solution(string s) {
    if (s.length() == 1) return 1;

    int answer = INF;
    for (int i = 1; i <= (s.length() / 2); i++)
        answer = min(answer, compress(s, i));
    return answer;
}
