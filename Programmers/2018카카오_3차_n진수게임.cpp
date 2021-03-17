/*
  1부터 시작해서 N진수로 변환한 후,
  N진수로 변환된 수(baseN)를 순회하며, 
  현재 baseN[i] 에 해당되는 people번 째 사람이 튜브라면 answer에 쌓아준다.
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(int n, int t, int m, int p) {
    char list[17] = { '0', '1', '2', '3', '4', '5','6',
    '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    string answer = "";
    int number = 0, people = 1;
    while (t) {
        string baseN = "";
        int baseNumber = number;
        while (1) {
            baseN.push_back(list[baseNumber % n]);
            baseNumber /= n;
            if (baseNumber == 0) break;
        }
        reverse(baseN.begin(), baseN.end());
        for (int i = 0; i < baseN.length(); i++) {
            // baseN[i], people번 째 사람
            if ((people - 1) % m == (p - 1)) {
                t--;
                answer.push_back(baseN[i]);
            }
            if (t == 0) break;
            people++;
        }
        cout << baseN << '\n';
        cout << "answer : " << answer << '\n';
        number++;
    }
    return answer;
}
