#ifndef __DNA_H__
#define __DNA_H__

#include <vector>
#include <random>
#include <time.h>

using namespace std;

class Drive
{
public:
	double angle;
	double interval;
	
	void CreateRandomGene() {
		std::random_device rdt;
		std::mt19937 mtt(rdt());
		std::uniform_real_distribution<double> randangle(-40, 40);
		std::uniform_real_distribution<double> randinterval(0, 10);

		angle = (double)randangle(mtt);
		interval = (double)randinterval(mtt);
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

	void CreateRandomData(int size);
	void SetData(DNA* dna);
	DNA* CreateNextGene(DNA* dna);
};

#endif