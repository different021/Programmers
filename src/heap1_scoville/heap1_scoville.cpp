/*
    ������ �ſ� ������ ��Ÿ���� ���ں�����(scoville)
    �־��� ���ĵ��� ��� ���� ����(k) �̻��� ���ں� ������ ����� �ʹ�.
    
    ���� ����� �Ʒ��� ����.
    ���ο� ���� ���ں� ���� = ���� �� �ſ� ���� ���ں� + (�ι�°�� ���� ���� ���ں� * 2)

    �־��� �迭�� ���� ��� k �̻����� ���鶧, ���� �ּ� Ƚ���� ���Ͽ� ���� �Ͻÿ�

    [���� ����]
    scovile.size()  : 2 ~ 1000000
    k               : 0 ~ 1000000000
    return -1 (��� ������ k �̻����� ���� �� ���� ���)

    [����]
    (�������� ���ں�)           (���� ������ 2�� ����) 
    scoville	            K	return
    [1, 2, 3, 9, 10, 12]	7	2

    [����]
    1. 1�� 2�� ���� ���� ����. 
        ���� ���ο� ������ 1 + (2 * 2) = 5�� �ȴ�.
    2. ���ο� �迭��
        { 5, 3, 9, 10, 12 }
    3. ���� k(=7)������ ���� ����
        3�� ���� �۰�, ������ 5
        ����, ���ο� ������ 3 + (5 * 2) = 13
    4. ���ο� �迭
        {13, 9, 10, 12}
        ��� ���ں� ������ k(=7) �̻�.
    5. ���� ������ 2�� �ݺ� �Ǿ���.
 */

/*
    [LOGIC]
    1. �迭�� ��� �켱 ���� ���� ���� �ڴ´�.
    2. ���� ���� ���� Ȯ��. 
        ->(scovile < k) 1���� 2�� �� pop() 
                -> pop() ����? newScovile = GetScovile(first, second)
                -> pop() ����?(���Ұ� 2�� ����) �Լ� ����
        
        ->(scovile > k)
                �ַ�� ����
*/

#include <string>
#include <vector>
#include <queue>

#define MAX_SIZE 1000000

using namespace std;

struct compareScoville
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

typedef priority_queue<int, vector<int>, compareScoville> ScovilleQueue;

int  CombineScoville(int first, int second);
bool ScovilleInitialize(ScovilleQueue& out, vector<int>& src);
bool ScovilleIsFirstDataUnderCutLine(ScovilleQueue& que, int iCutLine);
bool ScovilleCombineSmallestTwo(ScovilleQueue& que);
bool ScovillePrint(ScovilleQueue& que);

/*
    parameter�� vector�� ������ 2���� Ư���� ��Ģ���� ���ļ� k�� �̻����� ������ش�.
    
    [return]
    �� ���� ��ģ Ƚ��
*/
int solution(vector<int> scoville, int K) {
    int answer = 0;
    int cutLine = K;
    int combineCount = 0;
    int safeCount = 0;
    bool bSuccess = false;

    priority_queue<int, vector<int>, compareScoville> scovilleQue;

    ScovilleInitialize(scovilleQue, scoville);
    
    while ( ScovilleIsFirstDataUnderCutLine(scovilleQue, cutLine) == false )
    {
        if (safeCount > MAX_SIZE)
        {
            //[����ó��]
            //�ִ�Ƚ�� �ʰ�
            break;
        }

        bool isCombine = ScovilleCombineSmallestTwo(scovilleQue);
        if (isCombine)
        {
            combineCount++;
        }
        else
        {
            //��� ���� k �̻����� ������ ���� ���
            answer = -1;
            goto lb_return;
        }
        
    } 
    
    answer = combineCount;

lb_return:
    return answer;
}

//return -1, when input invaild data
int  CombineScoville(int first, int second)
{
    int iResult = -1;
    if (first < 0) goto lb_return;
    if (second < 0) goto lb_return;

    iResult = first + (second * 2);

lb_return:
    return iResult;
}

//Copt Data Vector -> priorityQueue
bool ScovilleInitialize(ScovilleQueue& out, vector<int>& src)
{
    bool bResult = false;
    if (src.size() == 0) goto lb_return;

    for (auto& it : src)
    {
        int scov = it;
        out.push(scov);
    }

    bResult = true;

lb_return:
    return bResult;
}

bool ScovilleIsFirstDataUnderCutLine(ScovilleQueue& que, int iCutLine)
{
    bool bResult = false;
    int smllestData = que.top();
    if (smllestData > iCutLine)
    {
        bResult = true;
    }

    return bResult;
}

//���� ���� �� ���� ���ؼ� ť�� �ٽ� ����ִ´�.
bool ScovilleCombineSmallestTwo(ScovilleQueue& que)
{
    bool bResult = false;
    int first = 0;
    int second = 0;
    int newScov = 0;
    if (que.size() < 2) goto lb_return;
    
    first = que.top();
    que.pop();
    
    second = que.top();
    que.pop();
    
    newScov = CombineScoville(first, second);
    if (newScov > 0)
    {
        que.push(newScov);
        bResult = true;
    }
    else
    {
        //�������� �� �� ���� ��
        //assert(false);
        
    }

lb_return:
    return bResult;
}

bool ScovillePrint(ScovilleQueue& que)
{
    bool bResult = false;
    
    printf("[PRIORITY_QUEUE]\t");
    while (que.empty() == false)
    {
        const int& a = que.top();
        printf("%d \t", a);
        que.pop();
    }
    printf("\n");

lb_result:
    return bResult;
}



int main()
{
    //return 2
    vector<int> scovile = { 1, 2, 3, 9, 10, 12 };
    int k = 7;	

    int result = solution(scovile, k);

    printf("RESULT : %d", result);

    return 0;
}