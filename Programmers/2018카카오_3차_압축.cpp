/*
  자료구조 Map을 이용해서 사전을 구현하면 된다.
  
*/
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    map<string, int> m;
    string alp = "A";
    int ind = 1;

    for(int i = 0; i < 26; i++){
        m.insert({ alp, ind++ });
        alp[0] = (alp[0] + 1);
    }

    int i = 0, j;
    while (i < msg.length()) {
        string temp = "";
        for (j = i; j < msg.length(); j++) {
            temp += msg[j];
            if (m.find(temp) == m.end()) {
                // 없다! --> 추가하고 그 전꺼 색인추출
                m.insert({ temp, ind++ });
                temp.pop_back();
                answer.push_back(m[temp]);
                break;
            }
        }
        if (j == msg.length()) { // 끝까지 다 탐색하고 사전에 있음!
            answer.push_back(m[temp]);
            break;
        }
        i += (j - i);
    }
    return answer;
}
