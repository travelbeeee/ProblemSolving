#include<iostream>

using namespace std;

int T, N;
string cube[6][3][4];
string order;

void setCube(void) {
	char color[6] = { 'w', 'g', 'r', 'b', 'o', 'y' };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube[i][j][k] = color[i];
}

void turnCubeFace(int c, bool dir) {
	string tempCube[3][4] = {};
	if (dir) { // 시계방향
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tempCube[i][j] = cube[c][2 - j][i];
	}
	else { // 반시계방향
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tempCube[i][j] = cube[c][j][2 - i];
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cube[c][i][j] = tempCube[i][j];
}

void turnCube(string order) {
	if (order == "U+") { // 윗면을 시계방향으로
		turnCubeFace(0, true);
		string tempLine[4] = { cube[2][0][0], cube[2][0][1], cube[2][0][2] };
		cube[2][0][0] = cube[3][0][0];
		cube[2][0][1] = cube[3][0][1];
		cube[2][0][2] = cube[3][0][2];
		
		cube[3][0][0] = cube[4][0][0];
		cube[3][0][1] = cube[4][0][1];
		cube[3][0][2] = cube[4][0][2];

		cube[4][0][0] = cube[1][0][0];
		cube[4][0][1] = cube[1][0][1];
		cube[4][0][2] = cube[1][0][2];

		cube[1][0][0] = tempLine[0];
		cube[1][0][1] = tempLine[1];
		cube[1][0][2] = tempLine[2];
	}
	else if (order == "U-") { // 윗면을 반시계방향으로
		turnCubeFace(0, false);
		string tempLine[4] = { cube[2][0][0], cube[2][0][1], cube[2][0][2] };
		cube[2][0][0] = cube[1][0][0];
		cube[2][0][1] = cube[1][0][1];
		cube[2][0][2] = cube[1][0][2];

		cube[1][0][0] = cube[4][0][0];
		cube[1][0][1] = cube[4][0][1];
		cube[1][0][2] = cube[4][0][2];

		cube[4][0][0] = cube[3][0][0];
		cube[4][0][1] = cube[3][0][1];
		cube[4][0][2] = cube[3][0][2];

		cube[3][0][0] = tempLine[0];
		cube[3][0][1] = tempLine[1];
		cube[3][0][2] = tempLine[2];
	}
	else if (order == "L+") { // 왼쪽면 시계방향
		turnCubeFace(1, true);
		string tempLine[4] = { cube[5][0][0], cube[5][1][0], cube[5][2][0] };
		cube[5][0][0] = cube[2][0][0];
		cube[5][1][0] = cube[2][1][0];
		cube[5][2][0] = cube[2][2][0];

		cube[2][0][0] = cube[0][0][0];
		cube[2][1][0] = cube[0][1][0];
		cube[2][2][0] = cube[0][2][0];

		cube[0][0][0] = cube[4][2][2];
		cube[0][1][0] = cube[4][1][2];
		cube[0][2][0] = cube[4][0][2];

		cube[4][0][2] = tempLine[2];
		cube[4][1][2] = tempLine[1];
		cube[4][2][2] = tempLine[0];
	}
	else if (order == "L-") { // 왼쪽면 반시계방향
		turnCubeFace(1, false);

		string tempLine[4] = { cube[0][0][0], cube[0][1][0], cube[0][2][0] };
		cube[0][0][0] = cube[2][0][0];
		cube[0][1][0] = cube[2][1][0];
		cube[0][2][0] = cube[2][2][0];

		cube[2][0][0] = cube[5][0][0];
		cube[2][1][0] = cube[5][1][0];
		cube[2][2][0] = cube[5][2][0];

		cube[5][0][0] = cube[4][2][2];
		cube[5][1][0] = cube[4][1][2];
		cube[5][2][0] = cube[4][0][2];

		cube[4][0][2] = tempLine[2];
		cube[4][1][2] = tempLine[1];
		cube[4][2][2] = tempLine[0];
	}
	else if (order == "F+") {
		turnCubeFace(2, true);
		string tempLine[4] = { cube[3][0][0], cube[3][1][0], cube[3][2][0] };
		cube[3][0][0] = cube[0][2][0];
		cube[3][1][0] = cube[0][2][1];
		cube[3][2][0] = cube[0][2][2];

		cube[0][2][0] = cube[1][2][2];
		cube[0][2][1] = cube[1][1][2];
		cube[0][2][2] = cube[1][0][02];

		cube[1][0][2] = cube[5][0][0];
		cube[1][1][2] = cube[5][0][1];
		cube[1][2][2] = cube[5][0][2];

		cube[5][0][0] = tempLine[2];
		cube[5][0][1] = tempLine[1];
		cube[5][0][2] = tempLine[0];
	}
	else if (order == "F-") {
		turnCubeFace(2, false);
		string tempLine[4] = { cube[3][0][0], cube[3][1][0], cube[3][2][0] };

		cube[3][0][0] = cube[5][0][02];
		cube[3][1][0] = cube[5][0][1];
		cube[3][2][0] = cube[5][0][0];

		cube[5][0][0] = cube[1][0][2];
		cube[5][0][1] = cube[1][1][2];
		cube[5][0][2] = cube[1][2][2];

		cube[1][0][2] = cube[0][2][2];
		cube[1][1][2] = cube[0][2][1];
		cube[1][2][2] = cube[0][2][0];

		cube[0][2][0] = tempLine[0];
		cube[0][2][1] = tempLine[1];
		cube[0][2][2] = tempLine[2];
	}
	else if (order == "R+"){
		turnCubeFace(3, true);
		
		string tempLine[4] = { cube[0][0][2], cube[0][1][2], cube[0][2][2] };
		cube[0][0][2] = cube[2][0][2];
		cube[0][1][2] = cube[2][1][2];
		cube[0][2][2] = cube[2][2][2];

		cube[2][0][2] = cube[5][0][2];
		cube[2][1][2] = cube[5][1][2];
		cube[2][2][2] = cube[5][2][2];

		cube[5][0][2] = cube[4][2][0];
		cube[5][1][2] = cube[4][1][0];
		cube[5][2][2] = cube[4][0][0];

		cube[4][0][0] = tempLine[2];
		cube[4][1][0] = tempLine[1];
		cube[4][2][0] = tempLine[0];
	}
	else if (order == "R-") {
		turnCubeFace(3, false);

		string tempLine[4] = { cube[0][0][2], cube[0][1][2], cube[0][2][2] };
		cube[0][0][2] = cube[4][2][0];
		cube[0][1][2] = cube[4][1][0];
		cube[0][2][2] = cube[4][0][0];

		cube[4][0][0] = cube[5][2][2];
		cube[4][1][0] = cube[5][1][2];
		cube[4][2][0] = cube[5][0][2];

		cube[5][0][2] = cube[2][0][2];
		cube[5][1][2] = cube[2][1][2];
		cube[5][2][2] = cube[2][2][2];

		cube[2][0][2] = tempLine[0];
		cube[2][1][2] = tempLine[1];
		cube[2][2][2] = tempLine[2];
	}
	else if (order == "B+") {
		turnCubeFace(4, true);

		string tempLine[4] = { cube[0][0][0], cube[0][0][1], cube[0][0][2] };
		cube[0][0][0] = cube[3][0][2];
		cube[0][0][1] = cube[3][1][2];
		cube[0][0][2] = cube[3][2][2];

		cube[3][0][2] = cube[5][2][2];
		cube[3][1][2] = cube[5][2][1];
		cube[3][2][2] = cube[5][2][0];

		cube[5][2][0] = cube[1][0][0];
		cube[5][2][1] = cube[1][1][0];
		cube[5][2][0] = cube[1][2][0];

		cube[1][0][0] = tempLine[2];
		cube[1][1][0] = tempLine[1];
		cube[1][2][0] = tempLine[0];
	}
	else if (order == "B-") {
		turnCubeFace(4, false);

		string tempLine[4] = { cube[0][0][0], cube[0][0][1], cube[0][0][2] };
		cube[0][0][0] = cube[1][2][0];
		cube[0][0][1] = cube[1][1][0];
		cube[0][0][2] = cube[1][0][0];

		cube[1][0][0] = cube[5][2][0];
		cube[1][1][0] = cube[5][2][1];
		cube[1][2][0] = cube[5][2][2];

		cube[5][2][0] = cube[3][2][2];
		cube[5][2][1] = cube[3][1][2];
		cube[5][2][2] = cube[3][0][2];

		cube[3][0][2] = tempLine[0];
		cube[3][1][2] = tempLine[1];
		cube[3][2][2] = tempLine[2];
	}
	else if (order == "D+") {
		turnCubeFace(5, true);
		
		string tempLine[4] = { cube[4][2][0], cube[4][2][1], cube[4][2][2] };
		cube[4][2][0] = cube[3][2][0];
		cube[4][2][1] = cube[3][2][1];
		cube[4][2][2] = cube[3][2][2];

		cube[3][2][0] = cube[2][2][0];
		cube[3][2][1] = cube[2][2][1];
		cube[3][2][2] = cube[2][2][2];
		
		cube[2][2][0] = cube[1][2][0];
		cube[2][2][1] = cube[1][2][1];
		cube[2][2][2] = cube[1][2][2];

		cube[1][2][0] = tempLine[0];
		cube[1][2][1] = tempLine[1];
		cube[1][2][2] = tempLine[2];
	}
	else if (order == "D-") {
		turnCubeFace(5, false);

		string tempLine[4] = { cube[4][2][0], cube[4][2][1], cube[4][2][2] };
		cube[4][2][0] = cube[1][2][0];
		cube[4][2][1] = cube[1][2][1];
		cube[4][2][2] = cube[1][2][2];

		cube[1][2][0] = cube[2][2][0];
		cube[1][2][1] = cube[2][2][1];
		cube[1][2][2] = cube[2][2][2];

		cube[2][2][0] = cube[3][2][0];
		cube[2][2][1] = cube[3][2][1];
		cube[2][2][2] = cube[3][2][2];

		cube[3][2][0] = tempLine[0];
		cube[3][2][1] = tempLine[1];
		cube[3][2][2] = tempLine[2];
	}
}

void printCube(void) {
	cout << "큐브출력!\n";
	char face[7] = { 'U', 'L', 'F', 'R', 'B', 'D' };
	for (int i = 0; i < 6; i++) {
		cout << face[i] << "출력\n";
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++)
				cout << cube[i][j][k] << ' ';
			cout << '\n';
		}
	}
}

void printUpFace(void) {
	for (int j = 0; j < 3; j++){
		for (int k = 0; k < 3; k++)
			cout << cube[0][j][k];
		cout << '\n';
	}
}

void testSetCube(void) {
	char face[7] = { 'U', 'L', 'F', 'R', 'B', 'D' };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++) {
				cube[i][j][k].clear();
				cube[i][j][k].push_back(face[i]);
				cube[i][j][k].push_back('0' + (3 * j) + k);
			}
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	/*
	while(1){
	testSetCube();

	cin >> order;

	turnCube(order);

	printCube();
	}
	*/

	cin >> T;
	while (T--) {
		cin >> N;

		setCube();

		for (int i = 0; i < N; i++) {
			cin >> order;
			turnCube(order);
		}
		
		printUpFace();
	}

}
