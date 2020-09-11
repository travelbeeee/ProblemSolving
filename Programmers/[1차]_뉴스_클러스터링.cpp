/*
    입력으로 주어진 String을 2글자씩 끊어가며 비교한다.
    이때 2글자가 모두 alphabet으로 이루어진 경우는 소문자로 바꾼 뒤, count를 해둔다.
    count는 [26][26] 배열을 선언해 ['a'~'z']['a'~'z']에 해당되는 case를 모두 다룰 수 있다.
*/
#include <string>
#include <algorithm>
using namespace std;

bool isAlphabet(char c) {
    if ('A' <= c && c <= 'Z') return true;
    if ('a' <= c && c <= 'z') return true;
    return false;
}

int solution(string str1, string str2) {
    int cnt1[26][26] = {}, cnt2[26][26] = {};

    for (int i = 0; i < str1.length() - 1; i++) {
        if (isAlphabet(str1[i]) && isAlphabet(str1[i + 1])) {
            if ('A' <= str1[i] && str1[i] <= 'Z') str1[i] = (str1[i] - 'A') + 'a';
            if ('A' <= str1[i + 1] && str1[i + 1] <= 'Z') str1[i + 1] = (str1[i + 1] - 'A') + 'a';
            cnt1[str1[i] - 'a'][str1[i + 1] - 'a']++;
        }
    }

    for (int i = 0; i < str2.length() - 1; i++) {
        if (isAlphabet(str2[i]) && isAlphabet(str2[i + 1])) {
            if ('A' <= str2[i] && str2[i] <= 'Z') str2[i] = (str2[i] - 'A') + 'a';
            if ('A' <= str2[i + 1] && str2[i + 1] <= 'Z') str2[i + 1] = (str2[i + 1] - 'A') + 'a';
            cnt2[str2[i] - 'a'][str2[i + 1] - 'a']++;
        }
    }
    int andSet = 0, orSet = 0;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++) {
            andSet += min(cnt1[i][j], cnt2[i][j]);
            orSet += max(cnt1[i][j], cnt2[i][j]);
        }
    int answer;
    if (andSet == 0 && orSet == 0) answer = 65536;
    else answer = (andSet * 65536) / orSet;
    return answer;
}
