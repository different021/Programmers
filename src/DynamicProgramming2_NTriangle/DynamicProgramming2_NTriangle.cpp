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

//int solution(vector<vector<int>> triangle) {
//    int answer = 0;
//    vector<vector<int>>& tower = triangle;
//    size_t numOfLayer = tower.size();
//    vector<multimap<int, int>> pool;
//    pool.reserve(numOfLayer);
//
//    //�ʱ�ȭ
//    for (size_t floor = 0; floor < numOfLayer; floor++)
//    {
//        multimap<int, int> temp;
//        pool.push_back(temp);
//    }
//    
//    //������ �� ����
//    int index0 = 0;
//    int layer0 = 0;
//    pool[0].insert(make_pair(index0, tower[layer0][index0]));
//
//
//    //������ ���� �������� ���ο� �� ����
//    //int max = 0;
//    for (size_t layer = 1; layer < numOfLayer; layer++)
//    {
//        for (auto& it : pool[layer - 1])
//        {
//            int index = it.first;
//            int value = it.second;
//
//            int newValue1 = value + tower[layer][index];
//            pool[layer].insert(make_pair(index, newValue1));
//
//            int nextIndex = index + 1;
//            int newValue2 = value + tower[layer][nextIndex];
//            pool[layer].insert(make_pair(nextIndex, newValue2));
//
//        }
//    }
//
//    //�ִ밪 ã��
//    answer= max_element(pool[numOfLayer-1].begin(), pool[numOfLayer-1].end(), compareValue())->second;
//
//    return answer;
//}


/*
    [solution2]
    �� ���� �ִ� ���� ����.
    ���ο� ���� ������ (index), (index - 1) �� ���Ͽ� ū�� ����


                7(7)                ---- 1
            3(10) 8(15)             ---- 2
        8(18) 1(16) 0(15)           ---- 3
     2(20) 7(25) 4(20) 4(19)        ---- 4
    4(24) 5(30) 2(27) 6(26) 5(24)   ---- 5

    ��ȣ �ȿ����� ū��. ���� ���� ������ �ʿ����.

    �� ��ġ�� �� �� �ִ� �ִ� ���� ����.
    3���� �ε��� 1�� ������ ���� 1�̴�.
    ���� 10, 15 �� ū���� 15�� ���� 16�� �ȴ�.


    //�ڵ�
    R = result Vector
    T = triangle Vector

    f = floor
    i = index
    

    LOOP{
        index�� 0�� ���, R[f][0] = R[f-1][0]+ T[f][0];
        index�� f�� ���, R[f] = R[f-1][i] + T[i] 
        ������ ���,
            int big = max( R[f-1][i] , R[f-1][i-1] )    -> (i���� i-1�� �� ��, ū ��)
            int num = big + T[f][i]
            R[f][i] = num;
    }
    ���� maxFloor���� 

*/

int solution(vector<vector<int>> triangle)
{
    int answer = 0;
    vector<vector<int>> result = {};
    size_t maxFloor = triangle.size();      //�ִ� ����
    result.reserve(maxFloor);               

    //�ʱ�ȭ
    for (int i = 0; i < maxFloor; i++)
    {
        vector<int> temp;
        temp.reserve(i + 1);
        result.push_back(temp);
    }
    
    //0��
    result[0].push_back(triangle[0][0]);

    //1�� ����
    for (size_t floor = 1; floor < maxFloor; floor++)
    {
        for (size_t index = 0; index <= floor; index++)
        {
            if (index == 0)
            {
                //ù��° ���� ���� ���� ���� �� ���� �׳� �ִ´�.
                int num = result[floor - 1][index] + triangle[floor][index];
                result[floor].push_back(num);
            }
            else if (index == (floor))
            {
                //�ǳ����� ���ñ��� ����. 
                int num = result[floor - 1][index - 1] + triangle[floor][index];
                result[floor].push_back(num);
            }
            else
            {
                //�� ���� index -1, index �� ���� ���Ͽ� ū���� ���Ͽ� �߰��Ѵ�.
                int upFloor = floor - 1;
                int num2 = result[upFloor][index - 1];
                int num1 = result[upFloor][index];
                int big = (num1 > num2) ? num1 : num2;
                int num = big + triangle[floor][index];
                result[floor].push_back(num);
            }
        }
        
    }

    //�ִ밪 ã��
    answer = *max_element(result[maxFloor - 1].begin(), result[maxFloor - 1].end());

    return answer;
}


int main()
{
    //return 30
    vector<vector<int>> triangle = { {7}, { 3, 8 }, { 8, 1, 0 }, { 2, 7, 4, 4 }, { 4, 5, 2, 6, 5 }};
    //vector<vector<int>> triangle = { {7}, { 3, 8 }, { 8, 1, 0 }, { 2, 7, 4, 4 }, { 4, 5, 2, 6, 5 }, { 1, 1, 1, 1, 1, 1 } };
    int result = solution(triangle);

    printf("%d\n", result);

    return 0;
}