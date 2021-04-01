/*
  
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(string s) {
    int zeros = 0, times = 0;
    while (s != "1") {
        int len = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == '1') len++;
        // len을 2진수로 돌리자
        zeros += (s.length() - len);
        times++;

        string nextS = "";
        while (len) {
            nextS.push_back('0' + len % 2);
            len /= 2;
        }
        reverse(nextS.begin(), nextS.end());
        s = nextS;
    }
    vector<int> answer;
    answer.push_back(times);
    answer.push_back(zeros);
    return answer;
}
