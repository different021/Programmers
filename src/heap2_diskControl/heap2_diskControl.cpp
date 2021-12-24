/*
    디스크는 한번에 한가지 일 밖에 하지 못한다.
    디스크에 2차원 배열 형태로 업무가 들어온다.
    { 요청 시점(int), 소요시간(int) }

    예를 들면,
    A : 0초 요청, 3초 소요
    B : 1초 요청, 9초 소요
    C : 2초 요청, 6초 소요

    위 요청을 A, B, C순으로 처리하면,

    A : 0초 요청, 0초 시작, 3초 종료 = 3초
    B : 1초 요청, 3초 시작, 12초 종료 = 11초
    C : 2초 요청, 12초 시작, 18초 종료 = 16초

    평균처리 시간은,
    평균처리시간 = ( 3 + 11 + 16) / 3
    처리순서 ABC일때,
    10초가 나온다.

    하지만 A, C, B 순으로 처리하면,

    A : 0초 요청, 0초 시작, 3초 종료 = 3초
    C : 2초 요청, 3초 시작, 9초 종료 = 7초
    B : 1초 요청, 9초 시작, 18초 종료 = 17초

    평균 처리시간 = (3 + 7 + 17) / 3
    9초가 나오게 된다.

    [파라미터]
    vector<vector<int>> (요청시간, 처리시간) 2차원 배열

    [리턴]
    가장 적은 평균 처리 시간

    [제한 사항]
    jobs.size() : 1 ~ 500
    요청 시간 : 0 ~ 1000
    소요 시간 : 1 ~ 1000
    업무가 없을때는 들어온 순으로.
*/


/*
    [Simple LOGIC]
    jobs -> requestQue
    while()
    {
        requestQue -> DurationQue
        DurationQue -> CompleteQue
    }


    [종료 조건]
    1. requestQue.size() == 0;
    2. drationQue.size() == 0;
    (1 & 2) 가 모두 참일때 솔루션 종료
    
    [soltuion]
    1. requestQueue에 요청 시간이 빠른 순으로 정렬해서 집어넣는다.
    
    2.
    소요시간 우선순위큐에 내용이 비었다?
       (가장 작은 요청시간을 넣는다.)   <- 동일로직a
       
    소요시간 큐가 비지 않았다?
        완료시간을 찾고 그보다 작은 요청시간을 모두 넣는다.
        없다면 (가장 작은 요청시간을 넣는다.) <- 동일로직a
    
    3. 소요시간 큐의 최소값을 완료큐로 이동 (이때, 완료시간과 처리시간 계산)

    4. 평균 소요 시간을 구한다. sum(처리시간총량) /  size 

    [필요]    
    requestQue  : 요청 시간이 낮은순으로 정렬   (우선순위 큐)
    durationQue : 소요시간이 낮은순으로 정렬    (우선순위 큐)

    completedTask : 완료된 작업    (큐 or vector)


    [예측]
    1. 소요시간이 적은 업무를 우선 처리하는 편이 빠를 것이다.
    2. 처리하는 업무가 완료되는 시점을 계산한다.
    3. 처리되는 시간까지 들어온 요청 중, 소요시간이 가장 작은 순으로 처리한다.
    
    [주의]
    인티저를 나누기 연산하는 과정이 있다. -> ....

*/


#include <string>
#include <vector>
#include <queue>

using namespace std;

struct stTask
{
    int requestTime;    //요청시간
    int duration;       //소요시간
    int completeTime;   //완료시간
    int handlingTime;   //처리시간

    //생성자1 
    stTask()  
    {
        requestTime = 0;
        duration = 0;
        completeTime = 0;
        handlingTime = 0;
    }

    //생성자2
    stTask(int request, int duration)
    {
        requestTime     = request;
        this->duration  = duration;
        completeTime    = 0;
        handlingTime = 0;
    }
};

//요청 시간에 순으로 정렬
struct orderByRequestTime
{
    bool operator()(stTask& a, stTask& b)
    {
        return a.requestTime > b.requestTime;
    }
};

