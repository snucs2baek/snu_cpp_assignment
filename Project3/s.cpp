#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;
vector<int> prime;

const int N = 50;
int* All = new int[N + 1]();
int back_now;
bool stop;

void* thread_function_front(void* data) {
	int prime_front = *((int*)data);
	for (int j = 1; j * prime_front <= back_now & j*prime_front<=N; j++) {
		All[j * prime_front] = 1;
	}
	stop = false;
	return NULL;
}

void* thread_function_back(void* data) {
	int prime_back = *((int*)data);
	int start=N-N% prime_back;
	for (int k = 0; stop; k++) {
		int l = start - k * prime_back;
		back_now = l;
		All[l] = 1;
	}
	return NULL;
}


int main() {
	double startTime = clock();
	for (int i = 2; i <= N; i++) {
	pthread_t pthread_id1;
	pthread_t pthread_id2;
		if (All[i] == 0) {
			prime.push_back(i);
			stop = true;
			back_now=N;
			pthread_t t_front = pthread_create(
				&pthread_id1, NULL, thread_function_front, (void*)&i
			);
			pthread_t t_back = pthread_create(
				&pthread_id2, NULL, thread_function_back, (void*)&i
			);
			cout << prime.back() << endl;
		}
	}
	int numberOfPrime = prime.size();
	cout << "number of prime" << numberOfPrime << endl;
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "execution time: " << elapsedTime << endl;
	return 0;
}