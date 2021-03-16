/*
    Parsing
    
    KMP를 사용해서 문제를 해결할 수도 있지만, Input크기가 크지 않아서 그냥 입력 값을 Parsing 한 후 
    멜로디가 있는지 전체 순회하며 찾아보면 된다.
    
    0) #이 붙은 음은 소문자로 바꾼다. ( C# -> c)
    1) musicinfos --> 플레이시간 / 제목 / 플레이시간만큼 연주한 음 으로 전처리한다.
*/

#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

struct music {
    int playTime;
    string title, melody;
};

string solution(string m, vector<string> musicinfos) {
    vector<music> musicInfos;
    // 전처리
    for (int i = 0; i < musicinfos.size(); i++) {
        string startTime = musicinfos[i].substr(0, 5);
        string endTime = musicinfos[i].substr(6, 5);
        int j = musicinfos[i].find(',', 12);
        string title = musicinfos[i].substr(12, j - 12);
        string melody = musicinfos[i].substr(j + 1);
        for (int j = 0; j < melody.length(); j++) {
            if (j + 1 < melody.length() && melody[j + 1] == '#') {
                melody[j] = (melody[j] - 'A') + 'a';
                melody.erase(j + 1, 1);
            }
        }
        int hour = (stoi(endTime.substr(0, 2)) - stoi(startTime.substr(0, 2)));
        // if (hour < 0) { // 23:59를 넘어서 진행!
        //     hour += 24;
        //     hour -= stoi(endTime.substr(0,2));
        // }
        int minute = (stoi(endTime.substr(3, 2)) - stoi(startTime.substr(3, 2)));
        if (minute < 0) {
            minute += 60;
            hour--;
        }

        int playTime = 60 * hour + minute;

        string totalMelody = "";
        int time = playTime;
        while (time) {
            if (time >= melody.length()) {
                totalMelody += melody;
                time -= (int)melody.length();
            }
            else {
                for (int j = 0; j < time; j++)
                    totalMelody += melody[j];
                time = 0;
            }
        }
        musicInfos.push_back({ playTime, title, totalMelody });
    }
    for (int i = 0; i < m.length(); i++) {
        if (i + 1 < m.length() && m[i + 1] == '#') {
            m[i] = (m[i] - 'A') + 'a';
            m.erase(i + 1, 1);
        }
    }
    // 전처리한 msuciInfos 에서 Melody가 있는 부분을 찾자
    string answer = "(None)";
    int ansPlayTime = 0;
    for (int i = 0; i < musicInfos.size(); i++) {
        if (musicInfos[i].melody.find(m) == string::npos) continue;
        if (ansPlayTime < musicInfos[i].playTime) {
            ansPlayTime = musicInfos[i].playTime;
            answer = musicInfos[i].title;
        }
    }
    return answer;
}
