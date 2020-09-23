/*
	postOrder의 마지막이 root 가 되고 이를 기준으로 leftSubtree, rightSubtree를 나눌 수 있다.
	--> leftSubtree , rightSubtree로 나눠가며 tree의 모양을 저장한다.
	tree[K][0] := K의 왼쪽 자식
	tree[K][1] := K의 오른쪽 자식
*/
#include<iostream>

using namespace std;

int N;
int tree[100001][2]; // left right
int inOrder[100001];
int postOrder[100001];

void solve(int inLeft, int inRight, int postLeft, int postRight, int par) {
	int l = inLeft;
	while (inOrder[l] != postOrder[postRight]) { // root를 찾을때까지
		l++;
	} 
	// 왼쪽 오른쪽 subtree의 개수
	int leftSubtree = (l - inLeft);
	int rightSubtree = (inRight - l);

	// 왼쪽 서브트리로 타고가자!
	if (leftSubtree != 0) {
		tree[postOrder[postRight]][0] = postOrder[postLeft + leftSubtree - 1];
		solve(inLeft, inLeft + leftSubtree - 1, postLeft, postLeft + leftSubtree - 1, postOrder[postRight]);
	}
	// 오른쪽 서브트리로 타고가자!
	if (rightSubtree != 0) {
		tree[postOrder[postRight]][1] = postOrder[postRight - 1];
		solve(inLeft + leftSubtree + 1, inRight, postLeft + leftSubtree, postRight - 1, postOrder[postRight]);
	}
}

void preOrder(int N) {
	cout << N << ' ';
	if (tree[N][0]) preOrder(tree[N][0]);
	if (tree[N][1]) preOrder(tree[N][1]);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> inOrder[i];
	for (int i = 0; i < N; i++)
		cin >> postOrder[i];

	// 트리 생성!
	int root = postOrder[N - 1];
	solve(0, N - 1, 0, N - 1, root);

	// preOrder !!
	preOrder(root);

	return 0;
}
