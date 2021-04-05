/*
  row 와 col이 주어지면 
  2 * row + 2 * col - 4 = brown
  row * col - brown = yellow 가 성립한다!
  따라서, 위의 조건을 만족하는 row, col을 순회하며 찾아보자.
*/
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    for (int row = 1; row <= 2501; row++)
        for(int col = 1; col <= 2501; col++)
            if (2 * row + 2 * col - 4 == brown &&
                (row * col - brown) == yellow) {
                answer.push_back(col);
                answer.push_back(row);
                row = 2502, col = 2502;
            }
    return answer;
}
