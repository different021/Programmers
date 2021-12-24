/*
    ��ũ�� �ѹ��� �Ѱ��� �� �ۿ� ���� ���Ѵ�.
    ��ũ�� 2���� �迭 ���·� ������ ���´�.
    { ��û ����(int), �ҿ�ð�(int) }

    ���� ���,
    A : 0�� ��û, 3�� �ҿ�
    B : 1�� ��û, 9�� �ҿ�
    C : 2�� ��û, 6�� �ҿ�

    �� ��û�� A, B, C������ ó���ϸ�,

    A : 0�� ��û, 0�� ����, 3�� ���� = 3��
    B : 1�� ��û, 3�� ����, 12�� ���� = 11��
    C : 2�� ��û, 12�� ����, 18�� ���� = 16��

    ���ó�� �ð���,
    ���ó���ð� = ( 3 + 11 + 16) / 3
    ó������ ABC�϶�,
    10�ʰ� ���´�.

    ������ A, C, B ������ ó���ϸ�,

    A : 0�� ��û, 0�� ����, 3�� ���� = 3��
    C : 2�� ��û, 3�� ����, 9�� ���� = 7��
    B : 1�� ��û, 9�� ����, 18�� ���� = 17��

    ��� ó���ð� = (3 + 7 + 17) / 3
    9�ʰ� ������ �ȴ�.

    [�Ķ����]
    vector<vector<int>> (��û�ð�, ó���ð�) 2���� �迭

    [����]
    ���� ���� ��� ó�� �ð�

    [���� ����]
    jobs.size() : 1 ~ 500
    ��û �ð� : 0 ~ 1000
    �ҿ� �ð� : 1 ~ 1000
    ������ �������� ���� ������.
*/


/*
    [Simple LOGIC]
    jobs -> requestQue
    while()
    {
        requestQue -> DurationQue
        DurationQue -> CompleteQue
    }


    [���� ����]
    1. requestQue.size() == 0;
    2. drationQue.size() == 0;
    (1 & 2) �� ��� ���϶� �ַ�� ����
    
    [soltuion]
    1. requestQueue�� ��û �ð��� ���� ������ �����ؼ� ����ִ´�.
    
    2.
    �ҿ�ð� �켱����ť�� ������ �����?
       (���� ���� ��û�ð��� �ִ´�.)   <- ���Ϸ���a
       
    �ҿ�ð� ť�� ���� �ʾҴ�?
        �Ϸ�ð��� ã�� �׺��� ���� ��û�ð��� ��� �ִ´�.
        ���ٸ� (���� ���� ��û�ð��� �ִ´�.) <- ���Ϸ���a
    
    3. �ҿ�ð� ť�� �ּҰ��� �Ϸ�ť�� �̵� (�̶�, �Ϸ�ð��� ó���ð� ���)

    4. ��� �ҿ� �ð��� ���Ѵ�. sum(ó���ð��ѷ�) /  size 

    [�ʿ�]    
    requestQue  : ��û �ð��� ���������� ����   (�켱���� ť)
    durationQue : �ҿ�ð��� ���������� ����    (�켱���� ť)

    completedTask : �Ϸ�� �۾�    (ť or vector)


    [����]
    1. �ҿ�ð��� ���� ������ �켱 ó���ϴ� ���� ���� ���̴�.
    2. ó���ϴ� ������ �Ϸ�Ǵ� ������ ����Ѵ�.
    3. ó���Ǵ� �ð����� ���� ��û ��, �ҿ�ð��� ���� ���� ������ ó���Ѵ�.
    
    [����]
    ��Ƽ���� ������ �����ϴ� ������ �ִ�. -> ....

*/


#include <string>
#include <vector>
#include <queue>

using namespace std;

struct stTask
{
    int requestTime;    //��û�ð�
    int duration;       //�ҿ�ð�
    int completeTime;   //�Ϸ�ð�
    int handlingTime;   //ó���ð�

    //������1 
    stTask()  
    {
        requestTime = 0;
        duration = 0;
        completeTime = 0;
        handlingTime = 0;
    }

