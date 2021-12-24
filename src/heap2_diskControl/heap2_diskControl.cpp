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
    [soltuion]
    1. 요청 큐에 요청 시간이 낮은 순 삽입
    2. 완료큐의 최상단에서 최상단 완료 시점 구하기
    3. 완료 시점 보다 작은 요청 시간을 갖는 모든 요청 시간을 모두 소요 시간큐에 넣기
        -> 단, 만족하는 조건이 없으면 요청큐 최상단값을 소요시간큐에 넣는다.(같은 요청값 모두)
    4. 소요큐의 최상단 값 pop()
    5. 완료시간 계산, 기록
    6. 완료큐로

    2 ~ 6 반복 (요청큐와 완료큐가 모두 빌때까지)


    
    [필요]    
    requestQue  : 요청 시간이 낮은순으로 정렬   (우선순위 큐)
    durationQue : 소요시간이 낮은순으로 정렬    (우선순위 큐)

    completedTask : 완료된 작업    (큐 or vector)


    [예측]
    1. 소요시간이 적은 업무를 우선 처리하는 편이 빠를 것이다.
    2. 처리하는 업무가 완료되는 시점을 계산한다.
    3. 처리되는 시간까지 들어온 요청 중, 소요시간이 가장 작은 순으로 처리한다.
    
    [주의]
    인티저를 나누기 연산하는 과정이 있다.

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

    stTask()  
    {
        requestTime = 0;
        duration = 0;
        completeTime = 0;
    }

    stTask(int request, int duration)
    {
        requestTime = request;
        this->duration = duration;
        completeTime = 0;
    }
};

struct orderByRequestTime
{
    bool operator()(stTask& a, stTask& b)
    {
        return a.requestTime > b.requestTime;
    }
};

struct orderByDuration
{
    bool operator()(stTask& a, stTask& b)
    {
        return a.duration > b.duration;
    }
};

typedef priority_queue<stTask, vector<stTask>, orderByRequestTime> RequestQueue;    //요청 시간 순으로 정렬되는 큐
typedef priority_queue<stTask, vector<stTask>, orderByDuration> DurationQueue;      //소요 시간 순으로 정렬되는 큐
typedef queue<stTask> CompleteQueue;

bool RequestQueueInitialize(RequestQueue& out, vector<vector<int>>& src);



int solution(vector<vector<int>> jobs) {
    int answer = 0;
    RequestQueue requestQue;
    DurationQueue durationQue;
    CompleteQueue completeQue;
    bool bSuccess = false;

    bSuccess = RequestQueueInitialize(requestQue, jobs);

    //loop
    //완료큐의 최상단 완료시간 시간 보다 작은 리퀘스트 시간을 모두 듀레이션큐에 넣는다.
    //단, 완료큐가 비어있으면 리퀘스트큐 최상단 값 듀레이션 큐에 넣는다.
    // 리퀘스트 큐가 비어 있다면 지나간다.
    //
    
    return answer;
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








int main()
{
    //return 9
    vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6} };

    int result = solution(jobs);
     
    printf("평균 처리 시간은  : %d 입니다.", result);

    return 0;
}
