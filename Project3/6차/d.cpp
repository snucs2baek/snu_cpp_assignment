#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;
// vector max size를 넘는 수 미만의 소수를 구하기 위해 2차원 벡터 형태로 나타낸다.
//가로
const long long total_r = 1000'000;
//세로 (가로*세로 = 수)
const long long v_size = 1000'000;

long long front_front;
long long back_front;

vector <vector<bool>> All(total_r+1, vector <bool> (v_size+1));
// 앞에서부터 소수를 제거
void* thread_function_front(void* data) {
	vector <int> prime_front = *((vector <int>*)data);
	int front_front = prime_front[0];
	int front_back = prime_front[1];
	while(true) {
		All[front_front][front_back] = true;
		if (front_front>back_front){break;}
		front_front += prime_front[0];
		front_back += prime_front[1];
		front_front = front_front+front_back/v_size;
		front_back = front_back-v_size*(front_back/v_size);
	}
	return NULL;
}
//뒤에서부터 소수를 제거
void* thread_function_back(void* data) {
	vector <int> prime_back = *((vector <int>*)data);
	//주어진 수 미만의 소수의 최대 배수(시작점) 찾기
	long long back_front = ((v_size*total_r)-((v_size*total_r)%(prime_back[0]*v_size+prime_back[1])))/v_size;
	long long back_back = ((v_size*total_r)-((v_size*total_r)%(prime_back[0]*v_size+prime_back[1])))%v_size;
	while(front_front<back_front&back_front>0) {
		All[back_front][back_back] = true;
		back_front -= prime_back[0];
		back_back -= prime_back[1];
		back_front = back_front + back_back/v_size;
		back_back = back_back - v_size*(back_back/v_size);
		if (back_back < 0){
			back_front -= 1;
			back_back += v_size;
		}
	}
	return NULL;
}

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
	long long count = 0;
	All[0][0]=true;
	All[0][1]=true;
	for (int i = 0; i < total_r; i++) {
		for (int j = 0; j < v_size; j++){
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
