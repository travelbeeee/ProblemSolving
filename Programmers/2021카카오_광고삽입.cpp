#include <string>
#include <vector>
#include <algorithm>

#include<iostream>

using namespace std;

int timeToInt(string time) {
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    int second = stoi(time.substr(6, 2));
    return 3600 * hour + 60 * minute + second;
}

string timeToString(int time) {
    string res = "";
    int hour = time / 3600;
    time %= 3600;
    int minute = time / 60;
    time %= 60;
    int second = time;

    res.push_back((hour / 10) + '0');
    res.push_back((hour % 10) + '0');
    res.push_back(':');
    res.push_back((minute / 10) + '0');
    res.push_back((minute % 10) + '0');
    res.push_back(':');
    res.push_back((second / 10) + '0');
    res.push_back((second % 10) + '0');
    return res;
}

long long sum[360005] = {};

string solution(string play_time, string adv_time, vector<string> logs) {
    int playTime = timeToInt(play_time);
    int advTime = timeToInt(adv_time);

    for (int i = 0; i < logs.size(); i++) {
        int startTime = timeToInt(logs[i].substr(0, 8));
        int endTime = timeToInt(logs[i].substr(9, 8));
        sum[startTime]++;
        sum[endTime]--;
    }

    // 각 시간별로 몇명이 보고있는지 
    for (int i = 1; i < 360005; i++)
        sum[i] += sum[i - 1];

    // 0초부터 i초까지 몇명이 보면서 왔는지
    for (int i = 1; i < 360005; i++)
        sum[i] += sum[i - 1];

    // left ~ right 까지 광고실행 중
    long long maxTime = 0;
    int ind;
    for (int i = 0; i <= playTime - advTime; i++) {
        int left = i, right = i + advTime;
        long long time;
        if (left == 0)
            time = sum[right - 1];
        else
            time = sum[right - 1] - sum[left - 1];

        if (maxTime < time) {
            maxTime = time;
            ind = i;
        }
    }
    string answer = timeToString(ind);

    return answer;
}
