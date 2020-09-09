/*
    우리가 고려해야 될 속성은 최대 8개
    --> bitMaks로 모든 경우(모든 후보키)를 다룰 수 있음!
    --> 예를 들어 1011 이란 비트는 0번 1번 3번 속성을 선택해 후보키로 삼은 경우라고 생각하자
    --> 속성이 M개라면 (1 ~ 2^M-1) 까지 다 순회하면 된다!
    --> 또, 모든 경우에 대해 getBit 함수를 통해 선택된 속성들의 index를 얻을 수 있다.

    먼저 유일성부터 따져보자
    유일성은 서로 다른 사람들이 현재 선택된 후보 속성 중에 다른 값이 하나라도 있으면 된다!
    --> N명의 사람 중 2명씩 후보 속성들을 순회하며 다른 값이 있나 체크
    --> 다른 경우가 하나라도 있으면 2명은 그 후보 속성들로 구분이 가능
    
    그 다음으로는 최소성을 따져야한다.
    유일성이 통과된 후보키들을 getBitCount 함수를 통해 몇 개의 속성을 후보로 삼았는지 알 수 있다.
    --> getBitCount 함수를 기준으로 유일성이 보장된 후보키들을 sort한다.
    --> 즉, 속성을 적게 선택한 경우가 앞으로 가게 된다.
    --> 최소성을 만족하려면 내가 지금 선택한 속성보다 적게 선택한 경우에서 나랑 겹치는 부분이 있으면 안된다
    --> bit 연산 & 를 이용해서 해결 가능!

    ex) 1011 과 0011 이 있다고 하자. 0011 때문에 1011은 최소성을 만족 못하고
        1011 & 0011 = 0011 라는 사실을 이용해서 체크 가능하다.
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getBit(int x) {
    vector<int> v;
    int index = 0;
    while (x) {
        if (x % 2) v.push_back(index);
        x /= 2;
        index++;
    }
    return v;
}

int getBitCount(int x) {
    int ans = 0;
    while (x) {
        if (x % 2) ans++;
        x /= 2;
    }
    return ans;
}

bool compare(int A, int B) {
    return getBitCount(A) <= getBitCount(B);
}

int solution(vector<vector<string>> relation) {
    int N = relation.size(), M = relation[0].size();
    int maxSize = (1 << M);

    vector<int> bitMask;
    for (int i = 1; i < maxSize; i++) {
        vector<int> cols = getBit(i);
        
        bool isBit = true;
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                bool isDif = false;
                for (int l = 0; l < cols.size(); l++) {
                    if (relation[j][cols[l]] != relation[k][cols[l]]) {
                        isDif = true;
                    }
                }
                if (!isDif) 
                    isBit = false;
            }
        }
        if (isBit) bitMask.push_back(i);
    }
    
   sort(bitMask.begin(), bitMask.end(), compare);
    
    int ans = 0;
    for (int i = 0; i < bitMask.size(); i++) {
        bool isAns = true;
        for (int j = 0; j < i; j++) {
            if ((bitMask[i] & bitMask[j]) == bitMask[j]) isAns = false;
        }
        if (isAns) ans++;
    }
    return ans;
}
