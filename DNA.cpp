#include "DNA.h"

void DNA::CreateRandomData(int size)
{
	std::random_device rdt;
	std::mt19937 mtt(rdt());
	
	len = size;

	for (int i = 1; i <= len; i++) {
		Drive* tmp = new Drive();
		tmp->CreateRandomGene();
		gene.push_back(*tmp);
	}
}

void DNA::SetData(DNA * dna)
{
	gene = dna->gene;
	len = dna->len;
	isMutate = dna->isMutate;
}

DNA * DNA::CreateNextGene(DNA * dna)
{
	DNA *res = new DNA();
	DNA *tmp1 = (fit > dna->fit) ? this : dna;
	DNA *tmp2 = (fit <= dna->fit) ? dna : this;

	std::random_device rdt;
	std::mt19937 mtt(rdt());
	std::uniform_int_distribution<int> randnum(0, tmp1->now);
	std::uniform_real_distribution<double> randangle(-MAX_ANGLE, MAX_ANGLE);
	std::uniform_real_distribution<double> randinterval(1, MAX_INTERVAL);

	res->len = tmp1->len;
	int flag = randnum(mtt);

	for (int i = 0; i < flag; i++) {
		Drive tmp = tmp1->gene[i];
		if (isMutation()) {
			tmp.angle = randangle(mtt);
			res->isMutate = true;
		}
		if (isMutation()) {
			tmp.interval = randinterval(mtt);
			res->isMutate = true;
		}
		tmp.reviseData();
		res->gene.push_back(tmp);
	}
	for (int i = flag; i < len; i++) {
		Drive tmp = tmp2->gene[i];
		if (isMutation()) {
			tmp.angle = randangle(mtt);
			res->isMutate = true;
		}
		if (isMutation()) {
			tmp.interval = randinterval(mtt);
			res->isMutate = true;
		}
		tmp.reviseData();
		res->gene.push_back(tmp);
	}
	
	return res;







	/*DNA *res = new DNA();
	int minsize = (len <= dna->len) ? len : dna->len;
	int maxsize = (len >= dna->len) ? len : dna->len;

	std::random_device rdt;
	std::mt19937 mtt(rdt());
	std::uniform_int_distribution<int> randlen(minsize, maxsize);
	std::uniform_int_distribution<int> randnum(1, 100);
	std::uniform_real_distribution<double> randangle(-MAX_ANGLE, MAX_ANGLE);
	std::uniform_real_distribution<double> randinterval(0, MAX_INTERVAL);

	res->len = randlen(mtt);
	if (isMutation()) res->len += 2;
	if (res->len > maxsize) res->len = maxsize;

	for (int i = 0, j = 0,l1,l2, check = 1;;) {
		int tmp = randnum(mtt);
		int cangle = (randnum(mtt) <= 50) ? 1 : -1;
		int cinterval = (randnum(mtt) <= 50) ? 1 : -1;
		int p = (check == 1) ? i : j;
		int length = (check == 1) ? len : dna->len;
		
		(len >= i) ? l1 = len - i : l1 = 0;
		(dna->len >= j) ? l2 = dna->len - j : l2 = 0;

		if (l1 + l2 == res->len - res->gene.size()) {
			for (int k = i, l = j;;) {
				if (k >= len && l >= dna->len) break;
				if (k < len) {
					if (isMutation()) gene[k].angle = randangle(mtt);
					if (isMutation()) gene[k].interval = randinterval(mtt);
					gene[k].reviseData();
					res->gene.push_back(gene[k++]);
				}
				if (l < dna->len) {
					if (isMutation()) dna->gene[l].angle = randangle(mtt);
					if (isMutation()) dna->gene[l].interval = randinterval(mtt);
					dna->gene[l].reviseData();
					res->gene.push_back(dna->gene[l++]);
				}
			}
		}
		if (res->len == res->gene.size()) break;
		if (tmp <= 50 && p < length) {
			Drive ttmp = (check == 1) ? gene[p] : dna->gene[p];
			if (isMutation()) ttmp.angle = randangle(mtt);
			if (isMutation()) ttmp.interval = randinterval(mtt);
			ttmp.reviseData();
			res->gene.push_back(ttmp);
		}
		(check == 1) ? i++ : j++;
		check *= -1;
		if (res->len == res->gene.size()) break;
	}

	return res;*/
}
