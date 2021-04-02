#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    const int m = 1234567;
    int fibonachi[100001]={};
    fibonachi[0] = 0, fibonachi[1] = 1;
    for (int i = 2; i <= 100000; i++)
        fibonachi[i] = (fibonachi[i - 1] + fibonachi[i - 2]) % m;
    
    return fibonachi[n];
}
