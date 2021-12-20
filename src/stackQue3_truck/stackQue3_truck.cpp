/*
    [parameter]
    int bridge_length
    int weight
    vector<int> truct_weight

    [return]
    int�ɸ� �� �ð�


    [����]
    �־��� �迭�� �������� ����ϴµ� �ɸ��� �ð��� ���϶�.

    Ʈ���� ����ϴµ��� BRIGDE_LENGTH��ŭ�� �ð��� �ɸ���
    �ٸ��� �� �� �ִ� �ִ뷮�� BRIDGE_LENGTH , WEIGHT ���� ������ �ִ�.
    BRIDGE_LENGTH ���� ���� ������ �ö� ���� ����.
    WEIGHT ���� ���̰� �ö� �� ����.

    [����]
    BRIDGE_LENGTH       : 1 ~ 10000
    WEIGTH              : 1 ~ 10000
    TRUCK_WEIGTH.SIZE() : 1 ~ 10000
    TRUCK_WEIGHT        : < WEIGTH  (Ʈ�� �Ѵ��� ���Դ� �ٸ��� ������ �� �ִ� ���� ���� �۴�. -> ��� �Ѵ�� ������ ��� �����ϴ�.)


    [����]
    BRIDGE_LENGTH   : 2
    WEIGTH          : 10
    TRUCK_WEIGTH    : [7, 4, 5, 6]

    �ð�     ����� Ʈ��   �ǳʴ� ��     �ǳʱ� ��
    0	        []	        []	        [7,4,5,6]
    1~2	        []	        [7]	        [4,5,6]
    3	        [7]	        [4]	        [5,6]
    4	        [7]	        [4,5]	    [6]
    5	        [7,4]	    [5]	        [6]
    6~7	        [7,4,5]	    [6]	        []
    8	        [7,4,5,6]	[]	        []

    RETURN 8;


    bridge_length	weight	truck_weights	                    return
    2	            10	    [7,4,5,6]	                        8
    100	            100	    [10]	                            101
    100	            100	    [10,10,10,10,10,10,10,10,10,10]	    110

*/


/*
    [Logic]
    1. push in bridge (if bridge can)
    2. pop  form bridge (max progress in bridge)
    3. increase every truck's progress in bridge (trucks in bridge)
    4. increase TimeCounter (return value, total time of passing the bridge in parameter)

    loop() 
       1 ~ 4 untiil bridge is Empty


    [weak point]
    It will be slow,
    when so many trucks in vector

    Because this logic will count every sigle time count
*/

#include <string>
#include <vector>
#include <queue>

#define TRUCK_WEIGTH_MAX  10000
#define BRIDGE_LENGTH_MAX 10000
#define BRIDGE_WEIGTH_MAX 10000

#define REQUEST_TIME_OUT  100000000

using namespace std;

struct stBRIDGE
{
    //private �ʵ�
    int bridge_length;
    int maxWeight;
    int curWeight;

    //�ΰ��� ���� ����? 
    //Ʈ���� ������ �ð��� �Է�. ���� �ð��� �񱳸� ���� ���൵ ����
    queue<int>  passingTruck;       //�ٸ����� Ʈ����
    vector<int> progress;           //�ٸ��� Ʈ������ ���൵
};

//bridge class
bool BridgeInitialize(stBRIDGE& bridge, int bridge_length, int weight);     //�긴�� �ʱ�ȭ
bool BridgePush(stBRIDGE& bridge, int Truckweight);                         //�긴���� �������� ���� �߰�
bool BridgePop(stBRIDGE& bridge, int* pOut = nullptr);
bool BridgeIncreaseProgress(stBRIDGE& bridge);
bool BridgeCheckComplete(stBRIDGE& bridge);

//solution class
bool SolutionPassBridge(stBRIDGE& bridge, vector<int>* pPassed = nullptr);
bool SolutionEnterBridge(stBRIDGE& bridge, vector<int>& waiting);

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    vector<int> passedTruck;    //���� ������ ����
    stBRIDGE bridge;
    int timeCounter = 0;
    
    BridgeInitialize(bridge, bridge_length, weight);    //�ٸ� ���� �ʱ�ȭ
    passedTruck.reserve(truck_weights.size());          //���� ������ ����

    do
    {
        if (timeCounter > REQUEST_TIME_OUT)
        {
            //���� ���� �Ұ����� ī���Ϳ� ����
            break;
        }

        //1. Ʈ���� �ٸ��� �����
        SolutionPassBridge(bridge, &passedTruck);
        
        //2. Ʈ���� �ٸ��� ������
        SolutionEnterBridge(bridge, truck_weights);

        //3. ���൵ ����
        BridgeIncreaseProgress(bridge);

        //4. �ɸ� �ð� (return value)
        timeCounter++;

    } while ( !BridgeCheckComplete(bridge) );

    //return value
    answer = timeCounter;

    return answer;
}

