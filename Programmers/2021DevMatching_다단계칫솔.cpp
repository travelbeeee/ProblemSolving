#include <string>
#include <vector>
#include <map>

using namespace std;

int ind, p[10001], gain[10001];
map<string, int> sellerMap;

void setSellerMap(vector<string> enroll) {
    sellerMap.insert({ "-", ind++ });
    for (int i = 0; i < enroll.size(); i++)
        sellerMap.insert({ enroll[i], ind++ });
}

void setParent(vector<string> referral) {
    for (int i = 0; i < referral.size(); i++) {
        // (i + 1)번 사람의 부모가 referral[i];
        p[i + 1] = sellerMap[referral[i]];
    }
}

void divideGain(int seller, int price) {
    if (seller == 0 || price == 0) return;

    int div = price / 10;
    price -= div;
    gain[seller] += price;
    
    divideGain(p[seller], div);
}

vector<int> solution(vector<string> enroll, 
    vector<string> referral, 
    vector<string> seller, vector<int> amount) {
    
    setSellerMap(enroll);

    setParent(referral);

    for (int i = 0; i < seller.size(); i++) {
        divideGain(sellerMap[seller[i]], 100 * amount[i]);
    }

    vector<int> answer;
    for (int i = 1; i < ind; i++)
        answer.push_back(gain[i]);
    return answer;
}
