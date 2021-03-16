#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> files) {

    vector <pair<string, pair<int, int>>> v;
    for (int i = 0; i < files.size(); i++) {
        string head = "", number = "";
        int j = 0;
        while (j < files[i].length()) {
            if ('0' <= files[i][j] && files[i][j] <= '9') break;
            head += files[i][j];
            j++;
        }
        while (j < files[i].length()) {
            if (!('0' <= files[i][j] && files[i][j] <= '9')) break;
            number += files[i][j];
            j++;
        }
        for (int k = 0; k < head.length(); k++) {
            if ('A' <= head[k] && head[k] <= 'Z') head[k] = (head[k] - 'A') + 'a';
        }
        v.push_back({ head, {stoi(number), i} });
    }
    sort(v.begin(), v.end());

    vector<string> answer;
    for (int i = 0; i < v.size(); i++)
        answer.push_back(files[v[i].second.second]);

    return answer;
}
