/*
    두개의 벡터(vector<int>)가 주어진다.
    첫번째는 현재 진행완료율
    두번째는 하루에 진행 가능한 %
    기능은 100%에 도달 했을때만 배포 가능합니다.
    하지만, 뒤에 기능이 먼저 완료되었다 하더라도 앞의 기능이 완료되지 않았다면, 배포할 수 없습니다.
    각 배포마다 몇개의 기능이 배포가능한지 리턴.


    [parameter]
    vector<int> progresses  : 현재 진행 완료율
    vector<int> speeds      : 하루 가능 진행률

    [return]
    vector<int>             : 배포시 배포되는 기능 수

    progresses.size() < 100     작업의 갯수(progresses, speeds) 는 100개 이하.
    progress < 100              progress는 100미만 정수 
    speeds < 100

    ex)
    progresses	                speeds	            return
    [93, 30, 55]	            [1, 30, 5]	        [2, 1]
    [95, 90, 99, 99, 80, 99]	[1, 1, 1, 1, 1, 1]	[1, 3, 2]
*/


/*
    [RULES]
    1. 무조건 0번부터 순서대로 배포해야한다.
    2. 100이 되어야만 배포 가능하다.

    How to solve?
    
    loop()
    {
        1. progress에 speed를 더한다.
        2. 배포되지 않은 최신 기능이 100 이상인지 검사
          -> 100이상일 경우, 다음 요소 검사 (배포 불가능을 만날 때까지 반복) 
            -> 더 이상 100이없으면 배포(배포 카운터 저장)
          -> 100미만일 경우, 루프 반복
    }

*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

//함수가 길어서 분해 필요
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> completeQue;
    size_t progressSize = progresses.size();
    size_t speedSize = speeds.size();
    size_t notCompleteProcessIndex = 0;        //배포 안된 프로세스 인덱스


    if (progressSize != speedSize)
    {
        //예외 처리
        //둘은 같아야만 한다.
        goto lb_return;
    }


    //모든 작업이 완료 될때까지 반복.
    while (notCompleteProcessIndex < progressSize)
    {
        int countOfComplete = 0;
        //100미만이 확실하다는 가정하에 바로 루프 시작(데이터 신뢰)
        for (int i = notCompleteProcessIndex; i < progressSize; i++)
        {
            progresses.at(i) += speeds.at(i);
            progresses.at(i) = min(progresses.at(i), 100);      //최대치 100
        }

        for (auto it : progresses)
        {
            if (notCompleteProcessIndex >= progressSize) break; //완료 케이스

            //진행률이 100보다 크다.
            if (progresses.at(notCompleteProcessIndex) == 100)
            {
                //챕터에 스택 큐라고 써있어서 하긴하는데 필요없다.
                countOfComplete++;
                notCompleteProcessIndex++;
            }
            else
            {
                break;
            }
        }

        if (countOfComplete > 0)
        {
            //배포된 기능이 있는 경우 몇개 를 배포 했는지 저장.
            completeQue.push(countOfComplete);
        }
    }

    while (completeQue.empty() == false)
    {
        int releaseCnt = completeQue.front();
        completeQue.pop();
        answer.push_back(releaseCnt);

    }

lb_return:
    return answer;
}

int main()
{
    /*
    //case1
    vector<int> progresses = { 93, 30, 55 };
    vector<int> speeds = { 1, 30, 5 };          ////[return] [2, 1]
    */

    //case2
    vector<int> progresses  = { 95, 90, 99, 99, 80, 99 };
    vector<int> speeds      = { 1, 1, 1, 1, 1, 1 };      //return [1, 3, 2]

    vector<int> result = solution(progresses, speeds);
    printf("[RESULT]\n");
    for (auto it : result)
    {
        printf("%d\n", it);
    }

    return 0;
}