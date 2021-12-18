/*
    ���� ������ �켱 ����ϴ� �ý����� ����
    
    1. ���� �տ� �ִ� ����(j = 0)�� ������.
    2. j���� �켱 ������ ���� ������ �Ѱ��� �����ϸ� j�� ��� ��� ���� �ڷ� ������.
    3. �׷��� ������ j �μ�


    //�ָ��� ���� 
    priorities	        location	return
    [2, 1, 3, 2]	    2	        1
    [1, 1, 9, 1, 1, 1]	0	        5

    ����� ������ ����
    ������ �ǵ��� ��Ȯ�ϰ� ������� �ʴ´�.
    ù��° ������ A�� 1, B�� 2�θ� �ٲپ� ���Ƶ� ������� �ǵ��� ������ ���ٵ�.
    
    ����� ����� ����� ������ ���� ���÷�
    �����ڿ��� -100�� �帳�ϴ�. 

    [�Ʒ� ���÷� ������ �ȵǴ� ���]
    ���� ū �켱 ������ ���� �ε�����  i 

    solution([2, 4, 8, 2, 9, 3, 3], 2) return 2 

     A, B, C, D, E, F, G 
    [2, 4, 8, 2, 9, 3, 3]

    EFGABCD

    i�� 2�϶�, return 2 (C(8)�� 2��°�� �μ�)
    i�� 4�϶�, return 1 (E(9)�� 1��°�� �μ�)

    

    [parameter]
    vector<int> : �켱�� �迭
    int         : �μ������ �˰���� ���� (0���� ����)

    [return]
    int         : �μ�� ���� (1���� ����)

    [���� ����]
    priorities.size()   : 1 ~ 100
    priority            : 1 ~ 9
    location            : 0 ~ 99

*/

/*
*   solution
    1. ù��° ��� ����
    2. ������ ��ҿ� ��
    3. �ϳ��� ū �켱���� �����ϸ� ���� �ڷ�
    4. ������ �Ϸ�Que��
    5. ��� ��Ұ� ���� �ɶ����� 1~4 �ݺ�.

*/


#include <string>
#include <vector>
#include <queue>

using namespace std;


int solution(vector<int> priorities, int location) {
    int answer = 0;
    vector<int>& inputVect = priorities;
    queue<int> resultQue;

    size_t size = inputVect.size();
    size_t targetIndex = 0;

    int priority = 0;
    int cnt = 0;

    //[Start] Check Parameter
    if (size < 1)
    {
        //���Ϳ� �����Ͱ� ���� ���
        goto lb_return;
    }
    if (location < 0)
    {
        //�߸��� �ε����� �Է��� ���
        goto lb_return;
    }
    //[Done] Check Parameter()
    targetIndex = static_cast<int>(location);

    for (vector<int>::iterator it = inputVect.begin(); it != inputVect.end(); )
    {
        int prio = *priorities.begin();
        it = inputVect.erase( inputVect.begin() );
        vector<int>::iterator itInner;
        for ( itInner = inputVect.begin(); itInner != inputVect.end(); itInner++)
        {
            if (prio < *itInner)
            {
                inputVect.push_back(prio);
                targetIndex--;
                break;
            }
        }

        if ((itInner) == inputVect.end())
        {
            resultQue.push(prio);
        }
    }


    printf("Que Test \n");
    while (resultQue.empty() != true)
    {
        printf("%d\n", resultQue.front());
        resultQue.pop();
    }
    

lb_return:
    return answer;
}






int main()
{
    /*vector<int> priorities = { 2, 1, 3, 2 };
    int location = 2;*/

    vector<int> priorities = { 1, 1, 9, 1, 1, 1 };
    int location = 0;

    int result = solution(priorities, location);
    printf("%d�� ������ �μ� ���� : %d\n", location, result);

    return 0;
}