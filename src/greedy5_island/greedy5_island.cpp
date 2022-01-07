/*
    ���� �ٸ��� �����Ѵ�.
    ���� ��� �����ϴ� �ּ� ����� ���϶�.

    ABC 3���� ���� �ִٰ� �Ҷ�,
    %% A-B�� ���� �ǰ�, B-C�� ���� �Ǹ�, A-C ���� ����. %%


    [���� ����]
    -���� ����(n)  : 1 ~ 100
    -cost.size    : ( (n - 1) * n ) / 2 ���� (n = 100 �϶�, (100 - 1) * 100 / 2 = 99 * 100 / 2 = 49500 )
    
    -������ i�� ���Ͽ�
    cost[i][0], const[i][1] �� ����Ǵ� �μ��� ��ȣ. cost[i][3] �� �Ǽ� ���

    -��� ���� �ٸ��� ���ᰡ�� �� ���� �ƴϴ�. A-B, B-C���� ���� A-C���� ���� �ؾ� �Ѵ�.
    -������ �Ұ����� ���� ����.

    [����]
    n	costs	                                    return
    4	[[0,1,1],[0,2,2],[1,2,5],[1,3,1],[2,3,8]]	4


    []  : �� �ε���
    ()  : �ڽ�Ʈ
    -, |: ����

    [0]-(1)-[1]
     |     / |
    (2) (5) (1)
     | /     |
    [2]-(8)-[3]




    [0,1,1]
    [0,2,2]
    [1,2,5]
    [1,3,1]
    [2,3,8]


    [��ũ] - �׸� ����
    https://programmers.co.kr/learn/courses/30/lessons/42861
*/


/*
    ���� ��ٷο� ����
    {0, 1}
    {2, 0}
    ���� ���.
    �Ѵ� 0���� ���� �Ǿ� ������. cost[i][0]�� ���� Ȯ�� �� �� ����. 
    
    �� ���� �������� �ٸ��� ���� �� �ִ�. 
*/

/*
    �迭�� ���� ���鼭 
    [i][0] < [i][1] �� �����ǵ��� �ٲ۴�.
    
    


*/

#include <string>
#include <vector>

using namespace std;

#define MAX_ISLAND_NUMBER 100

struct  cBridge
{
    int index[2];   //����� �� ���� �ε���
    int cost;

    
};

struct cIsland
{
    int index;
    vector<cBridge> link;
    int group;
};

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int numOfIsland = n;
    

    return answer;
}


