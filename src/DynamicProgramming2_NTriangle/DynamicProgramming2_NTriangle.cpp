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

//int solution(vector<vector<int>> triangle) {
//    int answer = 0;
//    vector<vector<int>>& tower = triangle;
//    size_t numOfLayer = tower.size();
//    vector<multimap<int, int>> pool;
//    pool.reserve(numOfLayer);
//
//    //초기화
//    for (size_t floor = 0; floor < numOfLayer; floor++)
//    {
//        multimap<int, int> temp;
//        pool.push_back(temp);
//    }
//    
//    //꼭데기 값 삽입
//    int index0 = 0;
//    int layer0 = 0;
//    pool[0].insert(make_pair(index0, tower[layer0][index0]));
//
//
//    //삽입한 값을 바탕으로 새로운 값 생성
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
//    //최대값 찾기
//    answer= max_element(pool[numOfLayer-1].begin(), pool[numOfLayer-1].end(), compareValue())->second;
//
//    return answer;
//}


/*
    [solution2]
    각 층별 최대 값을 저장.
    새로운 층은 위층의 (index), (index - 1) 을 비교하여 큰값 선택


                7(7)                ---- 1
            3(10) 8(15)             ---- 2
        8(18) 1(16) 0(15)           ---- 3
     2(20) 7(25) 4(20) 4(19)        ---- 4
    4(24) 5(30) 2(27) 6(26) 5(24)   ---- 5

    괄호 안에값이 큰값. 본래 수는 저장할 필요없다.

    각 위치별 올 수 있는 최대 값을 저장.
    3층의 인덱스 1인 지점은 값이 1이다.
    위층 10, 15 중 큰값인 15를 더해 16이 된다.


    //코드
    R = result Vector
    T = triangle Vector

    f = floor
    i = index
    

    LOOP{
        index가 0일 경우, R[f][0] = R[f-1][0]+ T[f][0];
        index가 f일 경우, R[f] = R[f-1][i] + T[i] 
        나머지 경우,
            int big = max( R[f-1][i] , R[f-1][i-1] )    -> (i번과 i-1번 비교 후, 큰 값)
            int num = big + T[f][i]
            R[f][i] = num;
    }
    루프 maxFloor까지 

*/

int solution(vector<vector<int>> triangle)
{
    int answer = 0;
    vector<vector<int>> result = {};
    size_t maxFloor = triangle.size();      //최대 층수
    result.reserve(maxFloor);               

    //초기화
    for (int i = 0; i < maxFloor; i++)
    {
        vector<int> temp;
        temp.reserve(i + 1);
        result.push_back(temp);
    }
    
    //0층
    result[0].push_back(triangle[0][0]);

    //1층 부터
    for (size_t floor = 1; floor < maxFloor; floor++)
    {
        for (size_t index = 0; index <= floor; index++)
        {
            if (index == 0)
            {
                //첫번째 값은 앞의 값과 비교할 수 없어 그냥 넣는다.
                int num = result[floor - 1][index] + triangle[floor][index];
                result[floor].push_back(num);
            }
            else if (index == (floor))
            {
                //맨끝값은 선택권이 없다. 
                int num = result[floor - 1][index - 1] + triangle[floor][index];
                result[floor].push_back(num);
            }
            else
            {
                //위 층의 index -1, index 두 값을 비교하여 큰값과 더하여 추가한다.
                int upFloor = floor - 1;
                int num2 = result[upFloor][index - 1];
                int num1 = result[upFloor][index];
                int big = (num1 > num2) ? num1 : num2;
                int num = big + triangle[floor][index];
                result[floor].push_back(num);
            }
        }
        
    }

    //최대값 찾기
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