/*
  백트레킹을 통한 완전탐색
  
  입력이 작아서 백트레킹으로 코스메뉴 후보가 될 수 있는 모든 코스 후보를 만들고,
  해당 코스가 2번 이상 등장하는지 확인하면 된다.
  
*/
#include <string>
#include <vector>
#include<algorithm>

#include<iostream>

using namespace std;

vector<string> btList;
int alphabetCnt[26];
bool visited[26];

void init(void) {
    btList.clear();
    for (int i = 0; i < 26; i++) alphabetCnt[i] = 0, visited[i] = false;
}

void backtracking(string cur, int s, int goal) {
    if ((int)cur.length() == goal) {
        btList.push_back(cur);
        return;
    }
    for (int i = s; i < 26; i++) {
        if (!visited[i] && alphabetCnt[i] >= 2) {
            visited[i] = true;
            cur.push_back('A' + i);
            backtracking(cur, i + 1, goal);
            cur.pop_back();
            visited[i] = false;
        }
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    init();

    for (int i = 0; i < orders.size(); i++)
        for (int j = 0; j < orders[i].length(); j++)
            alphabetCnt[orders[i][j] - 'A']++;

    for (int i = 0; i < orders.size(); i++)
        sort(orders[i].begin(), orders[i].end());

    vector<pair<int, string>> courseList;
    for (int i = 0; i < course.size(); i++) {
        // 2 개 이상의 alphabet 중에서 course[i]개 만큼 뽑아보자!
        backtracking("", 0, course[i]);
        
        for (int j = 0; j < btList.size(); j++) {
            // btList[j] 가 orders에 2개 이상 있는지!
            int cnt = 0;
            for (int k = 0; k < orders.size(); k++) {
                bool checkCnt = true;
                bool checkOrder[26] = {};
                for (int l = 0; l < orders[k].length(); l++)
                    checkOrder[orders[k][l] - 'A'] = true;
                for (int l = 0; l < btList[j].size(); l++)
                    if (checkOrder[btList[j][l] - 'A'] == false)
                        checkCnt = false;
                if (checkCnt)
                    cnt++;
            }
            if (cnt >= 2) {
                courseList.push_back({ cnt, btList[j] });
            }
        }
        btList.clear();
    }

    vector<string> answer;
    for (int i = 0; i < course.size(); i++) {
        int maxCnt = 0;
        for (int j = 0; j < courseList.size(); j++)
            if (courseList[j].second.length() == course[i])
                maxCnt = max(maxCnt, courseList[j].first);
        for (int j = 0; j < courseList.size(); j++)
            if (courseList[j].second.length() == course[i] &&
                courseList[j].first == maxCnt)
                answer.push_back(courseList[j].second);
    }
    sort(answer.begin(), answer.end());
    return answer;
}

/*
* 다시 푼 풀이
*/
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void backtracking(int s, int size, int goal, string res, string order, map<string, int>* m) {
    if (size == goal) {
        if (m->find(res) == m->end()) {
            m->insert({ res, 1 });
        }
        else {
            m->find(res)->second = m->find(res)->second + 1;
        }
        return;
    }

    for (int i = s; i < order.length(); i++) {
        res.push_back(order[i]);
        backtracking(i + 1, size + 1, goal, res, order, m);
        res.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    // orders 오른차순으로 정리
    for (string order : orders) {
        for (int i = 0; i < order.length(); i++) {
            for (int j = 0; j < order.length() - 1; j++) {
                if (order[j] > order[j + 1]) {
                    char c = order[j];
                    order[j] = order[j + 1];
                    order[j + 1] = c;
                }
            }
        }
    }

    vector<string> answer;
    for (int courseSize : course) {
        map<string, int> m;
        for (string order : orders)
            backtracking(0,0 , courseSize, "", order, &m);

        int maxCnt = -1;
        for (auto it = m.begin(); it != m.end(); it++) {
            maxCnt = max(maxCnt, it->second);
        }
        for (auto it = m.begin(); it != m.end(); it++) {
            if(it->second == maxCnt && maxCnt >= 2)
                answer.push_back(it->first);
        }
    }

    sort(answer.begin(), answer.end());

    return answer;
}
