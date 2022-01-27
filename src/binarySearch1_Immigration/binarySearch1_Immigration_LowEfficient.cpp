/*
    [solution]
    cur
    next
    값을 유지. 및 없데이트
    next값이 가장 낮은 곳으로 보낸다.

    next를 기준으로 정렬
    가장 낮은 next에 passed 증가(0번 인덱스)
    0번인덱스를 적절한 곳으로 삽입 정렬
    n번 반복

*/

#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

typedef long long ll_t;

struct Immigration
{
    long long next;
    long long cur;      //
    int times;          //심사에 걸리는 수
    int passed;         //심사한 수
};

bool ImmigrationCompByHighCurValue(const Immigration& ins1, const Immigration& ins2);
bool ImmigrationCompByLessNextValue(const Immigration& ins1, const Immigration& ins2);
bool ImmigrationInitalize(Immigration& dest, int times);
int ImmigrationIncreasePassed(Immigration& dest);

//Office class
ll_t OfficeSortByLessNextValue(vector<Immigration>& dest);
ll_t OfficeSortByLessNextValue(Immigration* pDest, int size);
ll_t OfficeGetMaxCurrentValue(Immigration* pDest, int size);


long long solution(int n, vector<int> times) {
    long long answer = 0;
    int size = static_cast<int>(times.size());
    Immigration* pOffice = new Immigration[size];
    int index = 0;
    //if (pOffice != nullptr) { /*말록 실패시, 처리 코드*/ };

    //초기화
    for (auto& it : times)
    {
        if (index > size)
        {
            //예외처리 추가
            break;
        }
        ImmigrationInitalize(pOffice[index], it);
        index++;
    }

    sort(pOffice, pOffice + size, ImmigrationCompByLessNextValue);

    for (int i = 0; i < n; i++)
    {
        //아래 두 함수는 셋트로 사용 할 것. 
        //값 변경 -> 삽입 정렬(변경된 0번 인덱스의 값을 적절한 위치로 삽입정렬.)
        ImmigrationIncreasePassed(pOffice[0]);     //next와 cur의 순서가 항상 일치하는 것은 아니다.
        OfficeSortByLessNextValue(pOffice, size);
    }

    //최대값 찾기
    answer = OfficeGetMaxCurrentValue(pOffice, size);

    delete[] pOffice;
    pOffice = nullptr;

    return answer;
}


bool ImmigrationCompByHighCurValue(const Immigration& ins1, const Immigration& ins2)
{
    bool bResult = false;

    if (ins1.cur < ins2.cur)
    {
        bResult = true;
    }

    return bResult;
}

bool ImmigrationCompByLessNextValue(const Immigration& ins1, const Immigration& ins2)
{
    bool bResult = false;

    if (ins1.next < ins2.next)
    {
        bResult = true;
    }
    else if (ins1.next == ins2.next)
    {
        //두값이 같을 경우 times를 비교하여 우위를 정한다. 타임즈가 작은 녀석이 앞으로 간다. 
        if (ins1.times < ins2.times)
            bResult = true;
    }

    return bResult;
}

/*
    @detail dest 초기화. 입국심사에 거리는 시간을 입력해 줄것.
*/
bool ImmigrationInitalize(Immigration& dest, int times)
{
    bool bResult = false;
    if (times < 0) goto lb_return;

    dest.times = times;
    dest.passed = 0;
    dest.cur = 0;
    dest.next = static_cast<ll_t>(times);

    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail 심사한 사람 추가. passed 1증가, cur, next, 증가.
*/
int ImmigrationIncreasePassed(Immigration& dest)
{
    int curValue = 0;
    dest.passed++;                                      //입국 심사한 갯수 증가
    ll_t increment = static_cast<ll_t>(dest.times);
    dest.cur += increment;        //현재 인원까지
    dest.next += increment;       //한명 더 하면 얼마나 걸릴까?

    return dest.cur;
}


ll_t OfficeSortByLessNextValue(vector<Immigration>& dest)
{
    ll_t llResult = 0;

    sort(dest.begin(), dest.end(), ImmigrationCompByLessNextValue);
    llResult = dest.at(0).cur;

    return llResult;
}


/*
    @detail
    0번 인덱스의 값이 변경되어 순서에 맞게 재정렬한다.
    단, 0번 이외의 값들은 이미 정렬되어 있어, 삽입정렬을 실시한다.
    1. 이진 탐색 -> 위치 찾기
    2. 삽입 정렬

    @warning 찾기만한다. -> 순서를 바꾸지는 않는다.
*/
size_t OfficeBinarySearchByNextValue(Immigration* pDest, int size, int _indexOfStart, int _indexOfEnd)
{
    size_t start = _indexOfStart;
    size_t end = _indexOfEnd;
    size_t mid = (start + end) / 2;
    ll_t halfValue = pDest[mid].next;
    ll_t modifiedValue = pDest[0].next;

    if (pDest[0].next < pDest[1].next)
    {
        mid = -1;
        goto lb_return;
    }

    while (true)
    {
        if (mid < start) break;
        if (mid > end) break;

        if (halfValue > modifiedValue)
        {
            //중간 값 보다 작거나 같은 경우

            //   here        
            //s---------mid----------e

            end = mid - 1;
        }
        else if (halfValue < modifiedValue)
        {
            //중간 값보다 크거나 같은 경우

            //                here
            //s---------mid----------e

            start = mid + 1;
        }
        else if (halfValue == modifiedValue)
        {
            if (pDest[mid].times >= pDest[0].times)
            {

                //    here 
                //s---------mid----------e
                end = mid - 1;
            }
            else
            {
                //                here
                //s---------mid----------e
                start = mid + 1;
            }
        }
        mid = static_cast<size_t>(start + end) / 2;

        if (mid < 1) break;
        if (mid >= size) break;

        halfValue = pDest[mid].next;
    }

lb_return:
    return mid;
}

//0번 인덱스값을 insert sort 한다.
bool OfficeInsertSortZeroIndex(Immigration* pDest, int numOfMember, int targetIndex)
{
    bool bResult = false;
    Immigration temp = pDest[0];
    size_t size = 0;

    if (targetIndex == -1)   goto lb_return;

    size = sizeof(Immigration) * targetIndex;
    memcpy(pDest, pDest + 1, size);
    memcpy(pDest + targetIndex, &temp, sizeof(Immigration));

    bResult = true;

lb_return:
    return bResult;
}

ll_t OfficeSortByLessNextValue(Immigration* pDest, int size)
{
    ll_t llResult = 0;

    int insertindex = OfficeBinarySearchByNextValue(pDest, size, 1, size - 1);
    bool bSuccess = OfficeInsertSortZeroIndex(pDest, size, insertindex);
    if (bSuccess == false)
    {
        //실패 처리 추가 
    }

    //sort(pDest, pDest + size, ImmigrationCompByLessNextValue);
    llResult = pDest[size - 1].cur;

    return llResult;
}

ll_t OfficeGetMaxCurrentValue(Immigration* pDest, int size)
{
    ll_t llResult = 0;

    llResult = max_element(pDest, pDest + size, ImmigrationCompByHighCurValue)->cur;

    return llResult;
}
