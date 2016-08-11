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
	
/*	int AVR_length = (gene.length()+dna->gene.length())/2;
	
	int RND_NUM_angle;
	int RND_NUM_interval;
	
	for(i=0;i<AVR_length;i++)
	{
		//gene[i].angle과 dna->gene[i].angle 사이의 난수 설정 (RND_NUM_angle)
		//(gene[i].angle+dna->gene[i].angle+RND_NUM_angle)/2를 교차값으로 설정
		//gene[i].interval과 dna->gene[i].interval 사이의 난수 설정 (RND_NUM_interval)
		//(gene[i].interval+dna->gene[i].interval+RND_NUM_interval)/2를 교차값으로 설정
	}
*/
	
	return dna;
}
