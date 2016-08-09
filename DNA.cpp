#include "DNA.h"

void DNA::CreateRandomData(int size)
{
	std::random_device rdt;
	std::mt19937 mtt(rdt());
	std::uniform_int_distribution<int> randlen(1, size);
	
	len = randlen(mtt);

	for (int i = 1; i <= len; ++i) {
		Drive* tmp = new Drive();
		tmp->CreateRandomGene();
		gene.push_back(*tmp);
	}
}

void DNA::SetData(DNA * dna)
{
	gene = dna->gene;
	len = dna->len;
}

DNA * DNA::CreateNextGene(DNA * dna)
{
	
	return dna;
}
