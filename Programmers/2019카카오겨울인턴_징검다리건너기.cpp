/*
  BinarySearch
  
  mid 만큼 사람이 지나간다고 하자!
  (mid - 1) 만큼 이미 사람이 지나갔을 때 k개의 연속된 밟을 수 없는 돌판이 존재한다면
  mid 번 째 사람은 지나갈 수 없다
  
*/
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    int left = 0, right = 200000000;
    while (left <= right) {
        // mid 만큼 사람이 지나간다.
        int mid = (left + right) / 2;
        
        // mid - 1만큼 사람이 지나갔을 때 k개의 연속된 0이 나오나체크
        int cnt = 0;
        bool check = false;
        for (int i = 0; i < stones.size(); i++){
            if (stones[i] - (mid - 1) <= 0) cnt++;
            else cnt = 0;
            if (cnt >= k) {
                check = true;
                break;
            }
        }
        if (check) // 너무 많이 지나감
            right = mid - 1;
        else {
            answer = mid;
            left = mid + 1;
        }
    }
    return answer;
}
