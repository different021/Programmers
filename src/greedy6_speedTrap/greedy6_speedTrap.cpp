/*
	단속 카메라

	고속도로를 이용하는 모든 차량이 한번은 과속 카메라에 걸리도록 하는 최소 설치 횟수를 구하라

	[input]
	vector<vector<int>> routes : 차량의 입출입 통로 번호

	[제한 사항]
	routes.size : 1 ~ 10000	
	routes.value : -30000 ~ 30000
	입출입 지점 끝에 걸리는 차량은 동시에 체크 했다고 간주한다.
	ex) 
		[-10 , -5], [-5, -3]
		-5 지점에 설치할 경우 두 차량 모두 체크 한 것

*/

/*
	[solution]
	1. 나가는 영역 기준. 오름차순 정렬 -> list사용 (중간 제거 용이)
	
	2. 기준 = 나가는 영역 (가장 낮은 나가는 값 보증 -> 정렬되어 있기 때문에)
	3. (들어온 영역 < 기준 ) 검사
	4. 검사에 걸리는 값 제거

	5. (2 ~ 4) 과정 반복, 반복한 횟수 카운트
	6. 리턴 카운트

*/

/*
나가는 지점이 낮은 순으로 정렬되어 있다.
가장 앞의 값이 가장 먼저 나간다는 사실이 보장되어 있다.

s : 들어온 지점
e : 나가는 지점

s-----------e					0번 
			s-----e				1번
	s-----------------e			2번
			

0번 인덱스의 e값보다 낮은 s값은 모두 삭제.
이때, 정렬이 e값 기준으로 되어 있기 때문에 모든 s값을 검사 필요

삭제후 다시 진행 한다. 0번 인덱스 부터 다시 시작

방식 자체가 최소값을 보장한다.
== 반복한 횟수가 최소값
*/


#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct stCar
{
	int start = 0;
	int end = 0;

	bool operator < (stCar& car)
	{
		return (this->end < car.end);
	}
};

int solution(vector<vector<int>> routes) {
	int answer = 0;
	list<stCar> cars;

	//list 초기화
	for (vector<vector<int>>::const_iterator it = routes.begin(); it != routes.end(); it++)
	{
		stCar car;
		car.start = it->at(0);
		car.end = it->at(1);
		cars.push_back(car);
	}

	//1. 나가는 영역 기준 오름차순 정렬 -> 연산자 오버로딩(<)
	cars.sort();

	list<stCar>::iterator it = cars.begin();
	while(it != cars.end() )
	{
		//2. 기준점 = 나가는 영역
		int threshold = it->end;
		cars.erase(cars.begin());
		//3. 들어온 영역 < 기준점
		//나가는 값 기준이라 들어온 값에 대한 보증이 없다. 전체 영역을 검사 해야한다.
		list<stCar>::iterator innerIt = cars.begin();
		//for (list<stCar>::iterator innerIt = cars.begin(); innerIt != cars.end(); innerIt++)
		while(innerIt != cars.end())
		{
			if (innerIt->start <= threshold)
			{
				cars.erase(innerIt++);
			}
			else
				innerIt++;
		}
		//cars.remove_if();	람다식 사용법 알아둘것.
		it = cars.begin();
		answer++;
	}

	return answer;
}



int main()
{
	//2
	vector<vector<int>> routes = { {-20, -15},{-14, -5},{-18, -13},{-5, -3} };

	int result = solution(routes);

	printf("%d\n", result);

	return 0;
}