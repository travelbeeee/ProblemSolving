#include <vector>

using namespace std;

// l번 ~ r번 아파트까지 W 크기의 5g 기지국을 최소로 설치하는 값
int getInstallBuilding(int l, int r, int W) {
    if (r - l + 1 <= 0) return 0;
    return (r - l + 1) / W + ((r - l + 1) % W != 0);
}

int solution(int n, vector<int> stations, int w) {
    int answer = 0, W = 2 * w + 1;

    stations.push_back(n + w + 1);
    answer += getInstallBuilding(1, stations[0] - w - 1, W);
    for (int i = 0; i < stations.size() - 1; i++) {
        answer += getInstallBuilding(stations[i] + w + 1, stations[i + 1] - w - 1, W);
    }
    return answer;
}