//소요 시간 순으로 정렬
struct orderByDuration
{
    bool operator()(stTask& a, stTask& b)
    {
        bool bResult = false;
        if (a.duration > b.duration)
        {
            //소요시간이 작으면 먼저
            bResult = true;
        }
        else if (a.duration == b.duration)
        {
            if (a.requestTime > b.requestTime)
            {
                //요청 시간이 작으면 먼저 
                bResult = true;
            }
        }

        return bResult;
    }
};

typedef priority_queue<stTask, vector<stTask>, orderByRequestTime> RequestQueue;    //요청 시간 순으로 정렬되는 큐
typedef priority_queue<stTask, vector<stTask>, orderByDuration> DurationQueue;      //소요 시간 순으로 정렬되는 큐
typedef queue<stTask> CompleteQueue;

//Task class
bool StTaskGetHandlingTime(stTask& task);

//Request class
bool RequestQueueInitialize(RequestQueue& out, vector<vector<int>>& src);

//Complete class
bool CompleteQueuePush(CompleteQueue& que, stTask task);

//Solution class
bool SolutionRequestToDurationUnderInputTime(RequestQueue& start, DurationQueue& end, int input);
bool SolutionRequestToDuration(RequestQueue& start, DurationQueue& end);
bool SolutionDurationToComplete(DurationQueue& start, CompleteQueue& end);
bool SolutionGetAverageHandlingTime(int& out, CompleteQueue& completeQue);

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    RequestQueue requestQue;
    DurationQueue durationQue;
    CompleteQueue completeQue;
    bool bSuccess = false;

    bSuccess = RequestQueueInitialize(requestQue, jobs);

    
    while ( (requestQue.size() != 0) || (durationQue.size() != 0) )
    {
        //request -> duration
        int completeTime = 0;
        if (completeQue.empty() == false)
        {
            completeTime = completeQue.back().completeTime;
        }
        bool bSuccess = SolutionRequestToDurationUnderInputTime(requestQue, durationQue, completeTime);
        
        //duration -> complete (completeTime, handlingTime 계산)
        SolutionDurationToComplete(durationQue, completeQue);

    }
     
    SolutionGetAverageHandlingTime(answer, completeQue);

    return answer;
}

/*
    [리턴]
    양수(< 0) : false (논리적 불가능)
    음수(> 0) : true  (정상으로 예측되는 값)
*/
bool StTaskGetHandlingTime(stTask& task)
{
    bool bResult = false;
    int handlingTime = task.completeTime - task.requestTime;
    if (handlingTime < 0) goto lb_return;
    
    task.handlingTime = handlingTime;
    bResult = true;

lb_return:
    return bResult;
}

bool RequestQueueInitialize(RequestQueue& out, vector<vector<int>>& src)
{
    bool bResult = false;
    if (src.size() == 0) goto lb_return;    //빈 배열

    for (auto& it : src)
    {
        stTask newTask(it[0], it[1]);
        out.push(newTask);
    }
    bResult = true;

lb_return:
    return bResult;
}

bool CompleteQueuePush(CompleteQueue& que, stTask _task)
{
    bool bResult = false;
    CompleteQueue& completeQue = que;
    stTask task = _task;
    int pastCompleteTime = 0;
    
    if (completeQue.size() != 0)
    {
        //완료큐의 최상단 
        pastCompleteTime = (completeQue.back().completeTime > task.requestTime) ? completeQue.back().completeTime : task.requestTime;
    }
    else
    {
        pastCompleteTime = task.requestTime;
    }

    //이 작업의 완료 시간 = 과거의 완료 시간 + 소요시간
    task.completeTime = pastCompleteTime + task.duration;

    //처리시간 구하기(완료시간 - 요청시간)
    bResult = StTaskGetHandlingTime(task);
    if (bResult == false) goto lb_return;   //0이하의 값이 나온 경우

    completeQue.push(task);

    bResult = true;

lb_return:
    return bResult;
}

