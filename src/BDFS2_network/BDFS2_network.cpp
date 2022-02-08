/*
    컴퓨터가 n개에 대한 열결 정보가 이차원 배열로 주어질때, 네트워크 갯수를 return 하시오
    
    [제한사항]
    computer : 연결시 1, 미연결시 0 (vector<vecotr<int>)
    n        : 컴퓨터 개수 1 ~ 200
    i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면
    computer[i][j]를 1로 표시한다.
    
                n   computer                            return
    case 1.     3	[[1, 1, 0], [1, 1, 0], [0, 0, 1]]	2
    case 2.     3	[[1, 1, 0], [1, 1, 1], [0, 1, 1]]	1


    [case 1]
    [1]
     |
    [2]   [3]

    return 2 ( 2개의 네트워크 존재 : (1,2), (3))


    [case 2]
    [1]
     |
    [2] - [3]

    return 1 ( 1개의 네트워크 존재 : (1, 2, 3) )

*/

/*
    [solution]
    1. computer의 0번 인덱스부터 작업 대기열에 넣는다.(단, 이미 완료된 컴퓨터는 스킵)
    2. 작업대기열의 한개 꺼내서 검사
    3. 작업대기열에서 꺼낸 컴퓨터는 검사 완료 셋에 넣는다.
    3. 검사 중, 연결된 네트워크는 작업 대기열에 넣는다.
    4. 작업대기열이 빌때까지 반복.
    5. 작업대기열이 비었을 경우 network count + 1
        -> 검사하지 않은 컴퓨터를 꺼내 검사
    6. 모든 computer가 검사가 완료 될때까지 반복

*/

/*
    [개선?]
    만약 각 네트워크가 어느 그룹 소속인지 표시하고 싶을 경우
    CompleteSet을 Set이 아닌 map을 이용하여, value값에 그룹 인덱스를 같이 저장할 것.

*/

#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

//이름 바꿀 것.
struct stNetworkChecker
{
    set<int> completeSet;   //검사가 완료된 인덱스   ->
    queue<int> workQue;     //작업 대기열
};

//network class
bool networkIsComplete(stNetworkChecker& network, int index);
bool networkWorkQueEmpty(stNetworkChecker& network);
bool netwrokInsertInWorkQue(stNetworkChecker& network, int index);


int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    int networkCount = 0;

    stNetworkChecker network;

    int index = -1;
    for (auto& computer : computers)
    {
        index++;
        
        //작업대기열에 추가.
        bool bIsInsert = netwrokInsertInWorkQue(network, index);
        if (bIsInsert == true)
        {
            //대기열에 추가 
            networkCount++;     //새로운 네트워크 감지
        }
        else
        {
            //추가하지 않았다? -> 이미 검사한 인덱스 패스
            continue;
        }


        //작업대기열이 빌때까지 반복 -> 함수화 하면 좋은 부분. 오늘은 패스한다.
        while ( networkWorkQueEmpty(network) == false)
        {
            queue<int>& workQue = network.workQue;
            set<int>& completeSet = network.completeSet;
            int comIndex = workQue.front();             //가장 앞의 값 검사 
            workQue.pop();
            completeSet.insert(comIndex);               //완료셋에 넣는다.
            vector<int>& com = computers.at(comIndex);  //해당 인덱스의 네트워크 상황 불러오기
            
            //네트워크 연결 현황 검사.
            size_t size = com.size();
            for (size_t i = 0; i < size; i++)
            {
                int isConnected = com.at(i);
                if (isConnected == 1)
                {
                    netwrokInsertInWorkQue(network, i);
                }
            }
        }
        
    }

    answer = networkCount;

    return answer;
}



/*
    @return 이미 검사한 네트워크일 경우 true 리턴 
    @detail 네트워크 검사가 완료된 인덱스인지 확인
*/
bool networkIsComplete(stNetworkChecker& network, int index)
{
    bool bIsExist = false;
    set<int>& completeSet = network.completeSet;
    set<int>::iterator it = completeSet.find(index);

    if (it != completeSet.end())
    {
        bIsExist = true;
    }

    return bIsExist;
}

/*
    @return 대기열이 비어있을 경우 리턴 true
    @detail 대기열이 비어있는지 검사 
*/
bool networkWorkQueEmpty(stNetworkChecker& network)
{
    return network.workQue.empty();
}


/*
    @return 작업대기열에 추가 시, 리턴 true
    @detail 작업대기열에 추가. 이미 네트워크 탐색이 완료된 컴퓨터는 추가되지 않는다. 
*/
bool netwrokInsertInWorkQue(stNetworkChecker& network, int index)
{
    bool bSuccess = false;  //insert 성공시, true
    bool bIsComplete = networkIsComplete(network, index);
    
    if (bIsComplete == false)
    {
        //네트워크 탐색이 완료된 컴퓨터 인덱스가 아니다. -> 대기열에 추가한다.
        network.workQue.push(index);
        bSuccess = true;
    }

    return bSuccess;
}



int main()
{
    //reteurn 2
    int n = 3;
    vector<vector<int>> computers = { {1, 1, 0}, { 1, 1, 0 }, { 0, 0, 1 }};

    //return 1
    /*int n = 3; 
    vector<vector<int>> coumputers = { {1, 1, 0},{1, 1, 1},{0, 1, 1} };
    */

    int result = solution(n, computers);

//    printf("네트워크 수 : %d\n", result);


    return 0;
}