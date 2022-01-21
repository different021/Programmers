/*
    �ﰢ�� ��������� �ٴڱ��� �̾����� ����� �ִ밪 ���ϱ�

        7       ---- 1
       3 8      ---- 2
      8 1 0     ---- 3
     2 7 4 4    ---- 4
    4 5 2 6 5   ---- 5

    ��, �Ʒ��� �̵��� ���, ���� �ε����� 0�� ��� 0�Ǵ� 1�θ� �̵� �����մϴ�.
*/

/*
    1������ ������������ ���� ������ �� ����.
    ������ ���� multimap�� �Է� <index, value>
    (�ε����� ���� ���� ���� �� ���� ���� �ϴ�)
    ������ ���� �ִ밪 ����.

    //��Ƽ���� ����ϴ� ����?
    //1. �� -> <index, value> ������ �����ϱ� ����. ���� ������ �ε����� �������� �� ����
    //2. ��Ƽ �� -> index�ϳ��� ���õǳ� index, index+1 �ΰ��� ��찡 �����ȴ�.

    -> ������ ���� �˸�.
    �ٸ� ��� ����� ��.
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct compareValue
{
    template <typename T>
    bool operator()(const T& pLhs, const T& pRhs)
    {
        return pLhs.second < pRhs.second;
    }
};

#define MAX_LAYER 500;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    vector<vector<int>>& tower = triangle;
    size_t numOfLayer = tower.size();
    vector<multimap<int, int>> pool;
    pool.reserve(numOfLayer);

    //�ʱ�ȭ
    for (size_t i = 0; i < numOfLayer; i++)
    {
        multimap<int, int> temp;
        pool.push_back(temp);
    }
    
    //������ �� ����
    int index0 = 0;
    int layer0 = 0;
    pool[0].insert(make_pair(index0, tower[layer0][index0]));


    //������ ���� �������� ���ο� �� ����
    //int max = 0;
    for (size_t layer = 1; layer < numOfLayer; layer++)
    {
        for (auto& it : pool[layer - 1])
        {
            int index = it.first;
            int value = it.second;

            int newValue1 = value + tower[layer][index];
            pool[layer].insert(make_pair(index, newValue1));

            int nextIndex = index + 1;
            int newValue2 = value + tower[layer][nextIndex];
            pool[layer].insert(make_pair(nextIndex, newValue2));

            //�ִ밪 ����
            //max = (max > newValue1) ? max : newValue1;
            //max = (max > newValue2) ? max : newValue2;
        }
    }

    int max = max_element(pool[numOfLayer-1].begin(), pool[numOfLayer-1].end(), compareValue())->second;
    answer = max;

    return answer;
}



int main()
{
    //return 30
    vector<vector<int>> triangle = { {7}, { 3, 8 }, { 8, 1, 0 }, { 2, 7, 4, 4 }, { 4, 5, 2, 6, 5 }};
    int result = solution(triangle);

    printf("%d\n", result);

    return 0;
}