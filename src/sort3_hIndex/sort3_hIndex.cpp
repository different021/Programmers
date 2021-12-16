
/*

    과학자의 생산성과 영향력을 나타내는 지표 H-Index

    n편의 논문 중, h번 이상 인용된 논문이 h개라고 할때,
    h값의 최대값을 H-index라고 한다.
    논문의 인용횟수가 들어간 vector<int> citations가 주어질때,
    H-Index를 구하여 리턴하라

    [parameter]
    vector<int> citations

    [return]
    int



    ex)
    citations	        return
    [3, 0, 6, 1, 5]	    3

    3회 이상 인용된 논문 3개 (인용횟수: 3, 6, 5 )
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const int& a, const int& b);
bool  GetHindex(int& out, vector<int>& citations);

int solution(vector<int> citations) {
    int answer = 0;

    bool bSuccess = GetHindex(answer, citations);

    return answer;
}

//참조한 수가 많은 순으로 소팅
bool comp(const int& a, const int& b)
{
    return (a > b);
}

//내부에서 소팅까지 진행
/*
    1. 인용횟수가 많은 순서로 정렬
    2. 가장 많이 인용된 횟수를 시작으로 인용된 횟수의 인덱스를 확인
    3. 크거나 같으면 리턴

*/
bool  GetHindex(int& out, vector<int>& citations) {
    bool bResult = false;
    int hIndex = 0;
    int citaSize = citations.size();
    int i = 0;

    //잘못된 파라미터
    if (citaSize == 0) goto lb_return;

    //인용횟수가 많은 순으로 정렬
    sort(citations.begin(), citations.end(), comp);

    i = *(citations.begin());
    for (; i > 0; i-- ) 
    {
        
        if (i < citaSize) {
            int useageOfIndex = citations.at(i - 1);
            if (useageOfIndex >= i)
            {
                hIndex = i;
                break;
            }
        }
        else {
            //마지막 인덱스 검사
            int lastData = citations.back();
            if (lastData >= i)
            {
                //n을 넘을 수 없다.
                hIndex = citaSize;
            }
            break;
        }
    }

    bResult = true;
    out = hIndex;

lb_return:
    return bResult;
}


int main()
{
    vector<int> citations = { 3, 0, 6, 1, 5 };
    int result = solution(citations);

    printf("H-Index : %d\n", result);

    return 0;
}