
/*
    [���� �� ���]
    1�� ���κ��� ���� �� ��尡 ����� �����Ͻÿ�

    n���� ��尡 �����Ѵ�.
    ������ ����� vertex�� ���� ǥ��(vector<vector<int>>)
    ���� ��� ������ ����ġ�� �� 1�� �����ϴ�.
    ���� �� ���� �ִ� ���� �̵��� ��, ���� ���� ���� ���� ������ �ǹ��Ѵ�.


*/

/*
    [���ѻ���]
    n : 2 ~ 20000
    vertex.size : 1 ~ 50000
    vertex [a, b]�� �ǹ̴� a�� b���̿� ������ �����Ѵٴ� ��
*/


/*
    [sample]
    node    vertex                                                      return  
    6	    [[3, 6], [4, 3], [3, 2], [1, 3], [1, 2], [2, 4], [5, 2]]	3

    [�׸�]
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
    1. node �� ��ŭ �޸� �Ҵ�
    2. vertex�� �������� ���� ����Ʈ ����
    3. ù��° ����� ���� ��� ť�� ����. + �Ÿ������ ������Ʈ
    4. ť�� �� ��� ������ ��������Ʈ�� �Ÿ� ������Ʈ
    5. ť�� �������� �ݺ�.

    /! ��������� ���� ��� ���� �� �ִ�. !/  -> �ʱⰪ�� -1�� ó���Ͽ� �ذ��� ����.

    [�ʿ�]
    n���� �迭 : �� ��庰 �Ÿ� �����(�ʱ�ȭ -1) -> -1 ����� ���� ��� 1�� ���� ���� ������ ���ٴ� ���� �ǹ�
    queue : �Ÿ��� ����� ��� ����. �ٽ� ��������Ʈ�� ������ ����.
    
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
    bool Initailze(int n, vector<vector<int>>& edge);   //�ʱ�ȭ
    node* GetNode(int id);
    bool UpdateDistance();
    int GetMaximumCount();

private:
    bool AddAdjacent(vector<int> edge);     //���� ��� �ε��� �߰� [a, b] ���� 
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

    //�Ÿ� ���� ������Ʈ
    bSuccess = pManager->UpdateDistance();
    if (!bSuccess)
    {
        //�̺κ��� �߰��ϴ� core dumped
        delete pManager;
        pManager = nullptr;
    }
    
    //�ִ� �Ÿ� ã�� & �ִ� �Ÿ� ���� ���ϱ�
    answer = pManager->GetMaximumCount();
    
    //�޸� ����
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
        //�߸��� �Ķ����
        goto lb_return;
    }

    if (edge.size() == 0)
    {
        //�߸��� �Ķ����
        goto lb_return;
    }

    _nodeNum = n;
    _pNode = new node[_nodeNum];
    for (int i = 0; i < _nodeNum; i++)
    {
        static int count = 0;   //���� ������ ����.

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

    _pDistance[0] = 0;      //�ڱ� �ڽ�

    //����� ���� ����Ʈ ����
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
    @detail id = 1�� ���� ���� ������ �Ÿ� ����. 1�� ����� ������带 �������� ������Ʈ �Ѵ�. 
    
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
        completeSet.insert(i);      //�Ϸ� �ε��� ��� -> ���̻� ������� �ʴ´�?

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
    @detail �Ÿ��� �ִ밪�� ã�´�. �ִ밪�� ������ ���� ���� �����Ѵ�. -> �и� ���
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

//���� ����Ʈ �߰� 
//param : [a, b] ���� (int, int)
//a�� ����� ���� ����Ʈ�� b�߰�,
//b�� ����� ���� ����Ʈ�� a�߰�
bool nodeManager::AddAdjacent(vector<int> edge)
{
    bool bResult = true;
    if (edge.size() == 2)
    {
        int id1 = edge.at(0);
        int id2 = edge.at(1);
        //id ��ȿ�� �˻�

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
    //�츮�� 1���� node���� �Ÿ��� ���ϸ� �ȴ�.
    //�迭���� start������ �Ÿ��� ã�´�.
    //_pDistance[start] + 1�� end���� �� �Ÿ��̴�.
    //end�� �ε����� �Ÿ��� �����Ѵ�.(��, ������ ���� �۾ƾ� �����Ѵ�.)
*/
bool nodeManager::UpdateDistanceNodeToNode(int start, int end)
{
    bool bResult = false;
    int prevDist = _pDistance[end]; //���� ���
    int dist = _pDistance[start];
    if (dist < 0)
    {
        //-1�� ���
        dist = 0;
    }
    
    dist++;

    //���ο� ��Ʈ�� ������
    if (prevDist < 0)
    {
        //���� ���� ��� �� ��.
        _pDistance[end] = dist;
        bResult = true;
    }
    else if (prevDist > dist)
    {
        //���� ���� ��� �� ��.
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
