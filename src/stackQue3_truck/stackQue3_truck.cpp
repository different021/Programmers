/*
    [parameter]
    int bridge_length
    int weight
    vector<int> truct_weight

    [return]
    int걸린 총 시간


    [문제]
    주어진 배열의 차량들이 통과하는데 걸리는 시간을 구하라.

    트럭이 통과하는데는 BRIGDE_LENGTH만큼의 시간이 걸린다
    다리에 들어갈 수 있는 최대량은 BRIDGE_LENGTH , WEIGHT 값과 관련이 있다.
    BRIDGE_LENGTH 보다 많은 차량이 올라 갈수 없다.
    WEIGHT 보다 무겁게 올라갈 수 없다.

    [제한]
    BRIDGE_LENGTH       : 1 ~ 10000
    WEIGTH              : 1 ~ 10000
    TRUCK_WEIGTH.SIZE() : 1 ~ 10000
    TRUCK_WEIGHT        : < WEIGTH  (트럭 한대의 무게는 다리가 감당할 수 있는 하중 보다 작다. -> 적어도 한대는 무조건 통과 가능하다.)


    [예시]
    BRIDGE_LENGTH   : 2
    WEIGTH          : 10
    TRUCK_WEIGTH    : [7, 4, 5, 6]

    시간     통과한 트럭   건너는 중     건너기 전
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
    //private 필드
    int bridge_length;
    int maxWeight;
    int curWeight;

    //두개를 묶는 편이? 
    //트럭이 진입한 시간을 입력. 현재 시간과 비교를 통해 진행도 측정
    queue<int>  passingTruck;       //다리위의 트럭들
    vector<int> progress;           //다리위 트럭들의 진행도
};

//bridge class
bool BridgeInitialize(stBRIDGE& bridge, int bridge_length, int weight);     //브릿지 초기화
bool BridgePush(stBRIDGE& bridge, int Truckweight);                         //브릿지를 지나가는 차량 추가
bool BridgePop(stBRIDGE& bridge, int* pOut = nullptr);
bool BridgeIncreaseProgress(stBRIDGE& bridge);
bool BridgeCheckComplete(stBRIDGE& bridge);

//solution class
bool SolutionPassBridge(stBRIDGE& bridge, vector<int>* pPassed = nullptr);
bool SolutionEnterBridge(stBRIDGE& bridge, vector<int>& waiting);

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    vector<int> passedTruck;    //성능 문제시 제거
    stBRIDGE bridge;
    int timeCounter = 0;
    
    BridgeInitialize(bridge, bridge_length, weight);    //다리 변수 초기화
    passedTruck.reserve(truck_weights.size());          //성능 문제시 제거

    do
    {
        if (timeCounter > REQUEST_TIME_OUT)
        {
            //논리적 도달 불가능한 카운터에 도달
            break;
        }

        //1. 트럭이 다리를 통과함
        SolutionPassBridge(bridge, &passedTruck);
        
        //2. 트럭이 다리에 진입함
        SolutionEnterBridge(bridge, truck_weights);

        //3. 진행도 증가
        BridgeIncreaseProgress(bridge);

        //4. 걸린 시간 (return value)
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

//다리에 트럭 추가
//다리의 상황에 따라서 진입하지 않을 수 있다. (다리 최대 길이, 다리 최대 허용 무게)
bool BridgePush(stBRIDGE& bridge, int Truckweight)
{
    bool bResult = false;
    //push 가능여부 검사.
    if (bridge.passingTruck.size() >= bridge.bridge_length) goto lb_return;     //최대 수용량 검사
    if ((bridge.curWeight + Truckweight) > bridge.maxWeight) goto lb_return;    //최대 무게 검사

    //PUSH 가능
    bridge.passingTruck.push(Truckweight);
    bridge.curWeight += Truckweight;
    bridge.progress.push_back(0);              //새로 진입한 차량의 진행도(0)
    bResult = true;

lb_return:
    return bResult;
}

bool BridgePop(stBRIDGE& bridge, int* pOut)
{
    bool isPop = false;
    int weigth = 0;
    int progress = 0;
    //팝이 가능한지 검사 
    bool isEmpty = bridge.passingTruck.empty();
    if ( isEmpty ) goto lb_return;

    //팝가능한 경우
    weigth = bridge.passingTruck.front();
    progress = bridge.progress.front();

    if (progress < bridge.bridge_length) goto lb_return;    //첫번째 차가 아직 끝에 도달하지 못했다.

    bridge.curWeight -= weigth;                       //차량 무게 만큼 제거
    bridge.passingTruck.pop();
    bridge.progress.erase( bridge.progress.begin() ); //times도 제거해야된다.

    if (bridge.passingTruck.size() != bridge.progress.size())
    {
        //예외 처리 추가
        //둘의 사이즈는 다를 수 없다.
    }

    if (pOut != nullptr)
    {
        //현재 팝된 값이 필요할 경우
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

//다리위에 아무 것도 없는지 확인 하는 함수
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

    //진행도 체크 후 다리에서 제거
    bool bPop = BridgePop(bridge, &passedTruckWeight);
    if (bPop == true)
    {
        //제거된 트럭 완료된 리스트에 추가 -> 이 문제에서는 안해도 된다. -> 성능 문제시 제거
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

    //대기 차량이 남아있을 경우 다리에 진입
    if (waiting.size() > 0)
    {
        it = waiting.begin();
        value = *it;

        bool bPush = BridgePush(bridge, value);
        if (bPush == true)
        {
            //트럭 추가(다리에)
            //대기중인 차량 제거
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

    printf("총 소요 시간은 %d 초 입니다.", result);

    return 0;
}