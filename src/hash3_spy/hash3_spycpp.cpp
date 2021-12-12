/*
* *   ���� ������ �� ������ ���ϴ� ���α׷�
*   �� 1������ �ݵ�� �Դ´�. ���� ��ġ �ߺ� ���� �Ұ���
    �Ʒ� ��� 5���� �߻�

    2���� �迭 ��
    ���� - ���_����, �ʷ�_�͹�
    ��  - ���۶� 
    [ "yellowhat", "headgear" ]

    [return]
    �ش� �ǻ��� �̿��� ���� �� �ִ� ������ 

    //�߰����� ����
    �ǻ� �� : 1 ~ 30 
    ���ڿ�  : 1 ~ 20
    �ߺ�����.
*/


#include <string>
#include <vector>

using namespace std;

bool GetCombinationCount(size_t& out, vector<vector<string>>& clothes);

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    size_t count = 0;
    bool bSuccess = GetCombinationCount(count, clothes);
    //�Լ� ���� ����üũ 
    
    answer = static_cast<int>(count);

    return answer;
}


//�� ���� ������ ����
bool GetCombinationCount(size_t& out, vector<vector<string>>& clothes) {
    bool bResult = false;
    vector<vector<string>>::iterator itPart;
    vector<string>::iterator itCloth;
    size_t countOfCombination = 1;

    if (clothes.size() == 0) goto lb_return;

    for (itPart = clothes.begin(); itPart != clothes.end(); itPart++) {
        vector<string>* vCloth = &(*itPart);
        
        size_t size = vCloth->size();
        if (size == 2)
            return 5;
        countOfCombination *= (size + 1);
    }

    out = countOfCombination - 1;
    bResult = true;

lb_return:
    return bResult;
}