bool BridgeInitialize(stBRIDGE& bridge, int bridge_length, int weight)
{
    bool bResult = false;
    if (bridge_length > BRIDGE_LENGTH_MAX) goto lb_return;
    if (weight > BRIDGE_WEIGTH_MAX) goto lb_return;

    bridge.maxWeight     = weight;
    bridge.bridge_length = bridge_length;
    bridge.curWeight     = 0;
    bResult = true;

lb_return:
    return bResult;
}

//�ٸ��� Ʈ�� �߰�
//�ٸ��� ��Ȳ�� ���� �������� ���� �� �ִ�. (�ٸ� �ִ� ����, �ٸ� �ִ� ��� ����)
bool BridgePush(stBRIDGE& bridge, int Truckweight)
{
    bool bResult = false;
    //push ���ɿ��� �˻�.
    if (bridge.passingTruck.size() >= bridge.bridge_length) goto lb_return;     //�ִ� ���뷮 �˻�
    if ((bridge.curWeight + Truckweight) > bridge.maxWeight) goto lb_return;    //�ִ� ���� �˻�

    //PUSH ����
    bridge.passingTruck.push(Truckweight);
    bridge.curWeight += Truckweight;
    bridge.progress.push_back(0);              //���� ������ ������ ���൵(0)
    bResult = true;

lb_return:
    return bResult;
}

bool BridgePop(stBRIDGE& bridge, int* pOut)
{
    bool isPop = false;
    int weigth = 0;
    int progress = 0;
    //���� �������� �˻� 
    bool isEmpty = bridge.passingTruck.empty();
    if ( isEmpty ) goto lb_return;

    //�˰����� ���
    weigth = bridge.passingTruck.front();
    progress = bridge.progress.front();

    if (progress < bridge.bridge_length) goto lb_return;    //ù��° ���� ���� ���� �������� ���ߴ�.

    bridge.curWeight -= weigth;                       //���� ���� ��ŭ ����
    bridge.passingTruck.pop();
    bridge.progress.erase( bridge.progress.begin() ); //times�� �����ؾߵȴ�.

    if (bridge.passingTruck.size() != bridge.progress.size())
    {
        //���� ó�� �߰�
        //���� ������� �ٸ� �� ����.
    }

    if (pOut != nullptr)
    {
        //���� �˵� ���� �ʿ��� ���
        *pOut = weigth;
    }

    isPop = true;

lb_return:
    return isPop;
}

//
bool BridgeIncreaseProgress(stBRIDGE& bridge)
{
    bool bExistPassed = false;
    if (bridge.progress.empty()) goto lb_return;

    for (auto& it : bridge.progress)
    {
        it++;
    }

lb_return:
    return bExistPassed;
}

//�ٸ����� �ƹ� �͵� ������ Ȯ�� �ϴ� �Լ�
bool BridgeCheckComplete(stBRIDGE& bridge)
{
    bool bComplete = false;

    if (bridge.passingTruck.size() > 0) goto lb_return;
    if (bridge.progress.size() > 0) goto lb_return;

    bComplete = true;

lb_return:
    return bComplete;
}

bool SolutionPassBridge(stBRIDGE& bridge, vector<int>* pPassed )
{
    int passedTruckWeight = 0;

    //���൵ üũ �� �ٸ����� ����
    bool bPop = BridgePop(bridge, &passedTruckWeight);
    if (bPop == true)
    {
        //���ŵ� Ʈ�� �Ϸ�� ����Ʈ�� �߰� -> �� ���������� ���ص� �ȴ�. -> ���� ������ ����
        if (pPassed != nullptr)
        {
            pPassed->push_back(passedTruckWeight);
        }
    }

    return bPop;
}

bool SolutionEnterBridge(stBRIDGE& bridge, vector<int>& waiting)
{
    bool bResult = false;
    vector<int>::iterator it;
    int value = 0;

    //��� ������ �������� ��� �ٸ��� ����
    if (waiting.size() > 0)
    {
        it = waiting.begin();
        value = *it;

        bool bPush = BridgePush(bridge, value);
        if (bPush == true)
        {
            //Ʈ�� �߰�(�ٸ���)
            //������� ���� ����
            it = waiting.erase(it);
        }

        bResult = true;
    }

    return bResult;
}

int main()
{
    //int bridge_length = 2;
    //int weigth = 10;
    //vector<int> truck_weights = { 7, 4, 5, 6 };
    ////return 8;
    
    int bridge_length = 100;
    int weigth = 100;
    vector<int> truck_weights = { 10,10,10,10,10,10,10,10,10,10 };
    //return 110;
    
    //int bridge_length = 100;
    //int weigth = 100;
    //vector<int> truck_weights = { 10 };
    ////return 101;

    int result = solution(bridge_length, weigth, truck_weights);

    printf("�� �ҿ� �ð��� %d �� �Դϴ�.", result);

    return 0;
}