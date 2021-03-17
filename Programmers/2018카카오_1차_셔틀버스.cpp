/*
    1) 시간을 모두 분으로 변환하자.
    2) 콘을 제외한 나머지들을 대상으로 버스 시뮬레이션을 돌려보자.
    3) 마지막 버스에 콘이 타기 위해서는
        3-1) 마지막 버스에 자리가 빈다! --> 마지막 버스 출발시간
        3-2) 마지막 버스에 자리가 부족하다 --> 마지막 버스에 마지막에 탄 사람보다 일찍!
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string changeTime(int time) {
    int hour = time / 60;
    int minute = time % 60;

    string res = "";
    if (hour < 10) res.push_back('0');
    else res.push_back('0' + hour / 10);
    res.push_back('0' + hour % 10);
    res.push_back(':');
    if (minute < 10) res.push_back('0');
    else res.push_back('0' + minute / 10);
    res.push_back('0' + minute % 10);

    return res;
}

string solution(int n, int t, int m, vector<string> timetable) {
    vector<int> busTime;
    vector<int> timeTable;

    for (int i = 0; i < n; i++)
        busTime.push_back({ 540 + t * i });
    for (int i = 0; i < timetable.size(); i++)
        timeTable.push_back({ 60 * stoi(timetable[i].substr(0, 2)) + stoi(timetable[i].substr(3, 2)) });

    sort(timeTable.begin(), timeTable.end());

    int b = 0, p = 0;
    vector<int> bus[10];
    while (b < busTime.size() && p < timeTable.size()) {
        // b번 째 버스에 사람들을 태울 수 있으면 최대한 태워보자.
        while (p < timeTable.size() && timeTable[p] <= busTime[b] && bus[b].size() < m) {
            bus[b].push_back(timeTable[p++]);
        }
        b++;
    }
    string answer = "";
    if (bus[b - 1].size() < m) {
        answer = changeTime(busTime[b - 1]);
    }
    else {
        answer = changeTime(bus[b - 1][m - 1] - 1);
    }
    return answer;
}
