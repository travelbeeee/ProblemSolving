/*
    Parsing
    입력된 로그를 Parsing해서 시작시간 ~ 끝시간을 MilliSeconds 로 표현하자!
    --> Seconds로 표현하면 double을 사용해야되서 부동소수점오류가 발생한다.
    --> 1000을 전체적으로 곱해서 MS로 표현하자.

    처리해야될 예외가 많다...!
    1) 2016-09-15 00:000:00.000 에 끝난 프로그램도 있으므로 시작 시간을 3초씩 다 더해주자...!
    2) 3.1s 같은 경우네는 3 / 1 로 나눠서 Parsing하는데 1 은 100ms 이므로 뒤에 00을 더 붙여줘야한다.
        if (playTimeMS.empty()) playTimeMS = "000";
        else if (playTimeMS.length() == 1) {
            playTimeMS.push_back('0');
            playTimeMS.push_back('0');
        }
        else if (playTimeMS.length() == 2) {
            playTimeMS.push_back('0');
        }
    3) N이 2000이므로 우리는 그냥 모든 로그의 
    시작지점 ~ 시작지점 + 1초
    끝지점 ~ 끝지점 + 1초 에 몇 개의 로그들이 겹치는지 다 확인해봐도된다!
    이때, [A ~ A + 1000] 이 아니라 [A ~ A + 999] 를 확인해야된다. ( MilliSeconds 표현)
    또, 어떤 로그의 시작지점 ~ 어떤 로그의 끝 지점이 [A ~ A + 999] 범위를 포함하며 커져버리는 경우도 count 해야한다.
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> parseIntoMS(string line) {
    int hour = stoi(line.substr(11, 2));
    int minute = stoi(line.substr(14, 2));
    int second = stoi(line.substr(17, 2));
    int milliSecond = stoi(line.substr(20, 3));

    int endTime = (3600 * hour + 60 * minute + second) * 1000 + milliSecond + 3000;

    int ind = 0;
    string playTime = line.substr(24);
    string playTimeS = "";
    string playTimeMS = "";
    while (ind < playTime.length()) {
        playTimeS += playTime[ind++];
        if (playTime[ind] == '.' || playTime[ind] == 's') {
            ind++;
            break;
        }
    }
    while (ind < playTime.length()) {
        playTimeMS += playTime[ind++];
        if (ind < playTime.length() && playTime[ind] == 's') break;
    }
    if (playTimeMS.empty()) playTimeMS = "0";
    else if (playTimeMS.length() == 1) {
        playTimeMS.push_back('0');
        playTimeMS.push_back('0');
    }
    else if (playTimeMS.length() == 2) {
        playTimeMS.push_back('0');
    }
    int startTime = endTime - (1000 * stoi(playTimeS) + stoi(playTimeMS)) + 1;
    return { startTime, endTime };
}

int solution(vector<string> lines) {
    vector<pair<int, int>> logs; // 로그의 시작시간 ~ 끝 시간을 ms로 기록
    for (int i = 0; i < lines.size(); i++)
        logs.push_back(parseIntoMS(lines[i]));

    int answer = 0;
    for (int i = 0; i < logs.size(); i++) {
        // logs[i] 시작시간부터 1초동안 얼마나 많이 처리되나 보자!
        int cnt = 0;
        for (int j = 0; j < logs.size(); j++) {
            if ((logs[i].first <= logs[j].first && logs[j].first <= logs[i].first + 999)
                || (logs[i].first <= logs[j].second && logs[j].second <= logs[i].first + 999)
                || (logs[j].first <= logs[i].first && logs[i].first + 999 <= logs[j].second)) cnt++;
        }
        answer = max(answer, cnt);
        // logs[i] 끝시간부터 1초동안 얼마나 많이 처리되나 보자!
        cnt = 0;
        for (int j = 0; j < logs.size(); j++) {
            if ((logs[i].second <= logs[j].first && logs[j].first <= logs[i].second + 999)
                || (logs[i].second <= logs[j].second && logs[j].second <= logs[i].second + 999)
                || (logs[j].first <= logs[i].second && logs[i].second + 999 <= logs[j].second)) cnt++;
        }
        answer = max(answer, cnt);
    }
    return answer;
}
