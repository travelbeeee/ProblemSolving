/*
  단순 구현 문제
  단계별로 구현하면된다.
  
  입력도 작아서 시간초과 혹은 최적화를 생각하지않아도 된다.
*/

#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string temp_id = "";
    // 1단계
    for (int i = 0; i < new_id.length(); i++)
        if ('A' <= new_id[i] && new_id[i] <= 'Z')
            new_id[i] = (new_id[i] - 'A') + 'a';
    // 2단계
    for (int i = 0; i < new_id.length(); i++){
        if ('a' <= new_id[i] && new_id[i] <= 'z') continue;
        if ('0' <= new_id[i] && new_id[i] <= '9') continue;
        if (new_id[i] == '.' || new_id[i] == '-' || new_id[i] == '_') continue;
        new_id[i] = 'E';
    }
    for (int i = 0; i < new_id.length(); i++)
        if (new_id[i] != 'E') temp_id.push_back(new_id[i]);
    new_id = temp_id;
    temp_id = "";
    // 3단계
    for (int i = 0; i < (int)new_id.length() - 1; i++){
        if (new_id[i] == '.') {
            int j = i + 1;
            while (j < (int)new_id.length() && new_id[j] == '.') {
                new_id[j] = 'E';
                j++;
            }
        }
    }
    for (int i = 0; i < new_id.length(); i++)
        if (new_id[i] != 'E') temp_id.push_back(new_id[i]);
    new_id = temp_id;
    temp_id = "";
    // 4단계
    if (!new_id.empty()) {
        if (new_id[0] == '.') new_id[0] = 'E';
        if (new_id[(int)new_id.length() - 1] == '.') new_id[(int)new_id.length() - 1] = 'E';
    }
    for (int i = 0; i < new_id.length(); i++)
        if (new_id[i] != 'E') temp_id.push_back(new_id[i]);
    new_id = temp_id;
    temp_id = "";
    // 5단계
    if (new_id.empty()) new_id.push_back('a');
    // 6단계
    if (16 <= (int)new_id.length()) new_id = new_id.substr(0, 15);
    if (new_id[14] == '.') new_id = new_id.substr(0, 14);
    // 7단계
    while ((int)new_id.length() < 3) {
        new_id.push_back(new_id[(int)new_id.length() - 1]);
    }
    return new_id;
}
