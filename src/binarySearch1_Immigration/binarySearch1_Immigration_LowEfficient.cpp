/*
    [solution]
    cur
    next
    ���� ����. �� ������Ʈ
    next���� ���� ���� ������ ������.

    next�� �������� ����
    ���� ���� next�� passed ����(0�� �ε���)
    0���ε����� ������ ������ ���� ����
    n�� �ݺ�

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
    int times;          //�ɻ翡 �ɸ��� ��
    int passed;         //�ɻ��� ��
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
    //if (pOffice != nullptr) { /*���� ���н�, ó�� �ڵ�*/ };

    //�ʱ�ȭ
    for (auto& it : times)
    {
        if (index > size)
        {
            //����ó�� �߰�
            break;
        }
        ImmigrationInitalize(pOffice[index], it);
        index++;
    }

    sort(pOffice, pOffice + size, ImmigrationCompByLessNextValue);

    for (int i = 0; i < n; i++)
    {
        //�Ʒ� �� �Լ��� ��Ʈ�� ��� �� ��. 
        //�� ���� -> ���� ����(����� 0�� �ε����� ���� ������ ��ġ�� ��������.)
        ImmigrationIncreasePassed(pOffice[0]);     //next�� cur�� ������ �׻� ��ġ�ϴ� ���� �ƴϴ�.
        OfficeSortByLessNextValue(pOffice, size);
    }

    //�ִ밪 ã��
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
        //�ΰ��� ���� ��� times�� ���Ͽ� ������ ���Ѵ�. Ÿ��� ���� �༮�� ������ ����. 
        if (ins1.times < ins2.times)
            bResult = true;
    }

    return bResult;
}

/*
    @detail dest �ʱ�ȭ. �Ա��ɻ翡 �Ÿ��� �ð��� �Է��� �ٰ�.
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
    @detail �ɻ��� ��� �߰�. passed 1����, cur, next, ����.
*/
int ImmigrationIncreasePassed(Immigration& dest)
{
    int curValue = 0;
    dest.passed++;                                      //�Ա� �ɻ��� ���� ����
    ll_t increment = static_cast<ll_t>(dest.times);
    dest.cur += increment;        //���� �ο�����
    dest.next += increment;       //�Ѹ� �� �ϸ� �󸶳� �ɸ���?

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
    0�� �ε����� ���� ����Ǿ� ������ �°� �������Ѵ�.
    ��, 0�� �̿��� ������ �̹� ���ĵǾ� �־�, ���������� �ǽ��Ѵ�.
    1. ���� Ž�� -> ��ġ ã��
    2. ���� ����

    @warning ã�⸸�Ѵ�. -> ������ �ٲ����� �ʴ´�.
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
            //�߰� �� ���� �۰ų� ���� ���

            //   here        
            //s---------mid----------e

            end = mid - 1;
        }
        else if (halfValue < modifiedValue)
        {
            //�߰� ������ ũ�ų� ���� ���

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

//0�� �ε������� insert sort �Ѵ�.
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
        //���� ó�� �߰� 
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
