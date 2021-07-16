/*
  Piroity_Queue 를 이용한 스케쥴링
  
	waiting : 줄서있는 계산대 { 시간, {계산대번호,회원번호}}
	시간이 작은순서대로 / 계산대번호가 큰 순서대로

	emptyCOunter : 비어있는 계산대 {계산대번호} 
	계산대 번호가 작은 순선대로

	1)현재 시간을 waiting 에서 가장 작은 시간으로 맞춘다.
	2)현재 시간에 waiting이 끝난 회원들을 쇼핑몰 밖으로 보낸다.
	  ( 계산대 번호가 큰 순서대로 pq에 넣었으므로 앞에서부터 꺼낸다. )
	3) 비어있는 계산대에 대기 중인 손님을 추가로 배치한다.
*/
#include<iostream>
#include<queue>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, K, time = 0, customerInd = 0;
	long long ans = 0, outPeople = 1;
	priority_queue<pair<int,pair<int,int>>> waiting;
	priority_queue<int> emptyCounter; // 비어있는계산대 --> 번호가 작은 순대로
	vector<pair<int, int>> customer(100000);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> customer[i].first >> customer[i].second;
	}

	for (int i = 0; i < N && i < K; i++) {
		waiting.push({ -(time + customer[i].second),{i, customer[i].first} });
	}
	customerInd = K; // K개의 계산대에 K명의 사람을 이미 추가함

	while (outPeople <= N) {
		// 현재 대기가 가장 적게 남은 사람한테 맞춰서 시간 갱신
		if(!waiting.empty()) time = -waiting.top().first;
		// 현재 시간에 쇼핑을 만료한 사람a과 해당 카운터를 날리자
		while (!waiting.empty() && -waiting.top().first <= time) {
			emptyCounter.push(-waiting.top().second.first);
			ans += 1L * waiting.top().second.second * outPeople;
			outPeople++;
			waiting.pop();
		}
		while (!emptyCounter.empty() && customerInd < N) {
			waiting.push({ -(time + customer[customerInd].second), {-emptyCounter.top(), customer[customerInd].first} });
			emptyCounter.pop();
			customerInd++;
		}
	}

	cout << ans << '\n';
	return 0;
}
