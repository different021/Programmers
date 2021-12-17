/*
    �ΰ��� ����(vector<int>)�� �־�����.
    ù��°�� ���� ����Ϸ���
    �ι�°�� �Ϸ翡 ���� ������ %
    ����� 100%�� ���� �������� ���� �����մϴ�.
    ������, �ڿ� ����� ���� �Ϸ�Ǿ��� �ϴ��� ���� ����� �Ϸ���� �ʾҴٸ�, ������ �� �����ϴ�.
    �� �������� ��� ����� ������������ ����.


    [parameter]
    vector<int> progresses  : ���� ���� �Ϸ���
    vector<int> speeds      : �Ϸ� ���� �����

    [return]
    vector<int>             : ������ �����Ǵ� ��� ��

    progresses.size() < 100     �۾��� ����(progresses, speeds) �� 100�� ����.
    progress < 100              progress�� 100�̸� ���� 
    speeds < 100

    ex)
    progresses	                speeds	            return
    [93, 30, 55]	            [1, 30, 5]	        [2, 1]
    [95, 90, 99, 99, 80, 99]	[1, 1, 1, 1, 1, 1]	[1, 3, 2]
*/


/*
    [RULES]
    1. ������ 0������ ������� �����ؾ��Ѵ�.
    2. 100�� �Ǿ�߸� ���� �����ϴ�.

    How to solve?
    
    loop()
    {
        1. progress�� speed�� ���Ѵ�.
        2. �������� ���� �ֽ� ����� 100 �̻����� �˻�
          -> 100�̻��� ���, ���� ��� �˻� (���� �Ұ����� ���� ������ �ݺ�) 
            -> �� �̻� 100�̾����� ����(���� ī���� ����)
          -> 100�̸��� ���, ���� �ݺ�
    }

*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

//�Լ��� �� ���� �ʿ�
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> completeQue;
    size_t progressSize = progresses.size();
    size_t speedSize = speeds.size();
    size_t notCompleteProcessIndex = 0;        //���� �ȵ� ���μ��� �ε���


    if (progressSize != speedSize)
    {
        //���� ó��
        //���� ���ƾ߸� �Ѵ�.
        goto lb_return;
    }


    //��� �۾��� �Ϸ� �ɶ����� �ݺ�.
    while (notCompleteProcessIndex < progressSize)
    {
        int countOfComplete = 0;
        //100�̸��� Ȯ���ϴٴ� �����Ͽ� �ٷ� ���� ����(������ �ŷ�)
        for (int i = notCompleteProcessIndex; i < progressSize; i++)
        {
            progresses.at(i) += speeds.at(i);
            progresses.at(i) = min(progresses.at(i), 100);      //�ִ�ġ 100
        }

        for (auto it : progresses)
        {
            if (notCompleteProcessIndex >= progressSize) break; //�Ϸ� ���̽�

            //������� 100���� ũ��.
            if (progresses.at(notCompleteProcessIndex) == 100)
            {
                //é�Ϳ� ���� ť��� ���־ �ϱ��ϴµ� �ʿ����.
                countOfComplete++;
                notCompleteProcessIndex++;
            }
            else
            {
                break;
            }
        }

        if (countOfComplete > 0)
        {
            //������ ����� �ִ� ��� � �� ���� �ߴ��� ����.
            completeQue.push(countOfComplete);
        }
    }

    while (completeQue.empty() == false)
    {
        int releaseCnt = completeQue.front();
        completeQue.pop();
        answer.push_back(releaseCnt);

    }

lb_return:
    return answer;
}

int main()
{
    /*
    //case1
    vector<int> progresses = { 93, 30, 55 };
    vector<int> speeds = { 1, 30, 5 };          ////[return] [2, 1]
    */

    //case2
    vector<int> progresses  = { 95, 90, 99, 99, 80, 99 };
    vector<int> speeds      = { 1, 1, 1, 1, 1, 1 };      //return [1, 3, 2]

    vector<int> result = solution(progresses, speeds);
    printf("[RESULT]\n");
    for (auto it : result)
    {
        printf("%d\n", it);
    }

    return 0;
}