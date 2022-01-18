/*
	�ܼ� ī�޶�

	��ӵ��θ� �̿��ϴ� ��� ������ �ѹ��� ���� ī�޶� �ɸ����� �ϴ� �ּ� ��ġ Ƚ���� ���϶�

	[input]
	vector<vector<int>> routes : ������ ������ ��� ��ȣ

	[���� ����]
	routes.size : 1 ~ 10000	
	routes.value : -30000 ~ 30000
	������ ���� ���� �ɸ��� ������ ���ÿ� üũ �ߴٰ� �����Ѵ�.
	ex) 
		[-10 , -5], [-5, -3]
		-5 ������ ��ġ�� ��� �� ���� ��� üũ �� ��

*/

/*
	[solution]
	1. ������ ���� ����. �������� ���� -> list��� (�߰� ���� ����)
	
	2. ���� = ������ ���� (���� ���� ������ �� ���� -> ���ĵǾ� �ֱ� ������)
	3. (���� ���� < ���� ) �˻�
	4. �˻翡 �ɸ��� �� ����

	5. (2 ~ 4) ���� �ݺ�, �ݺ��� Ƚ�� ī��Ʈ
	6. ���� ī��Ʈ

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

	//list �ʱ�ȭ
	for (vector<vector<int>>::const_iterator it = routes.begin(); it != routes.end(); it++)
	{
		stCar car;
		car.start = it->at(0);
		car.end = it->at(1);
		cars.push_back(car);
	}

	//1. ������ ���� ���� �������� ���� -> ������ �����ε�(<)
	cars.sort();

	list<stCar>::iterator it = cars.begin();
	while(it != cars.end() )
	{
		//2. ������ = ������ ����
		int threshold = it->end;
		cars.erase(cars.begin());
		//3. ���� ���� < ������
		//������ �� �����̶� ���� ���� ���� ������ ����. ��ü ������ �˻� �ؾ��Ѵ�.
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
		//cars.remove_if();	���ٽ� ���� �˾ƵѰ�.
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