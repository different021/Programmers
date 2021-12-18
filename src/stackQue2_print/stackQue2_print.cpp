/*
    급한 문서를 우선 출력하는 시스템을 개발
    
    1. 가장 앞에 있는 문서(j = 0)을 꺼낸다.
    2. j보다 우선 순위가 높은 문서가 한개라도 존재하면 j를 대기 목록 가장 뒤로 보낸다.
    3. 그렇지 않으면 j 인쇄


    //애매한 샘플 
    priorities	        location	return
    [2, 1, 3, 2]	    2	        1
    [1, 1, 9, 1, 1, 1]	0	        5

    빈약한 설명의 문제
    빈약한 설명과 배려가 부족한 샘플 제시로
    출제자에게 -100점 드립니다. 

    solution([2, 4, 8, 2, 9, 3, 3], 2) return 2 

     A, B, C, D, E, F, G 
    [2, 4, 8, 2, 9, 3, 3]

    EFGABCD

    i가 2일때, return 2 (C(8)는 2번째로 인쇄)
    i가 4일때, return 1 (E(9)는 1번째로 인쇄)

    

    [parameter]
    vector<int> : 우선도 배열
    int         : 인쇄순서를 알고싶은 문서 (0부터 시작)

    [return]
    int         : 인쇄될 숫서 (1부터 시작)

    [제한 사항]
    priorities.size()   : 1 ~ 100
    priority            : 1 ~ 9
    location            : 0 ~ 99

*/

/*
*   solution
    1. 첫번째 요소 추출
    2. 나머지 요소와 비교
    3. 하나라도 큰 우선도가 존재하면 가장 뒤로
    4. 없으면 완료Que로
    5. 모든 요소가 제거 될때까지 1~4 반복.

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
    if (size < 1)       goto lb_return;     //벡터에 데이터가 없는 경우
    if (location < 0)   goto lb_return;     //잘못된 인덱스를 입력한 경우

    bSuccess = MakeDocumentVector(vecDocument, priorities);
    if (bSuccess == false)
    {
        //실패 처리
    }
    
    //정렬하여 resultQue로 보냄 -> 사실 보낼 필요없다.
    bSuccess = SortDocumentByPriority(resultQue, vecDocument);
    if (bSuccess == false)
    {
        //실패 처리
    }
    
    bSuccess = GetTurnOfDocument(answer, resultQue, location);
    if(bSuccess == false)
    {
        //실패처리
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

        //int max = *max_element(priorities.begin(), priorities.end()); -> 범위내 최대값, 아래 로직 대체 가능할듯?

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
    printf("%d번 문서의 인쇄 순서 : %d\n", location, result);

    return 0;
}