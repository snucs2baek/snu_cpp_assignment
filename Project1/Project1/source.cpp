/*
* @Author: 2018-13285 �����
* @Date:   2021-09-24 03:25:34
* Brief: �ռ����� �ּ� ���μ��� �ռ��� Ȥ�� �ּ� ���μ��� �Ҽ��� ������ ��Ÿ�� �� �ִٴ� ���� �̿��Ѵ�.
  10^9 ������ ��� ���� �ּ� ���μ��� ����, �� �� �ڱ� �ڽ��� �ּ� ���μ��� ���� ��(�Ҽ�)�� ã�´�.
* TODO: �ַ�� ������ Release��, �ַ�� �÷����� X64�� �����Ѵ�.
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
	// ã���� �ϴ� �Ҽ��� ����
	const int kMax = 1000'000'000;
	// �ڽ��� �ּ� ���μ��� ���� �迭, �ʱⰪ�� 0
	int* leastPrimeFactor = new int[kMax + 1]();
	// �Ҽ��� ���� ����
	vector<int> prime;
	for (int i = 2; i <= kMax; i++) {
		//�ռ����� �ƴ� ���
		if (leastPrimeFactor[i] == 0) {
			leastPrimeFactor[i] = i;
			prime.push_back(i);
		}
		//�ռ����� �����ϰ� �ּ� ���μ��� �Է�
		for (int j = 0; j < prime.size() && i * prime[j] <= kMax && prime[j] <= leastPrimeFactor[i]; j++) {
			leastPrimeFactor[i * prime[j]] = prime[j];
		}
	}
	//�Ҽ��� ����
	size_t numberOfPrime = prime.size();
	cout << "�Ҽ��� ����: " << numberOfPrime << endl;
	double endTime = clock();
	double elapsedTime = (double)(endTime - startTime);
	cout << "���α׷� ���� �ð�: " << elapsedTime << endl;
	return 0;
}
