/*
* @Author: 2018-13285 백우현
* @Date:   2021-10-15 23:21:34
* Brief: 11X11의 체스판에 놓을 수 있는 11개의 퀸의 첫번째 조합을 찾는다. DFS를 사용한다.
         결과값은 각 행의 퀸이 놓여져있는 열의 위치를 출력함으로써 보인다.
*/

#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
// 한 행에서 시작 열부터 끝 열까지 가능한 첫번째의 위치를 찾는 함수.
//입력값은 시작열과 퀸의 위치.
int check(int start, vector<int> point) {
	for (int i = start; i < 11; i++) {
		//금지된 열인지 확인. 허용된 열이라 가정.
		bool forbidden = false;
		for (int j = 0; j < point.size(); j++) {
			//한 퀸에 의해 금지됐으면 다른 퀸에 의해 금지되는지는 확인하지 않음.
			if (forbidden == true) {
				break;
			}//퀸으로부터 대각선과 직선에 위치하는지 확인.
			if (i == point[j] || i == (point[j] + point.size() - j) || i == (point[j] - point.size() + j)) {
				forbidden = true;
			}
		}
		//금지되지 않은 첫번째 위치를 반환.
		if (forbidden == true) {
			continue;
		}
		return i;
	}//전부 금지됐으면 도달할 수 없는 열 번호인 11을 반환. 
	return 11;
}

//재귀를 이용해 한줄씩 차례로 퀸의 위치를 찾는 함수.
//입력값은 시작열과 퀸의 위치.
void dfs(vector<int> point, int start) {
	//11번째 행까지 모두 채워질때까지 실행
	if (point.size() != 11) {
		//가능한 열.
		int check_result = check(start, point);
		//가능한 열이 없을 경우.
		if (check_result == 11) {
			//바로 위의 행의 퀸의 위치를 저장.
			int back = point.back();
			//바로 위의 행의 퀸을 제거.
			point.pop_back();
			//원래 있던 자리보다 오른쪽 자리를 시작열로 하고 재귀.
			dfs(point, back + 1);
			return;
		}
		//가능한 열이 있으면 그 열에 퀸을 위치.
		point.push_back(check_result);
		//그 아래 행을 첫번째 열부터 찾는다.
		dfs(point, 0);
		return;
	}
	//모두 채워졌을 경우. 그 위치를 출력.
	if (point.size() == 11) {
		for (int i = 0; i < 11; i++) {
			cout << point[i] << "/";
		}
	}
	return;
}


int main() {
	double startTime = clock();
	//퀸이 놓여지지 않았을 때, 첫번째 행과 열에서부터 시작
	vector<int> point;
	dfs(point,0);
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "time: " << elapsedTime << endl;
	return 0;
}
