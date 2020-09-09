#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#define ll long long

using namespace std;

struct Point {
	int x, y, w;
};

struct Tree {
	ll lsum, rsum, sum, maxsum;
};

int N, leaf_size;
ll res = 0;
vector<int> x, y;
vector<Point> p;
Tree t[8192];

bool cmp(Point a, Point b) {
	if (a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

void clear(void) {
	for (int i = 0; i < 8192; i++)
		t[i].lsum = t[i].rsum = t[i].sum = t[i].maxsum = 0;
}

void update(int n, int w) {
	int c = leaf_size + n;
	t[c].lsum = t[c].rsum = t[c].sum = t[c].maxsum += w;
	while (c > 1) {
		c /= 2;
		int l = 2 * c, r = 2 * c + 1;
		t[c].sum = t[l].sum + t[r].sum;
		t[c].lsum = max(t[l].lsum, t[l].sum + t[r].lsum);
		t[c].rsum = max(t[r].rsum, t[l].rsum + t[r].sum);
		t[c].maxsum = max(max(t[l].rsum + t[r].lsum, t[c].sum), max(t[l].maxsum, t[r].maxsum));
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	leaf_size = 1 << ((int)ceil(log2(N)));

	for (int i = 0, j, k, l; i < N; i++) {
		cin >> j >> k >> l;
		p.push_back({ j, k, l });
		x.push_back(j);
		y.push_back(k);
	}
	// 좌표압축과정
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	x.erase(unique(x.begin(), x.end()), x.end());
	y.erase(unique(y.begin(), y.end()), y.end());

	for (int i = 0; i < p.size(); i++) {
		p[i].x = lower_bound(x.begin(), x.end(), p[i].x) - x.begin();
		p[i].y = lower_bound(y.begin(), y.end(), p[i].y) - y.begin();
	}
	sort(p.begin(), p.end(), cmp);

	// 이제 y값 후보 중에서 2개를 뽑는 모든 경우에서 최대로 얻을 수 있는 이득을 계산하자!
	for (int i = 0; i < y.size(); i++) {
		clear();
		int k = 0;
		while (k < p.size() && p[k].y < i)
			k++;
		for (int j = i; j < y.size(); j++) {
			while (k < p.size() && i <= p[k].y && p[k].y <= j) {
				update(p[k].x, p[k].w);
				k++;
			}
			//cout << i << "에서 시작해서 " << j << "까지 최대값  : " << t[1].maxsum << endl;
			res = max(res, t[1].maxsum);
		}
	}
	cout << res << '\n';
	return 0;
}
