/*
  구현
  
  vector erase 메소드를 이용하지않으면 복잡해진다...
*/
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long solution(string expression) {
    vector<long long> numbers;
    vector<char> operations;
    string number = "";
    for (int i = 0; i < expression.length(); i++) {
        if ('0' <= expression[i] && expression[i] <= '9') {
            number += expression[i];
        }
        else {
            numbers.push_back(stol(number));
            number = "";
            operations.push_back(expression[i]);
        }
    }
    numbers.push_back(stol(number));

    long long answer = -1;
    string priority[6] = {
        "+*-", "+-*", "*+-", "*-+", "-*+", "-+*"
    };
    for (int i = 0; i < 6; i++) {
        vector<long long> tempN = numbers;
        vector<char> tempOp = operations;
        for (int j = 0; j < 3; j++) {
            // priority[i][j] 가 지금 해야되는 연산!
            int k = 0;
            while (k < tempOp.size()) {
                if (tempOp[k] == priority[i][j]) {
                    long long temp;
                    if (priority[i][j] == '+') temp = tempN[k] + tempN[k + 1];
                    else if (priority[i][j] == '*') temp = tempN[k] * tempN[k + 1];
                    else temp = tempN[k] - tempN[k + 1];
                    tempN[k] = temp;
                    tempN.erase(tempN.begin() + (k + 1));
                    tempOp.erase(tempOp.begin() + k);
                }
                else
                    k++;
            }
        }
        answer = max(answer, abs(tempN[0]));
    }
    return answer;
}
