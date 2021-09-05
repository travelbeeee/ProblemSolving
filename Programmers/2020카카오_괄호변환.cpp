#include <string>
#include <vector>
#include <stack>

using namespace std;

bool checkCorrectStr(string str) {
    stack<int> s;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') s.push(i);
        else {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

string makeCorrectStr(string w) {
    if (w.empty()) return "";

    int lCnt = 0, rCnt = 0;
    for (int i = 0; i < w.length(); i++) {
        if (w[i] == '(') lCnt++;
        else rCnt++;

        if (lCnt == rCnt) {
            string u = w.substr(0, i + 1);
            string v = w.substr(i + 1);

            if (checkCorrectStr(u)) {
                return u + makeCorrectStr(v);
            }
            else {
                u = u.substr(1);
                u.pop_back();
                for (int i = 0; i < u.length(); i++) {
                    if (u[i] == '(') u[i] = ')';
                    else u[i] = '(';
                }
                return "(" + makeCorrectStr(v) + ")" + u;
            }
            break;
        }
    }
}

string solution(string p) {
    return makeCorrectStr(p);
}
