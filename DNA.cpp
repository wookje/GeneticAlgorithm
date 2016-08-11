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
	//----김기현 작성----
	//for(int i = 0;i < gene.size();i++)
	//{
	//	여기서의 (%)는 데이터의 갯수를 의미
	//	상위 20%의 데이터를 쩨껴 놓았다는 것을 전제로 하고 사전에 적합도기준으로 sort 가 되어있다는것을 기준으로 작성
	//	ramdom(0~30%의 난수 생성)
	//	gene[i].angle과 angle의 평균값사이의 delta값이 random의 생성난수와 가장 가까운것을 찾음(적합도기준)
	//	gene[i].interval 또한 마찬가지
	//	random(0~50%의 난수 재생성)
	//	dna->gene[i].angle,dna->gene[i].interval 또한 마찬가지로 찾음
	//	찾는 기준은 sort되값이 기준
	//	즉, 100% 의 값중 20%는 교차범위에서 나가리이고, 50%의 평균에서 앞 30%,뒤 50%에서 교차를 하는데 
	//	정렬되어 있는(적합도 기준으로) 앞 30%에서 떨어져있는 정도로 for문을 돌며 찾고
	//	마찬가지로 뒤에서 있는 값또한 for문을 돌며 찾음
	//	그리고 찾은 dna의 주소를 각각 r_a,r_b라 하면,
	//	즉,gene[r_a].(각도,시간),dna->gene[r_b].(각도 시간)은 각각 찾은 바꿀 dna라는 뜻
	//	swap(gene[r_a],dna->gene[r_b])
	//	--------------------------------------------------------------------------
	//	로직만 작성했어요 
	//	아직 제가 전체를 모르고  실력도 많이 딸려서 코딩까지는 못하겠네요 
	//}
	}
	
	return dna;
}
