
/*
    [가장 먼 노드]
    1번 노드로부터 가장 먼 노드가 몇개인지 리턴하시오

    n개의 노드가 존재한다.
    노드들의 관계는 vertex를 통해 표현(vector<vector<int>>)
    노드와 노드 사이의 가중치는 각 1로 동일하다.
    가장 먼 노드는 최단 노드로 이동할 때, 간선 수가 가장 많은 노드들을 의미한다.


*/

/*
    [제한사항]
    n : 2 ~ 20000
    vertex.size : 1 ~ 50000
    vertex [a, b]의 의미는 a와 b사이에 간선이 존재한다는 뜻
*/


/*
    [sample]
    node    vertex                                                      return  
    6	    [[3, 6], [4, 3], [3, 2], [1, 3], [1, 2], [2, 4], [5, 2]]	3

    [그림]
    1---2---5
    |   |
    |   |
    3---4
    |
    |
    6

*/

/*
    [solution]
    1. node 수 만큼 메모리 할당
    2. vertex를 바탕으로 근접 리스트 갱신
    3. 첫번째 노드의 근접 노드 큐에 저장. + 거리저장소 업데이트
    4. 큐에 들어간 노드 꺼내며 인접리스트의 거리 업데이트
    5. 큐가 빌때까지 반복.

    /! 인접행렬이 없는 노드 있을 수 있다. !/  -> 초기값을 -1로 처리하여 해결할 예정.

    [필요]
    n개의 배열 : 각 노드별 거리 저장용(초기화 -1) -> -1 결과가 나올 경우 1번 노드로 부터 연결이 없다는 것을 의미
    queue : 거리가 적용된 노드 저장. 다시 인접리스트를 꺼내기 위해.
    
*/


#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct node
{
    int id;
    set<int> adjacent;

    void AddAdjacent(int id)
    {
        if (id > 0)
        {
            adjacent.insert(id);
        }
    }
};

class nodeManager
{
public:
    ~nodeManager();
    bool Initailze(int n, vector<vector<int>>& edge);   //초기화
    node* GetNode(int id);
    bool UpdateDistance();
    int GetMaximumCount();

private:
    bool AddAdjacent(vector<int> edge);     //인접 노드 인덱스 추가 [a, b] 형태 
    bool UpdateDistanceNodeToNode(int start, int end);

private:
    int _nodeNum = 0;
    node* _pNode = nullptr;
    int* _pDistance = nullptr;
    queue<int> workQue;
    set<int> completeSet;
};

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    nodeManager* pManager = new nodeManager;
    bool bSuccess = pManager->Initailze(n, edge);
    if( !bSuccess )
    {
        //assert(false)
        printf("Fail to Init nodeManger\n");
    }

    //거리 정보 업데이트
    bSuccess = pManager->UpdateDistance();
    if (!bSuccess)
    {
        //이부분을 추가하니 core dumped
        delete pManager;
        pManager = nullptr;
    }
    
    //최대 거리 찾기 & 최대 거리 갯수 구하기
    answer = pManager->GetMaximumCount();
    
    //메모리 해제
    delete pManager;
    pManager = nullptr;

    return answer;
}



nodeManager::~nodeManager()
{
    if (_pNode != nullptr)
    {
        delete[] _pNode;
        _pNode = nullptr;
    }

    if (_pDistance != nullptr)
    {
        delete[] _pDistance;
        _pDistance = nullptr;
    }
}

