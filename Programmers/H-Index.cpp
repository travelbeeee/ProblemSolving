#include <string>
#include <vector>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    for (int H = 0; H <= 10000; H++) {
        int smallThanH = 0, biggerThanH = 0;
        for (int i = 0; i < citations.size(); i++)
            if (H <= citations[i]) biggerThanH++;
        if (biggerThanH >= H) answer = H;
    }
    return answer;
}
