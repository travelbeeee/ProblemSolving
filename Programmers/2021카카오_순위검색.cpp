/*
  O(info * query) 를 하면 시간 초과가 발생할 것 같았음...!
  --> 그냥 O(info * query)로 먼저 구현해보니 시간 초과 발생...!
  
  --> info를 먼저 전처리해서 score들을 저장해두자.
  cnt[language][position][career][food] 에 해당하는 score들이 담긴 vector!
  "-" 경우를 위해 cnt의 마지막 idx 들은 값을 신경쓰지않는 상황을 의미
  
  --> info를 전처리해서 score들을 상황별로 저장한 다음 query마다 info를 순회하면 시간 초과가 발생하므로
    socre들을 저장한 cnt 배열을 binary search로 탐색해야된다!
  --> sorting 을 진행
  --> 그 후 binary Search를 통해 원하는 조건, 원하는 score 이상의 사람들이 몇 명인지 탐색한다.  
*/

#include <string>
#include <vector>
#include<algorithm>

#include<iostream>

using namespace std;


vector<string> strSplit(string str) {
    vector<string> list;
    int i = 0;
    string temp = "";
    while (i < str.length()) {
        if (str[i] == ' ') {
            if (temp != "and") list.push_back(temp);
            temp = "";
        }
        else {
            temp += str[i];
        }
        i++;
    }
    list.push_back(temp);

    return list;
}

vector<int> strToInt(vector<string> strs) {
    vector<int> res;
    if (strs[0] == "cpp") res.push_back(0);
    else if (strs[0] == "java") res.push_back(1);
    else if (strs[0] == "python") res.push_back(2);
    else res.push_back(3);

    if (strs[1] == "backend") res.push_back(0);
    else if (strs[1] == "frontend") res.push_back(1);
    else res.push_back(2);

    if (strs[2] == "junior") res.push_back(0);
    else if (strs[2] == "senior") res.push_back(1);
    else res.push_back(2);

    if (strs[3] == "chicken") res.push_back(0);
    else if (strs[3] == "pizza") res.push_back(1);
    else res.push_back(2);

    return res;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> cnt[4][3][3][3];
    for (int i = 0; i < info.size(); i++) {
        vector<string> infoSplit = strSplit(info[i]);
        vector<int> infoToInt = strToInt(infoSplit);
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    for (int m = 0; m < 3; m++)
                        if ((j == infoToInt[0] || j == 3) && (k == infoToInt[1] || k == 2) && (l == infoToInt[2] || l == 2) &&  (m == infoToInt[3] || m == 2)){
                            cnt[j][k][l][m].push_back(stoi(infoSplit[4]));
                        }
    }
    for (int j = 0; j < 4; j++)
        for (int k = 0; k < 3; k++)
            for (int l = 0; l < 3; l++)
                for (int m = 0; m < 3; m++)
                    sort(cnt[j][k][l][m].begin(), cnt[j][k][l][m].end());

    vector<int> answer;
    for (int i = 0; i < query.size(); i++) {
        vector<string> querySplit = strSplit(query[i]);
        vector<int> queryToInt = strToInt(querySplit);

        int left = 0, right = cnt[queryToInt[0]][queryToInt[1]][queryToInt[2]][queryToInt[3]].size() - 1;
        int score = stoi(querySplit[4]), ind = cnt[queryToInt[0]][queryToInt[1]][queryToInt[2]][queryToInt[3]].size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (cnt[queryToInt[0]][queryToInt[1]][queryToInt[2]][queryToInt[3]][mid] < score) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
                ind = mid;
            }
        }
        answer.push_back(cnt[queryToInt[0]][queryToInt[1]][queryToInt[2]][queryToInt[3]].size() - ind);
    }
    return answer;
}

// 다시 푼 풀이
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int changePLtoInt(string pl) {
    if (pl == "cpp") return 0;
    else if (pl == "java") return 1;
    else if (pl == "python") return 2;
    return 3;
}

int changePositionToInt(string position) {
    if (position == "backend") return 0;
    else if (position == "frontend") return 1;
    return 2;
}

int changeCareerToInt(string career) {
    if (career == "junior") return 0;
    else if (career == "senior") return 1;
    return 2;
}

int changeFoodToInt(string food) {
    if (food == "chicken") return 0;
    else if (food == "pizza") return 1;
    return 2;
}

vector<string> split(string input, char delimiter) {
    vector<string> res;
    stringstream ss(input);
    string temp;
    while (getline(ss, temp, delimiter)) {
        res.push_back(temp);
    }
    return res;
}

int selectQuery(int score, vector<int>& scores) {

    int left = 0, right = scores.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (score <= scores[mid]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return scores.size() - left;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> score[4][3][3][3];

    for (string s : info) {
        vector<string> splitInfo = split(s, ' ');
        int plList[2] = { changePLtoInt(splitInfo[0]), 3 };
        int positionList[2] = { changePositionToInt(splitInfo[1]), 2 };
        int careerList[2] = { changeCareerToInt(splitInfo[2]), 2 };
        int foodList[2] = { changeFoodToInt(splitInfo[3]), 2 };
        for (int pl : plList)
            for (int position : positionList)
                for (int career : careerList)
                    for (int food : foodList)
                        score[pl][position][career][food].push_back(stoi(splitInfo[4]));
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    sort(score[i][j][k][l].begin(), score[i][j][k][l].end());
    vector<int> answer;
    for (string s : query) {
        vector<string> splitQuery = split(s, ' ');
        int pl = changePLtoInt(splitQuery[0]);
        int po = changePositionToInt(splitQuery[2]);
        int ca = changeCareerToInt(splitQuery[4]);
        int fo = changeFoodToInt(splitQuery[6]);

        answer.push_back(selectQuery(stoi(splitQuery[7]), score[pl][po][ca][fo]));
    }

    return answer;
}
