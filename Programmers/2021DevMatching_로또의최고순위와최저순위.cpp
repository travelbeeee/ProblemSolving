#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    int correctCnt = 0, zeroCnt = 0;
    for (int i = 0; i < lottos.size(); i++) {
        if (lottos[i] == 0) zeroCnt++;
        for (int j = 0; j < win_nums.size(); j++)
            if (lottos[i] == win_nums[j]) correctCnt++;
    }

    vector<int> answer;
    int maxCnt = correctCnt + zeroCnt;
    if (maxCnt == 6) answer.push_back(1);
    else if (maxCnt == 5) answer.push_back(2);
    else if (maxCnt == 4) answer.push_back(3);
    else if (maxCnt == 3) answer.push_back(4);
    else if (maxCnt == 2) answer.push_back(5);
    else answer.push_back(6);

    if (correctCnt == 6) answer.push_back(1);
    else if (correctCnt == 5) answer.push_back(2);
    else if (correctCnt == 4) answer.push_back(3);
    else if (correctCnt == 3) answer.push_back(4);
    else if (correctCnt == 2) answer.push_back(5);
    else answer.push_back(6);

    return answer;
}
