#include "DNA.h"

void DNA::CreateRandomData(int size)
{
	int hi;
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

// 님들은 아래의 함수만 건드리시면 됩니다
// 교차할 dna가 함수의 인자로 넘어오게 됩니다
// DNA.h에 있는 모든 변수들을 여러분들이 사용하시면 되구요
// 우리가 교차해야할 dna1이랑 dna2가 있을 거 아닙니까?
// dna1은 그냥 len, time, gene.length(), ... 이런 식으로 쓰시면 되구요
// dna2는 앞에 dna 붙여서 dna->len, dna->time, dna->gene.length(), ... 이렇게 쓰시면 됩니다
// dna1은 그냥 전역변수로 선언 돼 있다고 생각하시면 되구요
// dna2는 인자로 넘어온 저 매개변수라고 생각하시면 됩니다
// 저기 위쪽에 보시면 SetData 함수에서 gene = dna->gene라고 되어있죠?
// dna1.gene = dna2.gene랑 같은 표현입니다 ㅇㅇ
// 하 졸라 친절하네
// 그럼 미래의 수학자 여러분들의 코딩력을 믿습니다!
// 화이팅!
DNA * DNA::CreateNextGene(DNA * dna)
{
	
	return dna;
}