    //������2
    stTask(int request, int duration)
    {
        requestTime     = request;
        this->duration  = duration;
        completeTime    = 0;
        handlingTime = 0;
    }
};

//��û �ð��� ������ ����
struct orderByRequestTime
{
    bool operator()(stTask& a, stTask& b)
    {
        return a.requestTime > b.requestTime;
    }
};

//�ҿ� �ð� ������ ����
struct orderByDuration
{
    bool operator()(stTask& a, stTask& b)
    {
        bool bResult = false;
        if (a.duration > b.duration)
        {
            //�ҿ�ð��� ������ ����
            bResult = true;
        }
        else if (a.duration == b.duration)
        {
            if (a.requestTime > b.requestTime)
            {
                //��û �ð��� ������ ���� 
                bResult = true;
            }
        }

        return bResult;
    }
};

typedef priority_queue<stTask, vector<stTask>, orderByRequestTime> RequestQueue;    //��û �ð� ������ ���ĵǴ� ť
typedef priority_queue<stTask, vector<stTask>, orderByDuration> DurationQueue;      //�ҿ� �ð� ������ ���ĵǴ� ť
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
        
        //duration -> complete (completeTime, handlingTime ���)
        SolutionDurationToComplete(durationQue, completeQue);

    }
     
    SolutionGetAverageHandlingTime(answer, completeQue);

    return answer;
}

/*
    [����]
    ���(< 0) : false (���� �Ұ���)
    ����(> 0) : true  (�������� �����Ǵ� ��)
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
    if (src.size() == 0) goto lb_return;    //�� �迭

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
        //�Ϸ�ť�� �ֻ�� 
        pastCompleteTime = (completeQue.back().completeTime > task.requestTime) ? completeQue.back().completeTime : task.requestTime;
    }
    else
    {
        pastCompleteTime = task.requestTime;
    }

    //�� �۾��� �Ϸ� �ð� = ������ �Ϸ� �ð� + �ҿ�ð�
    task.completeTime = pastCompleteTime + task.duration;

    //ó���ð� ���ϱ�(�Ϸ�ð� - ��û�ð�)
    bResult = StTaskGetHandlingTime(task);
    if (bResult == false) goto lb_return;   //0������ ���� ���� ���

    completeQue.push(task);

    bResult = true;

lb_return:
    return bResult;
}

/*
    [����]
    RequestQueue.size() < 0 : false (�� ���� ����)
    RequestQueue.size() > 0 : true 

    [����]
    input���� ���� RequestTime�� ���� RequestQue�� ������ ��� DurationQue�� �ִ´�.
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
        //�ƹ� �����͵� ���� ���� ���.
        //������Ʈ �ֻ���� �����͸� �ִ´�.
        SolutionRequestToDuration(requests, durations);
    }

lb_return:
    return bResult;
}

/*
    [��ȯ] 
        start.size() == 0 �� ��� false
        �ƴϸ� true;

    [����]
    requestQue -> durationQue
    RequestQue�� �ֻ�� �����Ϳ� requestTime�� ���� ��� ����  DurationQue�� �Űܴ�� �Լ�

    [PARAMETER]
    RequestQueue    : requestTime���� ���ĵ� �켱���� ť
    DurationQueue   : durationTime���� ���ĵ� �켱 ���� ť
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
    [����]
    DurationQueue.size() == 0   : false
    DurationQueue.size() > 0    : true

    [����]
    ���� ���� �ҿ�ð��� ���� ������ �Ϸ� ť�� �̵�
    
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
    [����]
    completeQue.size() < 0 : false
    completeQue.size() > 0 : true

    [����]
    �Ϸ�ť�� ����ִ� ������ ó�� �ð��� ����� ���Ѵ�.

    [����]
    / ������ ��������� ������� int���̴�. (������ �ս� ���ɼ� ����) 
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

        if (safeCount > size)   //SIZE�� ������ ��(#DEFINE ������ �����ϴ� �͵� ����� ��)
        {
            break;    //���� ���� ����
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
     
    printf("��� ó�� �ð���  : %d �Դϴ�.\n", result);

    return 0;
}
