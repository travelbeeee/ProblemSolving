/*
  N을 K번 사용해서 만들 수 있는 수들의 집합
  = NNNNN...N (K번 사용)
  + N을 1번 사용한 집합과 N을 (K - 1)번 사용한 집합을 사칙 연산해서 나온 결과
  + N을 2번 사용한 집합과 N을 (K - 2)번 사용한 집합을 사칙 연산해서 나온 결과
  .....
  + N을 (K - 1)번 사용한 집합과 N을 1번 사용한 집합을 사칙 연산해서 나온 결과
  
  가 성립한다. 
  
  따라서,
  res[i] := N을 (i + 1)번 사용해서 나온 결과 집합으로 정의하자.
  --> res[0] 에는 { N } 하나만 존재!
  --> res[1] 은 NN과 res[0] 과 res[0] 에서 나온 결과들을 사칙 연산해서 나온 결과!
  --> res[2]는  NNN과 res[0] 과 res[1]에서 나온 결과들을 사칙 연산해서 나온 결과 + res[1]과 res[0]에서 나온 결과들을 사칙 연산해서 나온 결과
  --> - 랑 / 연산은 연산 순서에 따라 달라지므로 따로 처리하고, + , * 는 
  
*/
#include <string>
#include <map>

using namespace std;

map<int, int> res[8]; // result[i] 는 N을 (i + 1)번 사용해서 나온 결과들!
 
int solution(int N, int number) {
    res[0].insert({ N, 1 });
    
    int m = 10;
    int n = N;
    for (int i = 1; i < 8; i++) {
        n += m * N;
        m *= 10;
        res[i].insert({ n, 1 });
        // res[j] res[k] 의 조합으로 i를 만드는 경우의 수를 추가하자!
        for (int j = 0; j < i; j++){
            // res[j] 와 res[(i - 1) - j] 로 경우의 수를 만들자!
            for (auto it = res[j].begin(); it != res[j].end(); it++) {
                for (auto that = res[(i - 1) - j].begin(); that != res[(i - 1) - j].end(); that++) {
                    int n1 = it->first, n2 = that->first;
                    if (res[i].find(n1 + n2) == res[i].end()) res[i].insert({ n1 + n2, 1 });
                    if (n1 - n2 >= 0 && res[i].find(n1 - n2) == res[i].end()) res[i].insert({ n1 - n2, 1 });
                    if (n2 - n1 >= 0 && res[i].find(n2 - n1) == res[i].end()) res[i].insert({ n2 - n1, 1 });
                    if (res[i].find(n1 * n2) == res[i].end()) res[i].insert({ n1 * n2 , 1 });
                    if (n2 != 0 && n1 % n2 == 0 && res[i].find(n1 / n2) == res[i].end()) res[i].insert({ n1 / n2, 1 });
                    if (n1 != 0 && n2 % n1 == 0 && res[i].find(n2 / n1) == res[i].end()) res[i].insert({ n2 / n1, 1 });
                }
            }
        }
    }
    int answer = -1;
    for (int i = 0; i < 8; i++)
        for(auto it = res[i].begin(); it != res[i].end(); it++)
            if (it->first == number) {
                answer = i + 1;
                i = 8;
                break;
            }

    return answer;
}
