/*
    ���� N�� �̿��Ͽ� number�� ����ÿ�
    -��Ģ ����� ���� N�� �̿��Ͽ� number�� ������ �Ѵ�.
    -���� N�� ����ϴ� �ּ� Ƚ���� �����Ͻÿ�

    [����]
    N = 5, number = 12
    12 = 5 + 5 + (5 / 5) + (5 / 5)      N ��� : 6ȸ   
    12 = 55 / 5 + 5 / 5                 N ��� : 5ȸ
    12 = (55 + 5) / 5                   N ��� : 4ȸ

    �ּ� ��� 4ȸ

    [���� ����]
    N : 1 ~ 9
    number = 1 ~ 32000
    ���� : ��ȣ�� ��Ģ ���� ����
    ������ ����� ������ ����
    �ּҰ��� 8 �̻� �� ��� -1 ����
*/


/*
    [������ �ൿ]
    1. ��Ģ ����
    3. ���� ����
    2. ��ȣ (���� �ݱ� ���� ��) - ��Ģ���꿡 ���ÿ� ���Ե��� �ʴ´�. -> �Ű� �� �ʿ����.
*/

/*
    ���� ������ ���� set�� ����
    1���� ���� ������ ���� ���� -> s(1)
    2���� ���� ������ ���� ���� ���� -> s(2) = s(1) + s(1) 
    3���� ���� ������ ���� ���� ���� -> s(3) = s(1) + s(2) , s(2) + s(1)
    4���� ���� ������ ���� ���� ���� -> s(4) = s(1) + s(3), s(2) + s(2), s(3) + s(1)
    ...
    7���� �ݺ�

    �� �ܰ� ���� ��, target�� �����ϴ��� �˻�, ������ ���� �ܰ� ����

*/

/*
    [operator]
    1. +
    2. -
    3. *
    4. /

    5. ���ӵ� ����(���� �߰�)
 */



#include <string>
#include <vector>
#include <set>

using namespace std;

#define MAX_LAYER 8

int solution(int N, int number) {
    int answer = -1;
    int basicNumber = N;
    int target = number;
    int num = basicNumber;

    vector<set<int>> pool;
    pool.reserve(MAX_LAYER);
    
    for (int i = 0; i < MAX_LAYER; i++)
    {
        set<int> temp;
        pool.push_back(temp);
    }
    
    //1���� ������ �� �ִ� �� ����
    pool[0].insert(basicNumber);

    //Ÿ�� ���� Ȯ��
    if (pool[0].find(target) != pool[0].end())
    {
        //find
        answer = 1;
        goto lb_return;
    }

    //2�� �̻����� �����ϴ� ���� 
    for (int i = 1; i < MAX_LAYER; i++)
    {
        //�ڸ��� �߰�
        num = num * 10 + basicNumber;
        pool[i].insert(num);

        for (int j = 0; j < i; j++)
        {
            for (set<int>::iterator it = pool[j].begin(); it != pool[j].end(); it++)
            {
                int num1 = *it;
                for (set<int>::iterator it_opp = pool[i - (j + 1)].begin(); it_opp != pool[i - (j + 1)].end(); it_opp++)
                {
                    int num2 = *it_opp;

                    // + ����
                    int newNum = num1 + num2;
                    pool[i].insert(newNum);

                    // - ����
                    newNum = num1 - num2;
                    pool[i].insert(newNum);

                    // * ����
                    newNum = num1 * num2;
                    pool[i].insert(newNum);

                    // / ����
                    if (num2 != 0)
                    {
                        int div = num1 / num2;
                        pool[i].insert(div);
                    }
                    
                }

            }
            
        }

        //find target
        if (pool[i].find(target) != pool[i].end())
        {
            //find
            answer = i + 1;
            break;
        }
    }

lb_return:
    return answer;
}


int main()
{
    ////return 4
    //int N = 5;
    //int number = 12;

    //-1
    int N = 5;
    int number = 5555555;

    int result = solution(N, number);

    printf("input : %d\n", N);
    printf("target: %d\n", number);
    printf("�ּҰ�: %d\n", result);

    return 0;
}