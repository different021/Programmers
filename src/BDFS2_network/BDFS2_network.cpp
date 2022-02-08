/*
    ��ǻ�Ͱ� n���� ���� ���� ������ ������ �迭�� �־�����, ��Ʈ��ũ ������ return �Ͻÿ�
    
    [���ѻ���]
    computer : ����� 1, �̿���� 0 (vector<vecotr<int>)
    n        : ��ǻ�� ���� 1 ~ 200
    i�� ��ǻ�Ϳ� j�� ��ǻ�Ͱ� ����Ǿ� ������
    computer[i][j]�� 1�� ǥ���Ѵ�.
    
                n   computer                            return
    case 1.     3	[[1, 1, 0], [1, 1, 0], [0, 0, 1]]	2
    case 2.     3	[[1, 1, 0], [1, 1, 1], [0, 1, 1]]	1


    [case 1]
    [1]
     |
    [2]   [3]

    return 2 ( 2���� ��Ʈ��ũ ���� : (1,2), (3))


    [case 2]
    [1]
     |
    [2] - [3]

    return 1 ( 1���� ��Ʈ��ũ ���� : (1, 2, 3) )

*/

/*
    [solution]
    1. computer�� 0�� �ε������� �۾� ��⿭�� �ִ´�.(��, �̹� �Ϸ�� ��ǻ�ʹ� ��ŵ)
    2. �۾���⿭�� �Ѱ� ������ �˻�
    3. �۾���⿭���� ���� ��ǻ�ʹ� �˻� �Ϸ� �¿� �ִ´�.
    3. �˻� ��, ����� ��Ʈ��ũ�� �۾� ��⿭�� �ִ´�.
    4. �۾���⿭�� �������� �ݺ�.
    5. �۾���⿭�� ����� ��� network count + 1
        -> �˻����� ���� ��ǻ�͸� ���� �˻�
    6. ��� computer�� �˻簡 �Ϸ� �ɶ����� �ݺ�

*/

/*
    [����?]
    ���� �� ��Ʈ��ũ�� ��� �׷� �Ҽ����� ǥ���ϰ� ���� ���
    CompleteSet�� Set�� �ƴ� map�� �̿��Ͽ�, value���� �׷� �ε����� ���� ������ ��.

*/

#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

//�̸� �ٲ� ��.
struct stNetworkChecker
{
    set<int> completeSet;   //�˻簡 �Ϸ�� �ε���   ->
    queue<int> workQue;     //�۾� ��⿭
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
        
        //�۾���⿭�� �߰�.
        bool bIsInsert = netwrokInsertInWorkQue(network, index);
        if (bIsInsert == true)
        {
            //��⿭�� �߰� 
            networkCount++;     //���ο� ��Ʈ��ũ ����
        }
        else
        {
            //�߰����� �ʾҴ�? -> �̹� �˻��� �ε��� �н�
            continue;
        }


        //�۾���⿭�� �������� �ݺ� -> �Լ�ȭ �ϸ� ���� �κ�. ������ �н��Ѵ�.
        while ( networkWorkQueEmpty(network) == false)
        {
            queue<int>& workQue = network.workQue;
            set<int>& completeSet = network.completeSet;
            int comIndex = workQue.front();             //���� ���� �� �˻� 
            workQue.pop();
            completeSet.insert(comIndex);               //�Ϸ�¿� �ִ´�.
            vector<int>& com = computers.at(comIndex);  //�ش� �ε����� ��Ʈ��ũ ��Ȳ �ҷ�����
            
            //��Ʈ��ũ ���� ��Ȳ �˻�.
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
    @return �̹� �˻��� ��Ʈ��ũ�� ��� true ���� 
    @detail ��Ʈ��ũ �˻簡 �Ϸ�� �ε������� Ȯ��
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
    @return ��⿭�� ������� ��� ���� true
    @detail ��⿭�� ����ִ��� �˻� 
*/
bool networkWorkQueEmpty(stNetworkChecker& network)
{
    return network.workQue.empty();
}


/*
    @return �۾���⿭�� �߰� ��, ���� true
    @detail �۾���⿭�� �߰�. �̹� ��Ʈ��ũ Ž���� �Ϸ�� ��ǻ�ʹ� �߰����� �ʴ´�. 
*/
bool netwrokInsertInWorkQue(stNetworkChecker& network, int index)
{
    bool bSuccess = false;  //insert ������, true
    bool bIsComplete = networkIsComplete(network, index);
    
    if (bIsComplete == false)
    {
        //��Ʈ��ũ Ž���� �Ϸ�� ��ǻ�� �ε����� �ƴϴ�. -> ��⿭�� �߰��Ѵ�.
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

//    printf("��Ʈ��ũ �� : %d\n", result);


    return 0;
}