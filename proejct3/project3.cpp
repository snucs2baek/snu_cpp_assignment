/*
* @Author: 2018-13285 백우현
* @Date:   2021-09-24 03:25:34
* Brief: v.max_size 넘는 수를 저장하기 위해 2차원 벡터를 이용한다. 가로X세로가 찾고자 하는 수이다. 에라토스테네스의 체를 이용하되, 첫번째 쓰레드는 앞에서부터 소수의 배수를 지우고, 두번째 쓰레드는 끝에서부터 소수의 배수를 지운다.
* TODO: g++ -m64 a.out -lpthread로 64비트로 컴파일한다.
*/

#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

//가로x세로=찾고자 하는 수
const long long total_r = 1000'000;
//2차원 벡터의 행의 수
const long long v_size = 1000'000;
//2차원 벡터의 열의 수

long long front_front;
//첫번째 쓰레드가 지우고 있는 위치
long long back_front;
//두번째 쓰레드가 지우고 있는 위치
vector <vector<bool>> All(total_r+1, vector <bool> (v_size+1));
//소수는 false 배수는 true인 2차원 벡터

void* thread_function_front(void* data) {
	//쓰레드가 받는 현재 소수
	vector <int> prime_front = *((vector <int>*)data);
	int front_front = prime_front[0];
	//초기값 - 받은 소수의 행 위치
	int front_back = prime_front[1];
	//초기값 - 받은 소수의 열 위치
	//소수의 배수 지우기
	while(true) {
		All[front_front][front_back] = true;
		if (front_front>back_front){break;}
		//thread_fuction_back이 이미 지운 곳에 도달할 경우 종료
		front_front += prime_front[0];
		front_back += prime_front[1];
		//열 크기보다 넘어갈 경우 행 변환
		front_front = front_front+front_back/v_size;
		front_back = front_back-v_size*(front_back/v_size);
	}
	return NULL;
}

void* thread_function_back(void* data) {
	vector <int> prime_back = *((vector <int>*)data);
	//쓰레드가 받는 현재 소수
	//초기값 - 받은 소수의 주어진 수 미만의 최대 배수의 행, 열 위치
	long long back_front = ((v_size*total_r)-((v_size*total_r)%(prime_back[0]*v_size+prime_back[1])))/v_size;
	long long back_back = ((v_size*total_r)-((v_size*total_r)%(prime_back[0]*v_size+prime_back[1])))%v_size;
	//소수의 배수 지우기
	while(front_front<back_front&back_front>0) {
		//thread_fuction_front가 이미 지운 곳에 도달할 경우 종료
		All[back_front][back_back] = true;
		back_front -= prime_back[0];
		back_back -= prime_back[1];
		//열 크기보다 넘어가면 행 변환
		back_front = back_front + back_back/v_size;
		back_back = back_back - v_size*(back_back/v_size);
		if (back_back < 0){
			back_front -= 1;
			back_back += v_size;
		}
	}
	return NULL;
}
//소수를 받아 쓰레드를 만드는 함수
void make_thread(int front, int back){
	vector <int> trans;
	trans.push_back(front);
	trans.push_back(back);
	pthread_t pthread_id1;
	pthread_t pthread_id2;
	pthread_t t_front = pthread_create(
		&pthread_id1, NULL, thread_function_front, (void*)&trans
	);
	pthread_t t_back = pthread_create(
		&pthread_id2, NULL, thread_function_back, (void*)&trans
	);
	pthread_join(pthread_id1, NULL);
	pthread_join(pthread_id2, NULL);
}

int main() {
	time_t startTime = time(NULL);
	//소수의 개수를 저장
	long long count = 0;
	//0, 1은 미리 처리
	All[0][0]=true;
	All[0][1]=true;
	for (int i = 0; i < total_r; i++) {
		for (int j = 0; j < v_size; j++){
		//배수가 아니면 소수
			if (!All[i][j]) {
				count += 1;
				make_thread(i,j);
			}
		}
	}
	int numberOfPrime = count;
	cout << "number of prime" << numberOfPrime << endl;
	time_t endTime = time(NULL);
	double elapsedTime = (double)(endTime - startTime);
	cout << "execution time: " << elapsedTime << endl;
	return 0;
}