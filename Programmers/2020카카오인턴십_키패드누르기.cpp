/*
    단순구현

    1 2 3 (3, 0) (3, 1) (3, 2)
    4 5 6 (2, 0) (2, 1) (2, 2)
    7 8 9 (1, 0) (1, 1) (1, 2)
    * 0 # (0, 0) (0, 1) (0, 2)
*/
#include <string>
#include <vector>
#include <cmath>
using namespace std;

string solution(vector<int> numbers, string hand) {
    pair<int, int> number[10] = {
        {0, 1}, {3, 0}, {3, 1}, {3, 2}, {2, 0},
        {2, 1}, {2, 2}, {1, 0}, {1, 1}, {1, 2}
    };
    pair<int, int> left = { 0, 0 }, right = { 0, 2 };

    string answer = "";
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == 0 || (numbers[i] % 3) == 2) {
            int leftD = abs(left.first - number[numbers[i]].first) +
                abs(left.second - number[numbers[i]].second);
            int rightD = abs(right.first - number[numbers[i]].first) +
                abs(right.second - number[numbers[i]].second);
            if (leftD < rightD) {
                left = number[numbers[i]];
                answer += "L";
            }
            else if (leftD > rightD) {
                right = number[numbers[i]];
                answer += "R";
            }
            else {
                if (hand == "right") {
                    right = number[numbers[i]];
                    answer += "R";
                }
                else {
                    left = number[numbers[i]];
                    answer += "L";
                }
            }
        }
        else if (numbers[i] % 3 == 1) {
            answer += "L";
            left = number[numbers[i]];
        }
        else {
            answer += "R";
            right = number[numbers[i]];
        }
    }
    return answer;
}
