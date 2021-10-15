/*
* @Author: 2018-13285 백우현
* @Date:   2021-09-24 03:25:34
* Brief: 합성수는 최소 소인수와 합성수 혹은 최소 소인수와 소수의 곱으로 나타낼 수 있다는 것을 이용한다.
  10^9 이하의 모든 수의 최소 소인수를 구해, 그 중 자기 자신을 최소 소인수로 갖는 수(소수)를 찾는다.
* TODO: 솔루션 구성을 Release로, 솔루션 플랫폼을 X64로 설정한다.
* Reference :
	1.<Linear-sieve>, 2020.02.25.,<https://ahgus89.github.io/algorithm/Linear-sieve/>, 2021.09.24.
	2.<Sieve of Eratosthenes Having Linear Time Complexity>,
	<https://cp-algorithms.com/algebra/prime-sieve-linear.html>, 2021.09.24.
*/


#include "std_lib_facilities.h"
#include <time.h>
#include <vector>


int main() {
	double startTime = clock();
	// 찾고자 하는 소수의 상한
	const int kMax = 1000'000'000;
	// 자신의 최소 소인수를 담을 배열, 초기값은 0
	int* leastPrimeFactor = new int[kMax + 1]();
	// 소수를 담을 벡터
	vector<int> prime;
	for (int i = 2; i <= kMax; i++) {
		//합성수가 아닐 경우
		if (leastPrimeFactor[i] == 0) {
			leastPrimeFactor[i] = i;
			prime.push_back(i);
		}
		//합성수를 생성하고 최소 소인수를 입력
		for (int j = 0; j < prime.size() && i * prime[j] <= kMax && prime[j] <= leastPrimeFactor[i]; j++) {
			leastPrimeFactor[i * prime[j]] = prime[j];
		}
	}
	//소수의 개수
	size_t numberOfPrime = prime.size();
	cout << "소수의 개수: " << numberOfPrime << endl;
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "프로그램 수행 시간: " << elapsedTime << endl;
	return 0;
}
