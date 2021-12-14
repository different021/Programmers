/*
    �־��� �迭�� Ŀ�ǵ忡 ���� �߶� ���� �� �� k��° ���� ���� ��.

    [return]:
    vector<int>

    [parameter]
    vector<int>         
    vector<vector<int>> {command [i, j, k], command[i2, j2, k2] ...)
    
    i��° ���� j��°�������� ���� �� k��° ���� ���϶�
    ��� Ŀ�ǵ忡 ���� k��° ���� ���ϰ�
    vector<int>�� ��� ����
   

    ex)
    array :
        [1, 5, 2, 6, 3, 7, 4]	
    command :         
        [[2, 5, 3], [4, 4, 1], [1, 7, 3]]	
    
    return :
        [5, 6, 3]
*/

#include <string>
#include <vector>
#include <algorithm>


#define ARRAY_MAX 100
#define COMMAND_MAX 50

using namespace std;

bool comp(const int& a, const int& b);
bool FindKByCommand(vector<int>& out, vector<int> src, vector<vector<int>>& commands);
bool CheckInvaildCommand(vector<int>* pCommand);

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;    
    answer.reserve(COMMAND_MAX);

    bool bIsFind = FindKByCommand(answer, array, commands);
    if (bIsFind = false)
    {
        //����
    }

    return answer;
}

bool comp(const int& a, const int& b) {
    return (a < b);
}

bool FindKByCommand(vector<int>& out, vector<int> src, vector<vector<int>>& commands) {
    bool bResult = false;
    vector<int> temp;                           //i���� j���� ���� �ӽ� �迭
    vector <vector<int>>::iterator itCommand;

    temp.reserve(ARRAY_MAX);

    for (itCommand = commands.begin(); itCommand != commands.end(); itCommand++)
    {
        temp.clear();   //�ӽ� ���� �ʱ�ȭ
        vector<int>* pCommand = &(*itCommand);

        bool bCheck =CheckInvaildCommand(pCommand);
        if (bCheck == false) goto lb_return;

        int i = pCommand->at(0) - 1;
        int j = pCommand->at(1);
        int k = pCommand->at(2) - 1;

        for (int index = i; index < j; index++) {
            temp.push_back(src.at(index));
        }

        sort(temp.begin(), temp.end(), comp);

        int result = temp.at(k);
        out.push_back(result);
    }

    bResult = true;

lb_return:
    return bResult;
}

bool CheckInvaildCommand(vector<int>* pCommand) {
    bool bResult = false;
    int i = -1;
    int j = -1;
    int k = -1;
    
    if (pCommand == nullptr) goto lb_return;
    if (pCommand->size() != 3)  goto lb_return;

    i = pCommand->at(0);
    j = pCommand->at(1);
    k = pCommand->at(2);

    if (i > j) goto lb_return;
    if ((j - i + 1) < k) goto lb_return;

    bResult = true;

lb_return:
    return bResult;
}

int main() {

    vector<int> src = { 1, 5, 2, 6, 3, 7, 4 };
    vector<vector<int>> commands = { {2, 5, 3} ,{4, 4, 1}, {1, 7, 3} };

    vector<int> result = solution(src, commands);

    for (auto it : result) {
        printf("%d", it);
    }
    return 0;
}