/*
    [리턴]
    RequestQueue.size() < 0 : false (한 일이 없다)
    RequestQueue.size() > 0 : true 

    [내용]
    input보다 작은 RequestTime을 갖는 RequestQue의 값들을 모두 DurationQue에 넣는다.
*/
bool SolutionRequestToDurationUnderInputTime(RequestQueue& start, DurationQueue& end, int input)
{
    bool bResult = false;
    int cutLine = input;
    int requestTime = 0;
    RequestQueue& requests = start;
    DurationQueue& durations = end;
    
    if (requests.size() == 0) goto lb_return;

    while (requests.top().requestTime <= cutLine)
    {
        stTask task = requests.top();
        requests.pop();
        durations.push(task);

        if (requests.size() == 0) 
            break;
    };

    if (durations.empty())
    {
        //아무 데이터도 넣지 못한 경우.
        //리퀘스트 최상단의 데이터를 넣는다.
        SolutionRequestToDuration(requests, durations);
    }

lb_return:
    return bResult;
}

/*
    [반환] 
        start.size() == 0 일 경우 false
        아니면 true;

    [목적]
    requestQue -> durationQue
    RequestQue의 최상단 데이터와 requestTime이 같은 모든 값은  DurationQue에 옮겨담는 함수

    [PARAMETER]
    RequestQueue    : requestTime으로 정렬된 우선순위 큐
    DurationQueue   : durationTime으로 정렬된 우선 순위 큐
*/
bool SolutionRequestToDuration(RequestQueue& start, DurationQueue& end)
{
    bool bResult = false;
    int fastestRequestTIme = 0;
    RequestQueue& requests = start;
    DurationQueue& durations = end;

    if (start.size() == 0) goto lb_return;
    
    fastestRequestTIme = requests.top().requestTime;
    while (fastestRequestTIme == requests.top().requestTime)
    {
        stTask task = requests.top();
        requests.pop();
        durations.push(task);
        if (requests.size() == 0) break;
    }
        
    bResult = true;

lb_return:
    return bResult;
}


/*
    [리턴]
    DurationQueue.size() == 0   : false
    DurationQueue.size() > 0    : true

    [내용]
    가장 작은 소요시간을 갖는 업무를 완료 큐로 이동
    
*/
bool SolutionDurationToComplete(DurationQueue& start, CompleteQueue& end)
{
    bool bResult = false;
    stTask task;
    
    if (start.size() == 0) goto lb_return;
    
    task = start.top();
    start.pop();

    //end.push(task);
    CompleteQueuePush(end, task);

lb_return:
    return bResult;
}

/*
    [리턴]
    completeQue.size() < 0 : false
    completeQue.size() > 0 : true

    [내용]
    완료큐에 들어있는 값들의 처리 시간의 평균을 구한다.

    [주의]
    / 연산을 사용하지만 결과물을 int형이다. (데이터 손실 가능성 존재) 
*/
bool SolutionGetAverageHandlingTime(int& out, CompleteQueue& completeQue)
{
    bool bResult = false;
    int sum = 0;
    size_t size = 0;
    size_t safeCount = 0;
    int average = 0;
    CompleteQueue& completes = completeQue;
    size = completes.size();

    if (size == 0) goto lb_return;

    while (completes.empty() == false)
    {
        sum += completes.front().handlingTime;
        completes.pop();
        safeCount++;

        if (safeCount > size)   //SIZE를 고정된 값(#DEFINE 등으로 정의하는 것도 고려할 것)
        {
            break;    //무한 루프 방지
        }
    }

    average = static_cast<int>(sum / size);
    out = average;

    bResult = true;
lb_return:
    return bResult;
}

int main()
{
    //return 9
    //vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6} };

    //vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6}, {2, 3}, {4, 1}, {15, 6} };

    //vector<vector<int>> jobs = { {0, 4}, {0, 3}, {0, 2} };

    //6
    //vector<vector<int>> jobs = { {0, 5},{1, 2},{5, 5} };
    
    //72
    //vector<vector<int>> jobs = { {24, 10},{28, 39},{43, 20},{37, 5},{47, 22},{20, 47},{15, 34},{15, 2},{35, 43},{26, 1} };

    //
    vector<vector<int>> jobs = { {0, 5},{2, 10}, {1000000000, 2} };
        
    int result = solution(jobs);
     
    printf("평균 처리 시간은  : %d 입니다.\n", result);

    return 0;
}
