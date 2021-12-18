/*
    ���� ������ �켱 ����ϴ� �ý����� ����
    
    1. ���� �տ� �ִ� ����(j = 0)�� ������.
    2. j���� �켱 ������ ���� ������ �Ѱ��� �����ϸ� j�� ��� ��� ���� �ڷ� ������.
    3. �׷��� ������ j �μ�


    //�ָ��� ���� 
    priorities	        location	return
    [2, 1, 3, 2]	    2	        1
    [1, 1, 9, 1, 1, 1]	0	        5

    ����� ������ ����
    ����� ����� ����� ������ ���� ���÷�
    �����ڿ��� -100�� �帳�ϴ�. 

    solution([2, 4, 8, 2, 9, 3, 3], 2) return 2 

     A, B, C, D, E, F, G 
    [2, 4, 8, 2, 9, 3, 3]

    EFGABCD

    i�� 2�϶�, return 2 (C(8)�� 2��°�� �μ�)
    i�� 4�϶�, return 1 (E(9)�� 1��°�� �μ�)

    

    [parameter]
    vector<int> : �켱�� �迭
    int         : �μ������ �˰���� ���� (0���� ����)

    [return]
    int         : �μ�� ���� (1���� ����)

    [���� ����]
    priorities.size()   : 1 ~ 100
    priority            : 1 ~ 9
    location            : 0 ~ 99

*/

/*
*   solution
    1. ù��° ��� ����
    2. ������ ��ҿ� ��
    3. �ϳ��� ū �켱���� �����ϸ� ���� �ڷ�
    4. ������ �Ϸ�Que��
    5. ��� ��Ұ� ���� �ɶ����� 1~4 �ݺ�.

*/


#include <string>
#include <vector>
#include <queue>

using namespace std;

struct stDocument
{
    int priority;
    int location;

    stDocument(int prio, int loc)
    {
        priority = prio;
        location = loc;
    }
};

bool MakeDocumentVector(vector<stDocument>& out, vector<int>& srcPriority);
bool SortDocumentByPriority(queue<stDocument>& out, vector<stDocument>& src);
bool GetTurnOfDocument(int& outTurn, queue<stDocument>& queDocuemnt, int indexInOriginVector);

int solution(vector<int> priorities, int location) {
    int answer = 0;
    bool bSuccess = false;
    vector<stDocument> vecDocument;
    queue<stDocument> resultQue;

    size_t size = priorities.size();

    //[Start] Check Parameter
    if (size < 1)       goto lb_return;     //���Ϳ� �����Ͱ� ���� ���
    if (location < 0)   goto lb_return;     //�߸��� �ε����� �Է��� ���

    bSuccess = MakeDocumentVector(vecDocument, priorities);
    if (bSuccess == false)
    {
        //���� ó��
    }
    
    //�����Ͽ� resultQue�� ���� -> ��� ���� �ʿ����.
    bSuccess = SortDocumentByPriority(resultQue, vecDocument);
    if (bSuccess == false)
    {
        //���� ó��
    }
    
    bSuccess = GetTurnOfDocument(answer, resultQue, location);
    if(bSuccess == false)
    {
        //����ó��
    }

lb_return:
    return answer;
}


bool MakeDocumentVector(vector<stDocument>& _out, vector<int>& _srcPriority)
{
    bool bResult = false;
    vector<stDocument>& out = _out;
    vector<int>& srcPriority = _srcPriority;
    size_t size = srcPriority.size();
    
    if (size == 0) goto lb_return;

    out.reserve(size);      

    for (auto it : srcPriority)
    {
        static int i = 0;
        out.push_back(stDocument(it, i));
        i++;
    }

    bResult = true;

lb_return:
    return bResult;
}

bool SortDocumentByPriority(queue<stDocument>& out, vector<stDocument>& src)
{
    bool bResult = false;
    vector<stDocument>& vecDocument = src;
    queue<stDocument>& resultQue = out;

    //[Check Parameter]
    if (vecDocument.size() == 0) goto lb_return;

    for (vector<stDocument>::iterator it = vecDocument.begin(); it != vecDocument.end(); )
    {
        stDocument curDoc = *(vecDocument.begin());
        it = vecDocument.erase(vecDocument.begin());

        //int max = *max_element(priorities.begin(), priorities.end()); -> ������ �ִ밪, �Ʒ� ���� ��ü �����ҵ�?

        vector<stDocument>::iterator itInner;
        for (itInner = vecDocument.begin(); itInner != vecDocument.end(); itInner++)
        {
            if (curDoc.priority < itInner->priority)
            {
                vecDocument.push_back(curDoc);
                break;
            }
        }

        if ((itInner) == vecDocument.end())
        {
            resultQue.push(curDoc);
        }
    }

lb_return:
    return bResult;
}


bool GetTurnOfDocument(int& outTurn, queue<stDocument>& queDocuemnt, int indexInOriginVector)
{
    bool bResult = false;
    int& turn = outTurn;
    int location = indexInOriginVector;
    queue<stDocument>& que = queDocuemnt;
    
    if (location < 0) goto lb_return;
    if (que.size() == 0) goto lb_return;

    while (que.empty() != true)
    {
        turn++;
        stDocument print = que.front();
        que.pop();

        if (print.location == location)
        {
            break;
        }
    }

lb_return:
    return bResult;
}

int main()
{
    //vector<int> priorities = { 2, 1, 3, 2 };
    //int location = 2;

    vector<int> priorities = { 1, 1, 9, 1, 1, 1 };
    int location = 0;

    int result = solution(priorities, location);
    printf("%d�� ������ �μ� ���� : %d\n", location, result);

    return 0;
}