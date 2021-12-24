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
    [soltuion]
    1. ��û ť�� ��û �ð��� ���� �� ����
    2. �Ϸ�ť�� �ֻ�ܿ��� �ֻ�� �Ϸ� ���� ���ϱ�
    3. �Ϸ� ���� ���� ���� ��û �ð��� ���� ��� ��û �ð��� ��� �ҿ� �ð�ť�� �ֱ�
        -> ��, �����ϴ� ������ ������ ��ûť �ֻ�ܰ��� �ҿ�ð�ť�� �ִ´�.(���� ��û�� ���)
    4. �ҿ�ť�� �ֻ�� �� pop()
    5. �Ϸ�ð� ���, ���
    6. �Ϸ�ť��

    2 ~ 6 �ݺ� (��ûť�� �Ϸ�ť�� ��� ��������)


    
    [�ʿ�]    
    requestQue  : ��û �ð��� ���������� ����   (�켱���� ť)
    durationQue : �ҿ�ð��� ���������� ����    (�켱���� ť)

    completedTask : �Ϸ�� �۾�    (ť or vector)


    [����]
    1. �ҿ�ð��� ���� ������ �켱 ó���ϴ� ���� ���� ���̴�.
    2. ó���ϴ� ������ �Ϸ�Ǵ� ������ ����Ѵ�.
    3. ó���Ǵ� �ð����� ���� ��û ��, �ҿ�ð��� ���� ���� ������ ó���Ѵ�.
    
    [����]
    ��Ƽ���� ������ �����ϴ� ������ �ִ�.

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

typedef priority_queue<stTask, vector<stTask>, orderByRequestTime> RequestQueue;    //��û �ð� ������ ���ĵǴ� ť
typedef priority_queue<stTask, vector<stTask>, orderByDuration> DurationQueue;      //�ҿ� �ð� ������ ���ĵǴ� ť
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
    //�Ϸ�ť�� �ֻ�� �Ϸ�ð� �ð� ���� ���� ������Ʈ �ð��� ��� �෹�̼�ť�� �ִ´�.
    //��, �Ϸ�ť�� ��������� ������Ʈť �ֻ�� �� �෹�̼� ť�� �ִ´�.
    // ������Ʈ ť�� ��� �ִٸ� ��������.
    //
    
    return answer;
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








int main()
{
    //return 9
    vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6} };

    int result = solution(jobs);
     
    printf("��� ó�� �ð���  : %d �Դϴ�.", result);

    return 0;
}
