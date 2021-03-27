#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(string A, string B) {
    string C = A + B;
    string D = B + A;
    if(stoi(C) > stoi(D)) return true;
    return false;
}

string solution(vector<int> numbers) {
    vector<string> list;
    int zeroCnt = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == 0) zeroCnt++;
        else {
            string temp = "";
            while (numbers[i]) {
                temp.push_back('0' + numbers[i] % 10);
                numbers[i] /= 10;
            }
            reverse(temp.begin(), temp.end());
            list.push_back(temp);
        }
    }

    sort(list.begin(), list.end(), cmp);

    string answer = "";
    for (int i = 0; i < list.size(); i++)
        answer += list[i];
    for (int i = 0; i < zeroCnt; i++)
        answer.push_back('0');
    // 0 만 들어온 경우!! --> "000" 이 아니라 "0"
    if(answer[0] == '0') return "0";
    return answer;
}
