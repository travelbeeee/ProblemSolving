/*
    dp[i] := i칸을 뛰는 경우의 수
    := (i - 1)칸을 뛰는 경우의 수에서 1칸을 더 뛴 것 + (i - 2)칸을 뛰는 경우의 수에서 2칸을 더 뛴 컷 
    := (dp[i - 1] + dp[i - 2])
*/
#include <string>
#include <vector>

using namespace std;

long long solution(int n) {
    const int MOD = 1234567;
    long long dp[2001];
    dp[1] = 1, dp[2] = 2;
    for (int i = 3; i <= n; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    return dp[n];
}
