/*
    삼각형 꼭데기부터 바닥까지 이어지는 경로중 최대값 구하기

        7       ---- 1
       3 8      ---- 2
      8 1 0     ---- 3
     2 7 4 4    ---- 4
    4 5 2 6 5   ---- 5

    단, 아래로 이동할 경우, 현재 인덱스가 0일 경우 0또는 1로만 이동 가능합니다.
*/

/*
    1층부터 마지막층까지 생성 가능한 수 생성.
    생성된 층의 multimap에 입력 <index, value>
    (인덱스에 따라 다음 층의 값 생성 가능 하다)
    마지막 층에 최대값 리턴.

    //멀티맵을 사용하는 이유?
    //1. 맵 -> <index, value> 구조로 저장하기 위함. 다음 층에서 인덱스를 바탕으로 값 생성
    //2. 멀티 맵 -> index하나가 제시되념 index, index+1 두가지 경우가 생성된다.

    -> 예상대로 성능 똥망.
    다른 방법 사용할 것.
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

    //초기화
    for (size_t i = 0; i < numOfLayer; i++)
    {
        multimap<int, int> temp;
        pool.push_back(temp);
    }
    
    //꼭데기 값 삽입
    int index0 = 0;
    int layer0 = 0;
    pool[0].insert(make_pair(index0, tower[layer0][index0]));


    //삽입한 값을 바탕으로 새로운 값 생성
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

            //최대값 갱신
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