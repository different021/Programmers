/*
* *   착용 가능한 옷 가지수 구하는 프로그램
*   옷 1가지는 반드시 입는다. 같은 위치 중복 착용 불가능
    아래 경우 5가지 발생

    2차원 배열 옷
    모자 - 노란_모자, 초록_터번
    눈  - 선글라스 
    [ "yellowhat", "headgear" ]

    [return]
    해당 의상을 이용해 만들 수 있는 가지수 

    //추가적인 사항
    의상 수 : 1 ~ 30 
    문자열  : 1 ~ 20
    중복없음.
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


//각 행의 갯수를 구한
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

