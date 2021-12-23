/*
    음식의 매운 정도를 나타내는 스코빌지수(scoville)
    주어진 음식들을 섞어서 일정 수준(k) 이상의 스코빌 지수로 만들고 싶다.
    
    섞는 방식은 아래와 같다.
    새로운 음식 스코빌 지수 = 가장 안 매운 음식 스코빌 + (두번째로 맵지 않은 스코빌 * 2)

    주어진 배열의 수를 모두 k 이상으로 만들때, 섞는 최소 횟수를 구하여 리턴 하시오

    [제한 사항]
    scovile.size()  : 2 ~ 1000000
    k               : 0 ~ 1000000000
    return -1 (모든 음식을 k 이상으로 만들 수 없는 경우)

    [예시]
    (각음식의 스코빌)           (섞는 행위를 2번 실행) 
    scoville	            K	return
    [1, 2, 3, 9, 10, 12]	7	2

    [설명]
    1. 1과 2가 가장 적은 숫자. 
        따라서 새로운 음식은 1 + (2 * 2) = 5가 된다.
    2. 새로운 배열은
        { 5, 3, 9, 10, 12 }
    3. 아직 k(=7)이하의 값이 존재
        3이 가장 작고, 다음은 5
        따라서, 새로운 음식은 3 + (5 * 2) = 13
    4. 새로운 배열
        {13, 9, 10, 12}
        모든 스코빌 지수가 k(=7) 이상.
    5. 섞는 행위는 2번 반복 되었다.
 */

/*
    [LOGIC]
    1. 배열을 모두 우선 순위 힙에 때려 박는다.
    2. 가장 앞의 값을 확인. 
        ->(scovile < k) 1번과 2번 값 pop() 
                -> pop() 가능? newScovile = GetScovile(first, second)
                -> pop() 실패?(원소가 2개 이하) 함수 실패
        
        ->(scovile > k)
                솔루션 종료
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
    parameter의 vector의 값들을 2개씩 특저어 규칙으로 합쳐서 k값 이상으로 만들어준다.
    
    [return]
    두 값을 합친 횟수
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
            //[예외처리]
            //최대횟수 초과
            break;
        }

        bool isCombine = ScovilleCombineSmallestTwo(scovilleQue);
        if (isCombine)
        {
            combineCount++;
        }
        else
        {
            //모든 수를 k 이상으로 만들지 못한 경우
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
        //int scov = it;
        //out.push(scove);  
        out.push(it);       //미세하게 더 빠르다.
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

//가장 작은 두 수를 더해서 큐에 다시 집어넣는다.
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
        //존재하지 할 수 없는 값
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