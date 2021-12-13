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
#include <unordered_set>
#include <unordered_map>

using namespace std;

bool GetCombinationCount(size_t& out, vector<vector<string>>& clothes);

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    size_t count = 0;
    bool bSuccess = GetCombinationCount(count, clothes);
    
    answer = static_cast<int>(count);

    return answer;
}


//�� ���� ������ ����
bool GetCombinationCount(size_t& out, vector<vector<string>>& clothes) {
    bool bResult = false;
    unordered_multiset<string> clothPart;
    unordered_set<string> kindOfPart;
    vector<vector<string>>::iterator itPart;
    unordered_set<string>::iterator itr_set;
    size_t countOfCombination = 1;

    if (clothes.size() == 0) goto lb_return;

    for (itPart = clothes.begin(); itPart != clothes.end(); itPart++) {
        vector<string>* vCloth = &(*itPart);
        
        string& part = (vCloth->at(1));
        kindOfPart.insert(part);
        clothPart.insert(part);
    }

    for (itr_set = kindOfPart.begin(); itr_set != kindOfPart.end(); itr_set++) {
        string pStr = (*itr_set);
        countOfCombination *= (clothPart.count(pStr) + 1);
    }

    out = countOfCombination - 1;
    bResult = true;

lb_return:
    return bResult;
}

