/*
    어떤 수에서 k개의 수를 제거 했을때, 가장 큰 수를 구하시오.

    [param]
    string number   : 어떤 수
    int k           : 제거할 갯수

    [return]
    int             : number에서 k개의 수를 제거 후, 가장 큰 수

    [예시]
    number  : 1924
    k       : 2

    생성 가능한 수 :  [19, 12, 14, 92, 94, 24]

    return  : 94 (가장 큰 수)

    1924중 두개의 숫자를 제거 하면, 2자리 수가 된다. 
    생성 가능한 두자리 수는 19, 12, 14, 92, 94, 24 이다.
    이 중, 가장 큰 수는 94


    [제한 사항]
    number.size : 1 ~ 10000000
    k           : 1 < k < number.size

*/

/*
    [solution]
    1. 문자열 -> 숫자 배열 로 변환 
    2. index ~  end (= size - k) 번째 수 중 가장 큰 찾기
    3. index = 가장 큰 수의 index
    4. end++
    2 ~ 4 반복 ( (size - k) 번 )

    k가 제거할 문자의 갯수 이므로. 
    size - k 는 표시할 문자 수이다.
*/


#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool GetDigit(int& out, char* pChar);

//solutoin
string solution(string _number, int k);
bool solutionInitialize(vector<int>& out, string _number);
bool solutionGetBiggestNumber(string& out, vector<int>& src, int k);

string solution(string _number, int k) {
    string answer = "";
    string number = _number;
    vector<int> numList;

    //number를 사용하기 쉬운 형태로 가공
    bool bSuccess = solutionInitialize(numList, number);
    if (bSuccess == false) { /*초기화 실패 코드 문자열에 숫자가 아닌 수가 섞여 있는 경우를 강력 의심*/ };

    bSuccess = solutionGetBiggestNumber(answer, numList, k);

    if (answer.compare("") == 0)
    {
        answer = "0";
    }

    return answer;
}

/*
    @detail 실패시 out = 0, 하지만 0일때도 out = 0, return값이 함수의 변환 실패 여부를 알려준다.
    @param  out : output, pChar : src
    @return 함수 성공 여부 0일경우 검사.     
*/
bool GetDigit(int& out, char* pChar)
{
    bool bResult = true;

    int num = atoi(pChar);  
    if (num == 0)   //실패시 0리턴
    {
        if (*pChar != '0')  bResult = false;
    }

    //return
    out = num;

lb_return:
    return bResult;
}

/*
    @detail     주어진 문자열(오로지 숫자로 이루어진)을 숫자로 변환하여 리스트에 넣어주는 함수.
    @param      out : _number를 숫자로 변환해서 넣어주는 리스트(output), _number 숫자로 바꿔줄 문자열(문자열 내부 값이 모두 숫자로 변환 가능해야한다.)
    @return     함수 성공 여부. 모든 수를 
    @warning    _number가 숫자로 변환하지 못하는 경우 return false; 음수는 측정되지 않는다.
*/
bool solutionInitialize(vector<int>& out, string _number)
{
    bool bResult = true;
    string& number = _number;

    for (size_t i = 0; i < number.size(); i++)
    {
        int num = 0;
        char ch = number[i];
        bool bSuccess = GetDigit(num, &ch);
        if (bSuccess == false) { bResult = false; /* 변환 실패시 처리 방법 추가 */ };
        out.push_back(num);     //마지막에 삽입
    }

lb_return:
    return bResult;
}

bool solutionGetBiggestNumber(string& out, vector<int>& src, int k)
{
    bool bResult = false;
    int length = src.size() - k;
    int start = 0;
    string result = "";

    for (; length > 0; length--)
    {
        vector<int>::iterator it_start = src.begin();
        vector<int>::iterator it_end = src.end() - length + 1;  //(+ 1?)범위의 마지막 원소는 검사하지 않는다.
        advance(it_start, start);

        vector<int>::iterator it_max = max_element(it_start, it_end );
        int maxIndex = max_element(it_start, it_end ) - src.begin();
        start = maxIndex + 1;
        int value = *it_max;
        result += to_string(value);
    }

    out = result;

    return bResult;
}


int main()
{
    ////return 94
    /*string number = "1924";
    int k = 2;*/

    ////"3234"
    /*string number = "1231234";
    int k = 3;*/

    //////"4567"
    //string number = "1234567";
    //int k = 3;

    string number = "2190999999";
    int k = 2;


    string result = solution(number, k);

    printf("%s \n", result.c_str());

    return 0;
}