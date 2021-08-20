/*
	1) 각 자리별로 가능한 숫자들을 다 구하자.

	2) 각 자리별로 가능한 숫자들을 구하면 전체 경우의 수를 구할 수 있다.
	그 후, 각 자리별로 가능한 숫자 * (전체 경우의 수 / 각 자리별 가능 숫자의 수 ) 를 모두 합하면 전체 합을 구할 수 있다.

	예를 들어, 10의 자리로 가능한 숫자가 3, 4 이고 전체 8가지의 경우의 수가 나오는 상황이라면
	30, 40은 8 / 10의자리로가능한숫자 = 4개씩 생기게 된다.
*/

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> digits(10);
vector<string> nums;

void init(void) {
	nums.push_back("####.##.##.####"); // 0
	nums.push_back("..#..#..#..#..#"); // 1
	nums.push_back("###..#####..###"); // 2
	nums.push_back("###..####..####"); // 3
	nums.push_back("#.##.####..#..#"); // 4
	nums.push_back("####..###..####"); // 5
	nums.push_back("####..####.####"); // 6
	nums.push_back("###..#..#..#..#"); // 7
	nums.push_back("####.#####.####"); // 8
	nums.push_back("####.####..####"); // 9
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	string bulbs[5];

	init();

	cin >> N;
	for (int i = 0; i < 5; i++)
		cin >> bulbs[i];

	// 일의 자리, 십의 자리.. 각 자리별로 가능한 모든 숫자를 구하자.
	for (int digit = 1; digit <= N; digit++) {
		string bulb = "";
		for (int r = 0; r < 5; r++)
			for (int c = 0; c < 3; c++)
				bulb.push_back(bulbs[r][4 * N - 1 - (3 * digit + digit - 1) + c]);

		for (int num = 0; num <= 9; num++) {
			// nums[num] 과 비교해서 현재 bulb로 만들 수 있는지!
			bool isPossible = true;
			for (int j = 0; j < 3 * 5; j++) {
				if (bulb[j] == '#' && nums[num][j] == '.')
					isPossible = false;
			}
			if (isPossible){
				digits[digit].push_back(num);
			}
		}
	}

	// 각 자리별로 만들 수 있는 숫자가 없는 경우 --> -1
	for (int digit = 1; digit <= N; digit++){
		if (digits[digit].empty()) {
			cout << -1 << '\n';
			return 0;
		}
	}

	long long totalCount = 1;
	for (int digit = 1; digit <= N; digit++) {
		totalCount *= 1L * digits[digit].size();
	}

	long long totalSum = 0;
	int mul = 1;
	for (int digit = 1; digit <= N; digit++) {
		for (int num : digits[digit])
			totalSum += (mul * num) * (totalCount / digits[digit].size());
		mul *= 10;
	}
	cout << (1.0 * totalSum) / (1.0 * totalCount) << '\n';

}
