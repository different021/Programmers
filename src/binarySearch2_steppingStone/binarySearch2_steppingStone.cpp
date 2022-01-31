/*
    [징검다리] 
    vector<int> 형태로 주어진 징검다리 배열이 있다.
    이 중, n개의 값을 제거한다.
    이때, 징검다리 사리의 거리의 최소값을 최대로 만들어 리턴하라.

    [제한]
    distance   : 1 ~ 1000000000
    rocks.size : 1 ~ 50000
    n : 1 ~ rocks.size

    [제시된 설명]
    제거한 바위의 위치	각 바위 사이의 거리	거리의 최솟값
    [21, 17]	        [2, 9, 3, 11]	        2
    [2, 21]	            [11, 3, 3, 8]	        3
    [2, 11]	            [14, 3, 4, 4]	        3
    [11, 21]	        [2, 12, 3, 8]	        2
    [2, 14]	            [11, 6, 4, 4]	        4

    생성된 최소값 중 최대값 4.
    
*/

/*
    [solution]
    0. 구조체 정의 
        int rock (key)
        int prvRock (이전 키값)
        int nextRock (다음 키값)
        int prvDist    (거리)
        int nextDist
          
            prevDist     nextDist
        prvRock       rock       nextRock
                      (key)
        해당 돌의 값과, 앞뒤 거리 저장.
        메모리 사용 : rocks.size * sizeof(int) * 5
    
    1. 바위 오름차순 정렬 후, 새로운 구조체에 정렬

    2. prvDist 기준, 오름 차순 정렬
        거리가 같으면, nextDist 로 정렬
    
    3. 가장 앞의 값 제거. (0과 distance 값 제외)
      단, 제거풀에 해당 인덱스가 포함되어있는지 검사한 후.
      제거풀에 존재할 경우 다음 인덱스로 이동. dist다시 계산. 
      -> 인설트 소팅
    
    4. 반복 제거 회수 만큼 반복      

*/



#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define NOT_INITIALIZE -1

using namespace std;


struct stRock
{
    int key     = NOT_INITIALIZE;
    int prevKey = NOT_INITIALIZE;
    int nextKey = NOT_INITIALIZE;
    int prevDist= NOT_INITIALIZE;
    int nextDist= NOT_INITIALIZE;
};

//rock
bool rockSetKey(stRock& pDest, int index);
bool rockSetPrevIndex(stRock& pDest, int index);
bool rockSetNextIndex(stRock& pDest, int index);
bool rockSetPrevDist(stRock& pDest);
bool rockSetNextDist(stRock& pDest);


//rockManager
bool rockManagerInitialize(stRock* &pOut, vector<int>& src, int distance);
bool rockManagerSortByPrevDist(stRock& r1, stRock& r2);
int  rockManagerFind(stRock* pRocks, int key, int dist);    //dist는 빨리 찾기 위해
int  rockManagerDelete(stRock* pRocks, int index);

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    map<int, stRock> deletePool;
    size_t numOfRock = rocks.size();
    int numOfDel = n;
    int end = distance;
    int start = 0;
    stRock* pRocks = nullptr;

    //바위 오름차순 정렬.
    sort(rocks.begin(), rocks.end());

    //새 데이터 초기화
    rockManagerInitialize(pRocks, rocks, distance);
    
    //prevDist 기준 정렬
    sort(pRocks, pRocks + numOfRock, rockManagerSortByPrevDist);

    //첫번째 요소 삭제.
    //1. 삭제 풀에 넣는다.
    //2. prevIndex 수정
    
    //3. nextIndex 수정
    deletePool.insert( make_pair(pRocks[0].key, pRocks[0]) );

    int prevIndex = pRocks[0].prevKey;
    int prevDist = pRocks[0].prevKey;

    int nextIndex = pRocks[0].nextKey;
    int nextDist = pRocks[0].nextDist;



    int a = 0;

    return answer;
}

bool rockSetKey(stRock& pDest, int index)
{
    bool bResult = false;
    pDest.key = index;
    
    bResult = true;
    return bResult;
}

bool rockSetPrevIndex(stRock& pDest, int index)
{
    bool bResult = false;
    if (pDest.key == NOT_INITIALIZE) goto lb_return;
    if (index > pDest.key) goto lb_return;
    pDest.prevKey = index;
    
    bResult = true;
lb_return:
    return bResult;
}

bool rockSetNextIndex(stRock& pDest, int index)
{
    bool bResult = false;
    if (pDest.key == NOT_INITIALIZE) goto lb_return;
    if (index < pDest.key) goto lb_return;
    pDest.nextKey = index;

    bResult = true;
lb_return:
    return bResult;
}

bool rockSetPrevDist(stRock& pDest)
{
    bool bResult = false;
    stRock& pRock = pDest;
    if (pDest.key == NOT_INITIALIZE) goto lb_return;
    if (pDest.prevKey == NOT_INITIALIZE) goto lb_return;
    
    pRock.prevDist = pRock.key - pRock.prevKey;

    bResult = true;
lb_return:
    return bResult;
}

bool rockSetNextDist(stRock& pDest)
{
    bool bResult = false;
    stRock& pRock = pDest;
    if (pDest.key == NOT_INITIALIZE) goto lb_return;
    if (pDest.nextKey == NOT_INITIALIZE) goto lb_return;

    pRock.nextDist = pRock.nextKey - pRock.key;

    bResult = true;
lb_return:
    return bResult;
}

bool rockManagerInitialize(stRock*& pOut, vector<int>& src, int distance)
{
    bool bResult = false;
    size_t size = src.size();
    int start = 0;
    int end = distance;
    if (size == 0) goto lb_return;
    if (pOut != nullptr)
    {
        delete[] pOut;
        pOut = nullptr;
    }
    
    pOut = new stRock[size];

    for (size_t i = 0; i < size; i++)
    {
        int index = src.at(i);
        int prvIndex = start;
        int nextIndex = end;

        rockSetKey(pOut[i], index);

        if (i != 0) prvIndex = src.at(i - 1);
        if (i != size - 1) nextIndex = src.at(i + 1);

        rockSetPrevIndex(pOut[i], prvIndex);
        rockSetNextIndex(pOut[i], nextIndex);

        rockSetPrevDist(pOut[i]);
        rockSetNextDist(pOut[i]);
    }

    bResult = true;

lb_return:
    return bResult;
}

bool rockManagerSortByPrevDist(stRock& r1, stRock& r2)
{
    bool bResult = false;
    if (r1.prevDist < r2.prevDist)
    {
        bResult = true;
    }
    else if (r1.prevDist == r2.prevDist)
    {
        if (r1.nextDist < r2.nextDist) bResult = true;
    }

    return bResult;
}



int main()
{
    //return 4;
    int distance = 25;
    vector<int> rocks = { 2, 14, 11, 21, 17 };
    int n = 2;

    int result = solution(distance, rocks, n);

    printf("%d\n", result);

    return 0;
}