/*
    A팀 / B팀을 모두 sorting 한 후에
    투포인터를 이용해서 
    현재 A팀 팀원 보다 큰 B팀원이랑 매치를 시키자!
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int answer = 0;
    int indA = 0, indB = 0, N = A.size();
    while (indA < N && indB < N) {
        if (A[indA] < B[indB]) // A팀원보다 B팀원이 더 큼!
            indA++, indB++, answer++;
        else // A팀원을 이길 수 있는 B팀원을 데려오자!
            indB++;
    }
    return answer;
}
