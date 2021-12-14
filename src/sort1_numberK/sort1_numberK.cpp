/*
    주어진 배열을 커맨드에 따라 잘라 정렬 한 후 k번째 수를 구할 것.

    [return]:
    vector<int>

    [parameter]
    vector<int>         
    vector<vector<int>> {command [i, j, k], command[i2, j2, k2] ...)
    
    i번째 부터 j번째까지수를 정렬 후 k번째 수를 구하라
    모든 커맨드에 대한 k번째 수를 구하고
    vector<int>에 담아 리턴
   

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

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;    
    answer.reserve(COMMAND_MAX);

    bool bIsFind = FindKByCommand(answer, array, commands);

    return answer;
}

bool comp(const int& a, const int& b) {
    return (a < b);
}

bool FindKByCommand(vector<int>& out, vector<int> src, vector<vector<int>>& commands) {
    bool bResult = false;
    vector<int> temp;                           //i부터 j까지 넣을 임시 배열
    vector <vector<int>>::iterator itCommand;

    temp.reserve(ARRAY_MAX);

    for (itCommand = commands.begin(); itCommand != commands.end(); itCommand++)
    {
        temp.clear();   //임시 벡터 초기화
        vector<int>* pCommand = &(*itCommand);

        //command 유효성 검사 추가

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