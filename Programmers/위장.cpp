/*
  옷 종류당 옷이 몇 개 있는지만 파악되면 됨!
  전체 경우의 수에서 모두 벗은 경우 1가지만 빼주면 된다.
*/
#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    map<string, int> m;
    for (int i = 0; i < clothes.size(); i++) {
        if (m.find(clothes[i][1]) == m.end()) {
            m.insert({ clothes[i][1], 1 });
        }
        else {
            m[clothes[i][1]]++;
        }
    }
    int answer = 1;
    for (auto it = m.begin(); it != m.end(); it++) {
        answer *= (it->second) + 1;
    }
    answer--;
    return answer;
}
