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

// 다시 푼 풀이
#include <string>
#include <vector>

using namespace std;

void turnClockwise(vector<vector<int>>* key) {
    int M = key->size();

    vector<vector<int>> tempKey;
    for (int i = 0; i < M; i++)
        tempKey.push_back(key->at(i));

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            tempKey[i][j] = key->at(M - 1 - j).at(i);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            key->at(i).at(j) = tempKey[i][j];
}

bool isInside(int x, int y, int N) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int M = key.size(), N = lock.size();
    int goalCnt = 0; // 채워야되는 홈부분
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            goalCnt += 1 - lock[i][j];

    for (int turn = 0; turn < 4; turn++) {
        //l key를 (i, j)부터 시작해서 놓아본다
        for (int i = -(M - 1); i <= N - 1; i++) {
            for (int j = -(M - 1); j <= N - 1; j++) {
                // key[k][l] 부분이 lock[i + k][j + l] 부분과 만나고 있다
                int cnt = 0;
                for (int k = 0; k < M; k++) {
                    for (int l = 0; l < M; l++) {
                        if (!isInside(i + k, j + l, N)) continue;
                        if (key[k][l] == 1 && lock[i + k][j + l] == 1) { // 돌기와 돌기가 만남
                            k = M, l = M;
                            break;
                        }
                        else if (key[k][l] == 1 && lock[i + k][j + l] == 0) {
                            cnt++;
                        }
                    }
                }
                if (cnt == goalCnt)
                    return true;
            }
        }
        turnClockwise(&key);
    }
    return false;
}
