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
    1. 가능한 조합 모두 생성 후, 소팅
    2. 작은 수 골라서 제거.

    두 경우 모두 순서를 바꿀 일은 없다.
    다만 중간의 값이 바뀔 수 있다.

    [방법 1]
    1. 조합 가능한 모든 수 생성 
    2. 내림차순 소팅

    단점. 숫자가 커지면 모든 조합 생성에 부하가 있다. 수의 크기 (1 ~ 1000000)
    자릿수가 큰 관계로 탈락.


    [방법 2] -> 채택
    1. i부터 k번째 까지 수 중 가장 큰 수 찾기
    2. 가장 큰수 앞의 수 n개 제거
    3. i 번째 수 확정
    (i + 1)번째부터 2 ~ 3 반복

    [i번째 자리수 확정 방식]
    1. 남은 자릿수와 제거할 숫자가 같다면 몽땅 제거.
    2. i번째 수부터 d번재 수 중 가장 큰 수를 찾는다.
    3. 가장 큰 수 앞의 앞의 숫자들을 제거
    
    
    nubmer = 1942, k = 2

    string의 i번째 부터 k 번째 중 최대값의 인덱스 n 찾기 
    
    
    string 
    
    ("1942", 2) 중 0부터 1까지 중 최대값 9 인덱스 1
    ("942, 1)  0번 인덱스 1개 제거
    0번 인덱스 확정,

    ("942", 1) 1번 인덱스 부터 


    
    <선행 작업>
    string을 하나하나 int로 변환
    중간 삭제가 용이한 자료구조에 넣는다.
    리스트가 용이해 보이지만
    리스트는 인덱스 접근에 불편한 점이 있다.
    인덱스 접근에 용이하도록 벡터 사용

    <후행 작업>
    숫자들을 문자열로 바꾸어 리턴.
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

void Trim(int index, vector<int>& out, int k);


string solution(string _number, int k) {
    string answer = "";
    string number = _number;
    vector<int> numList;
    int num = k;        //제거할 갯수

    //파라미터 검증 루틴 추가.
    /* 파라미터 검증 */

    //number를 사용하기 쉬운 형태로 가공
    bool bSuccess = solutionInitialize(numList, number);
    if (bSuccess == false) { /*초기화 실패 코드 문자열에 숫자가 아닌 수가 섞여 있는 경우를 강력 의심*/ };

    bSuccess = solutionGetBiggestNumber(answer, numList, num);

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
    int end = src.size() - k - 1;
    string result = "";

    for (; length > 0; length--)
    {
        vector<int>::iterator it_start = src.begin();
        vector<int>::iterator it_end = src.begin();
        advance(it_start, start);
        advance(it_end, end);

        vector<int>::iterator it_max = max_element(it_start, it_end + 1);
        int maxIndex = max_element(it_start, it_end + 1) - src.begin();
        start = maxIndex + 1;
        end++;
        int value = *it_max;
        result += to_string(value);
    }

    out = result;

    return bResult;
}


int main()
{
    ////return 94
    string number = "1924";
    int k = 2;

    ////"3234"
    /*string number = "1231234";
    int k = 3;*/

    ////"4567"
    /*string number = "1234567";
    int k = 3;*/



    string result = solution(number, k);

    printf("%s \n", result.c_str());

    return 0;
}