bool nodeManager::Initailze(int n, vector<vector<int>>& edge)
{
    bool bResult = false;

    if (n < 0)
    {
        //잘못된 파라미터
        goto lb_return;
    }

    if (edge.size() == 0)
    {
        //잘못된 파라미터
        goto lb_return;
    }

    _nodeNum = n;
    _pNode = new node[_nodeNum];
    for (int i = 0; i < _nodeNum; i++)
    {
        static int count = 0;   //버퍼 오버런 방지.

        _pNode[i].id = i + 1;

        count++;
        if (_nodeNum < count)
        {
            //assert
            break;
        }
    }

    _pDistance = new int[_nodeNum];
    for (int i = 0; i < _nodeNum; i++)
    {
        _pDistance[i] = -1;
    }

    _pDistance[0] = 0;      //자기 자신

    //노드의 인접 리스트 갱신
    for (auto& it : edge)
    {
        AddAdjacent(it);
    }

    bResult = true;

lb_return:
    return bResult;
}

node* nodeManager::GetNode(int id)
{
    node* pNode = nullptr;
    if (id <= _nodeNum)
    {
        pNode = &_pNode[id - 1];
    }

    return pNode;
}

/*
    @detail id = 1인 노드로 부터 떨어진 거리 갱신. 1번 노드의 인접노드를 기준으로 업데이트 한다. 
    
*/
bool nodeManager::UpdateDistance()
{
    bool bResult = true;
    int safeCount = 0;
    workQue.push(1);

    while ( !workQue.empty() )
    {
        if (safeCount > 100000000)
        {
            //assert
            bResult = false;
            break;
        }

        int i = workQue.front();
        workQue.pop();
        completeSet.insert(i);      //완료 인덱스 계산 -> 더이상 계산하지 않는다?

        for (auto& it : _pNode[i - 1].adjacent)
        {
            if (completeSet.find(it) == completeSet.end())
            {
                workQue.push(it);
                UpdateDistanceNodeToNode(i - 1, it - 1);
            }
            
        }
        safeCount++;
    }

    return bResult;
}

/*
    @detail 거리의 최대값을 찾는다. 최대값과 동일한 값의 수를 리턴한다. -> 분리 고려
*/
int nodeManager::GetMaximumCount()
{
    int result = 0;
    int max = *max_element(_pDistance, _pDistance + _nodeNum);

    for (int i = 0; i < _nodeNum; i++)
    {
        if (_pDistance[i] == max)
        {
            result++;
        }
    }
    
    return result;
}

//인접 리스트 추가 
//param : [a, b] 형태 (int, int)
//a번 노드의 인접 리스트에 b추가,
//b번 노드의 인접 리스트에 a추가
bool nodeManager::AddAdjacent(vector<int> edge)
{
    bool bResult = true;
    if (edge.size() == 2)
    {
        int id1 = edge.at(0);
        int id2 = edge.at(1);
        //id 유효성 검사

        GetNode(id1)->AddAdjacent(id2);
        GetNode(id2)->AddAdjacent(id1);
    }
    else
    {
        bResult = false;
    }

    return bResult;
}

/*
    //우리는 1에서 node까지 거리만 구하면 된다.
    //배열에서 start까지의 거리를 찾는다.
    //_pDistance[start] + 1이 end까지 의 거리이다.
    //end의 인덱스에 거리를 갱신한다.(단, 기존값 보다 작아야 갱신한다.)
*/
bool nodeManager::UpdateDistanceNodeToNode(int start, int end)
{
    bool bResult = false;
    int prevDist = _pDistance[end]; //기존 경로
    int dist = _pDistance[start];
    if (dist < 0)
    {
        //-1인 경우
        dist = 0;
    }
    
    dist++;

    //새로운 디스트가 작으면
    if (prevDist < 0)
    {
        //같은 내용 고민 할 것.
        _pDistance[end] = dist;
        bResult = true;
    }
    else if (prevDist > dist)
    {
        //같은 내용 고민 할 것.
        _pDistance[end] = dist;
        bResult = true;
    }

    return bResult;
}


int main()
{
    int n = 6;
    vector<vector<int>> edge = { {3, 6}, {4, 3}, {3, 2},{ 1, 3 }, { 1, 2 }, { 2, 4 }, { 5, 2 } };

    int answer = solution(n, edge);

    printf("[RETURN] %d", answer);

    return 0;
}
