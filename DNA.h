#ifndef __DNA_H__
#define __DNA_H__

#include <vector>
#include <random>
#include <time.h>

#define MUTATION 100
#define REVISEDATA 1000
#define MAX_ANGLE 40.0f
#define MAX_INTERVAL 4.0f

using namespace std;

class Drive
{
public:
	double angle;
	double interval;
	
	void CreateRandomGene() {
		std::random_device rdt;
		std::mt19937 mtt(rdt());
		std::uniform_real_distribution<double> randangle(-MAX_ANGLE, MAX_ANGLE);
		std::uniform_real_distribution<double> randinterval(0, MAX_INTERVAL);

		angle = (double)randangle(mtt);
		interval = (double)randinterval(mtt);
	}

	void reviseData() {
		if (angle < -MAX_ANGLE || angle>MAX_ANGLE) angle = (angle > MAX_ANGLE) ? MAX_ANGLE : -MAX_ANGLE;
		if (interval<0.0f || interval>MAX_INTERVAL) interval = (interval < MAX_INTERVAL) ? MAX_INTERVAL : MAX_INTERVAL;
	}
};

class DNA
{
public:
	DNA() {};
	~DNA() {};
	vector<Drive> gene;
	int len = 0;
	clock_t start = 0, end = 0;
	double time = 0.0f;
	double fit = 0.0f;
	int now = 0;
	bool isStart = false;
	bool isMutate = false;

	void CreateRandomData(int size);
	void SetData(DNA* dna);
	DNA* CreateNextGene(DNA* dna);

	double getChance() {
		std::random_device rdt;
		std::mt19937 mtt(rdt());
		std::uniform_int_distribution<int> randmutation(0, MUTATION * REVISEDATA);
		int tmp = randmutation(mtt);
		int res = 0;
		for (int i = 1, sum = 0; i <= 100; i++) {
			sum += i*REVISEDATA;
			if (tmp <= sum) res = i;
		}
		return res;
	}

	bool isMutation() {
		std::random_device rdt;
		std::mt19937 mtt(rdt()); 
		std::uniform_int_distribution<int> randmutation(0, MUTATION * REVISEDATA);
		int tmp = randmutation(mtt);
		return tmp <= REVISEDATA;
	}
};

#endif
