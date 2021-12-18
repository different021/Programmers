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
    문제의 의도가 정확하게 설명되지 않는다.
    첫번째 샘플의 A를 1, B를 2로만 바꾸어 놓아도 어느정도 의도가 설명이 될텐데.
    
    빈약한 설명과 배려가 부족한 샘플 제시로
    출제자에게 -100점 드립니다. 

    [아래 샘플로 설명이 안되는 경우]
    가장 큰 우선 순위를 갖는 인덱스를  i 

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


int solution(vector<int> priorities, int location) {
    int answer = 0;
    vector<int>& inputVect = priorities;
    queue<int> resultQue;

    size_t size = inputVect.size();
    size_t targetIndex = 0;

    int priority = 0;
    int cnt = 0;

    //[Start] Check Parameter
    if (size < 1)
    {
        //벡터에 데이터가 없는 경우
        goto lb_return;
    }
    if (location < 0)
    {
        //잘못된 인덱스를 입력한 경우
        goto lb_return;
    }
    //[Done] Check Parameter()
    targetIndex = static_cast<int>(location);

    for (vector<int>::iterator it = inputVect.begin(); it != inputVect.end(); )
    {
        int prio = *priorities.begin();
        it = inputVect.erase( inputVect.begin() );
        vector<int>::iterator itInner;
        for ( itInner = inputVect.begin(); itInner != inputVect.end(); itInner++)
        {
            if (prio < *itInner)
            {
                inputVect.push_back(prio);
                targetIndex--;
                break;
            }
        }

        if ((itInner) == inputVect.end())
        {
            resultQue.push(prio);
        }
    }


    printf("Que Test \n");
    while (resultQue.empty() != true)
    {
        printf("%d\n", resultQue.front());
        resultQue.pop();
    }
    

lb_return:
    return answer;
}






int main()
{
    /*vector<int> priorities = { 2, 1, 3, 2 };
    int location = 2;*/

    vector<int> priorities = { 1, 1, 9, 1, 1, 1 };
    int location = 0;

    int result = solution(priorities, location);
    printf("%d번 문서의 인쇄 순서 : %d\n", location, result);

    return 0;
}