/*
  two pointer
  
  left, right 투 포인터를 이용해 (left ~ right - 1) 범위의 보석들을 체크한다.
  
  이때, 모든 종류의 보석을 다 찾은 경우라면 left를 올려가며 답을 갱신하고
  아니라면 right를 올려가며 보석을 추가한다.
  
*/
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<string> gems) {
    int ind = 0, N = gems.size();

    map<string, int> m;
    for (int i = 0; i < gems.size(); i++) {
        if (m.find(gems[i]) == m.end())
            m.insert({ gems[i], ind++ });
    }

    // ind개의 보석을 뽑아야됨
    int ansL = 0, ansR = gems.size() - 1;
    int left = 0, right = 0;
    map<string, int> selected;
    while (1) {
        while (selected.size() == ind) { // 보석을 다 찾음 --> left를 올려가며 범위를 줄이자.
            if ((right - 1) - left < ansR - ansL) { // 답갱신
                ansR = right - 1, ansL = left;
            }
            selected[gems[left]]--;
            if (selected[gems[left]] == 0) {
                selected.erase(gems[left]);
            }
            left++;
        }
        if (right == N) break;
        // 보석을 다 못찾음 --> right를 늘려가며 보석을 찾자.
        if (selected.find(gems[right]) == selected.end())
            selected.insert({ gems[right++], 1 });
        else
            selected[gems[right++]]++;
    }
    vector<int> answer;
    answer.push_back(ansL + 1);
    answer.push_back(ansR + 1);
    return answer;
}
