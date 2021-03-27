/*
  2배씩 점프할 수 있으므로
  목표 N을 /2 해가며 목표를 줄여본다.
  --> N이 홀수라면 + 1 해서 최소한의 에너지를 쓰고
  --> N이 짝수라면 * 2 는 에너지 소모가 없으므려 /2 로 목표를 줄인다.
*/
#include <iostream>
using namespace std;

int solution(int n)
{
    int ans = 0;
    while(n){
        ans += n % 2;
        n /= 2;
    }
    return ans;
}
