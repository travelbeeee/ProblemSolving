/*
    key를 90도씩 돌려가며 모든 지점에서 고!
    
    주의할점 !
    
    key의 우측하단이 lock의 좌측상단과 맞는 경우부터
    key의 좌측상단이 lock의 우측하단과 맞는 경우까지!
    범위를 (-M + 1) ~ (N + (M - 1)) 까지 봐야된다.
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int N, M;

vector<vector<int>> changeKey(vector<vector<int>> key) {
    vector<vector<int>> changedKey = key;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            changedKey[i][j] = key[(M - 1) - j][i];
    return changedKey;
}

bool isInside(int x, int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

bool checkKey(vector<vector<int>> key, vector<vector<int>> lock, int i, int j) {
    for (int k = 0; k < M; k++)
        for (int l = 0; l < M; l++){
            if (!isInside(i + k, j + l)) continue;
            if (key[k][l] && lock[i + k][j + l]) return false; // 둘다 돌기
            if (key[k][l] && !lock[i + k][j + l]) lock[i + k][j + l] = 1;
        }
    for (int k = 0; k < N; k++)
        for (int l = 0; l < N; l++)
            if (!lock[k][l]) return false;
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    M = key.size(), N = lock.size();

    vector<vector<int>> tempKey = key;
    vector<vector<int>> tempLock = lock;
    for (int t = 0; t < 4; t++) {
        // 90도 key변환
        tempKey = changeKey(tempKey);
        for (int i = -M; i < N + M; i++) {
            for (int j = -M; j < N + M; j++) {
                tempLock = lock;
                if (checkKey(tempKey, tempLock, i, j)) return true;
            }
        }
    }
    return false;
}
