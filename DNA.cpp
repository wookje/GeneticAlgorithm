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
// 왜 ->를 붙이는 지는 아시죠? 포인터 변수니까요
// dna1은 그냥 전역변수로 선언 돼 있다고 생각하시면 되구요
// dna2는 인자로 넘어온 저 매개변수라고 생각하시면 됩니다
// 저기 위쪽에 보시면 SetData 함수에서 gene = dna->gene라고 되어있죠?
// dna1.gene = dna2.gene랑 같은 표현입니다 ㅇㅇ
// gene가 벡터로 선언되어 있습니다!
// gene가 바로 어떤 각도로 어느 길이로 갈지에 대한 정보의 집합이 순서대로 정렬되어 있는 벡터입니다
// 벡터는 다들 아시죠? 모르면 쳐보세요
// 님들은 dna1->gene[i]와 dna2->gene[j]를 알아서 적절히 교차하시면 됩니다
// 다시 말해서 gene[i]와 dna->gene[j]를 교차하라는 거죠
// i랑 j가 뭐가 될 지는 님들이 생각한 방식대로 구현하는 거고 ㅇㅇ
// 반복문 쓰고 싶으면 for (int i=0; i<dna->gene.length(); i++) 하시면 됩니다
// gene의 자료형이 Drive이고 위쪽에 Drive가 struct 대신 class로 정의되어 있습니다!
// 클래스나 구조체나 똑같은 거라고 생각하시면 됩니다
// 요약하자면 님들이 쓰면 되는 거는 gene.angle(각도)이랑 gene.interval(길이, 거리)입니다
// 하 졸라 친절하네
// 그럼 미래의 수학자 여러분들의 코딩력을 믿습니다!
// 화이팅!
DNA * DNA::CreateNextGene(DNA * dna)
{
	// 욱제의 로직!
	// gene.angle의 평균값과 gene.interval의 평균값을 각각 구함
	// for (int i=0; i<gene.length(); i++)
	//	random(0~100%중 하나) 수 생성
	//	gene[i].angle을 random% 만큼 평균값에 가까이 함
	//	random(0~100%중 하나) 수 생성
	//	gene[i].interval을 random% 만큼 평균값에 가까이 함
	//	dna->gene도 똑같이
	//	gene.length()와 dna->gene.length()의 평균(중간)값 구함
	// for (int i=0; i<중간값; i++)
	//	swap(gene[random1], dna->gene[random2])
	
	/*
	※ 정현 ※
	ex)
	a b c d e (5)
	e f g (3)
	위 두개의 데이터를 교차
	- 3 ~ 5 사이 랜덤값을 자식 염색체 길이로 설정
	- 각 유전자(a~g)가 선택될 확률은 50%
	- a -> e -> b -> f -> ... 순서대로 선택된 유전자를 자식 염색체에 저장
	- 0.1% 확률로 돌연변이 발생 ( 돌연변이 발생 시 각도와 시간을 랜덤값으로 재설정 )
	- 길이가 충족되면 리턴
	
	DNA *res = new DNA();
	int minsize = (len <= dna->len) ? len : dna->len;
	int maxsize = (len >= dna->len) ? len : dna->len;

	std::random_device rdt;
	std::mt19937 mtt(rdt());
	std::uniform_int_distribution<int> randlen(minsize, maxsize);
	std::uniform_int_distribution<int> randnum(1, 100);
	std::uniform_real_distribution<double> randangle(-40, 40);
	std::uniform_real_distribution<double> randinterval(0, 4);

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

	return res;
	*/
	
	return dna;
}
