/*
    [¡�˴ٸ�] 
    vector<int> ���·� �־��� ¡�˴ٸ� �迭�� �ִ�.
    �� ��, n���� ���� �����Ѵ�.
    �̶�, ¡�˴ٸ� ������ �Ÿ��� �ּҰ��� �ִ�� ����� �����϶�.

    [����]
    distance   : 1 ~ 1000000000
    rocks.size : 1 ~ 50000
    n : 1 ~ rocks.size

    [���õ� ����]
    ������ ������ ��ġ	�� ���� ������ �Ÿ�	�Ÿ��� �ּڰ�
    [21, 17]	        [2, 9, 3, 11]	        2
    [2, 21]	            [11, 3, 3, 8]	        3
    [2, 11]	            [14, 3, 4, 4]	        3
    [11, 21]	        [2, 12, 3, 8]	        2
    [2, 14]	            [11, 6, 4, 4]	        4

    ������ �ּҰ� �� �ִ밪 4.
    
*/

/*
    [solution]
    0. ����ü ���� 
        int prvRock  (�� Ű��)
        int nextRock (�� Ű��)
        int dist     (next - prev)
        
          
               prevDist     
        prvRock       nextRock
                      
        �ش� ���� ����, �յ� �Ÿ� ����.
        �޸� ��� : rocks.size * sizeof(int) * 3
    
    1. ���� �������� ���� ��, ���ο� ����ü�� ����

    2. dist ����, ���� ���� ����
        �Ÿ��� ������, prevKey �� ����
    
    3. �Ÿ��� ���� ª�� �� ���� (0�� �ε���)
     -prevKey nextKey
     -nextKey�� ���

    4. nextKey���� prevKey�� ���� ã�´�.
    5. 0�� �ε����� nextKey�� ��� ã�� ���� nextKey�� ����
    7. �Ʊ� ã�� ��ġ �� ���� (��ü ������ 1 ����)
    6. dist �ٽ� ���
    7. insert sorting
    


    ���� ���� �� ����. (0�� distance �� ����)
      ��, ����Ǯ�� �ش� �ε����� ���ԵǾ��ִ��� �˻��� ��.
      ����Ǯ�� ������ ��� ���� �ε����� �̵�. dist�ٽ� ���. 
      -> �μ�Ʈ ����
    
    4. �ݺ� ���� ȸ�� ��ŭ �ݺ�      

*/



#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define NOT_INITIALIZE -1

using namespace std;


struct stRock
{
    //int key     = NOT_INITIALIZE;
    int prevKey = NOT_INITIALIZE;
    int nextKey = NOT_INITIALIZE;
    int dist    = NOT_INITIALIZE;
    //int nextDist= NOT_INITIALIZE;

    bool operator== (const stRock& r1)
    {
        bool bResult = false;
        if (this->dist == r1.dist)
        {
            if (this->prevKey == r1.prevKey)
            {
                bResult = true;
            }
        }

        return bResult;
    }
};

//rock
bool rockSetPrevIndex(stRock& pDest, int index);
bool rockSetNextIndex(stRock& pDest, int index);
bool rockSetDist(stRock& pDest);


//rockManager
bool rockManagerInitialize(stRock* &pOut, vector<int>& src, int distance);
bool rockManagerSortByPrevDist(stRock& r1, stRock& r2);
int  rockManagerFind(stRock* pRocks, int key, int dist);    //dist�� ���� ã�� ����
int  rockManagerDelete(stRock* pRocks, int index);

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    map<int, stRock> deletePool;
    size_t numOfRock = rocks.size();
    int numOfDel = n;
    int end = distance;
    int start = 0;
    stRock* pRocks = nullptr;

    //���� �������� ����.
    sort(rocks.begin(), rocks.end());

    //�� ������ �ʱ�ȭ
    rockManagerInitialize(pRocks, rocks, distance);
    
    //prevDist ���� ����
    sort(pRocks, pRocks + numOfRock, rockManagerSortByPrevDist);
    
    deletePool.insert( make_pair(pRocks[0].prevKey, pRocks[0]) );

    //delete
    int prevIndex = pRocks[0].prevKey;
    int nextIndex = pRocks[0].nextKey;
    int dist = nextIndex - prevIndex;

    auto it = find(rocks.begin(), rocks.end(), nextIndex);
    int newPrev = *it;
    it++;
    int newNext = *it;
    
    stRock temp;
    temp.dist = newNext - newPrev;
    temp.prevKey = newPrev;
    auto target = find(pRocks, pRocks + numOfRock, temp);


    //rockManagerFind(pRocks, nextIndex, *it - nextIndex );
    //int nextDist = pRocks[0].nextDist;

    int a = 0;

    return answer;
}


bool rockSetPrevIndex(stRock& pDest, int index)
{
    bool bResult = false;
    /*if (pDest.key == NOT_INITIALIZE) goto lb_return;
    if (index > pDest.key) goto lb_return;*/
    pDest.prevKey = index;
    
    bResult = true;
lb_return:
    return bResult;
}

bool rockSetNextIndex(stRock& pDest, int index)
{
    bool bResult = false;
    
    pDest.nextKey = index;

    bResult = true;
lb_return:
    return bResult;
}

bool rockSetDist(stRock& pDest)
{
    bool bResult = false;
    stRock& pRock = pDest;
    if (pDest.prevKey == NOT_INITIALIZE) goto lb_return;
    
    pRock.dist = pRock.nextKey - pRock.prevKey;

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


        if (i != 0) prvIndex = src.at(i);
        if (i != size - 1) nextIndex = src.at(i + 1);

        rockSetPrevIndex(pOut[i], prvIndex);
        rockSetNextIndex(pOut[i], nextIndex);

        rockSetDist(pOut[i]);
    }

    bResult = true;

lb_return:
    return bResult;
}

bool rockManagerSortByPrevDist(stRock& r1, stRock& r2)
{
    bool bResult = false;
    if (r1.dist < r2.dist)
    {
        bResult = true;
    }
    else if (r1.dist == r2.dist)
    {
        if (r1.prevKey < r2.prevKey) bResult = true;
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