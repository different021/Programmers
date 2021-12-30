
/*
    숫자로 이루어진 문자열을 이용해 소수(prime number)를 만들자

    [파라미터]
    string : 숫자로 이루어지 문자열

    [리턴]
    int : 주어진 문자열로 만들 수 있는 소수 갯수

    [제한]
    numbers.size() : 1 ~ 7
    numbers 는 0 ~ 9 사이의 숫자만으로 이루어 져 있다.
    "013" 은 0, 1, 3을 이용해 만들수 있는 소수를 찾으라는 뜻
    { 3, 13, 31 } 3개의 소수를 만들수 있다.

    [예제1]
    numbers     return 
    "17"        3
    
    { 7, 17, 71 } 3개의 소수를 만들 수 있다.

    [예제2]
    numbers     return
    "011"       2

    { 11, 101 } 2개의 소수를 만들 수 있다.

*/

/*
    [SOLUTION]
    1. 주어진 문자열을 하나씩 쪼갠다. (+ 정수 검증 과정)
    2. 정렬 (%필수%)
    3. 가능한 모든 수 생성
    4. 생성한 수 map에 저장 (중복제거)
    5. map에 저장된 모든 수에 대해 소수 검사
    6. 리턴
*/

/*
    [수 생성]
    문자를 이용해 생성 가능한 모든 숫자를 생성하는 방식
    
    vector<string> src 
    [검증된 파라미터]
    1. src는 1자리 정수가 string형태로 저장되어 있다ㅏ.
    2. src는 오름차순으로 정렬되어 있다.
        
    next_permutation 함수를 이용해서 품. 편리하네.
    주의할 점은 오름차순으로 정렬되어 있어야한다.
    높은 순으로 이동하며 정렬하기 때문에 정렬되어 있지 않다면 중간부터 계산

*/

/*
    [소수 검사]
    bool CheckPrimeNumber(int input);

    input을 2 ~ input의 제곱근 까지의 수로 나누어 확인
    


*/


#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

using namespace std;


//solution class
int solution(string numbers);
bool SolutionCutEverySingleChar(vector<string>& out, string& input);            
bool SolutionMakeNumberBySingleDigit(map<int, int>& out, vector<string>& src);
bool SolutionCountPrimeNumber(int& out, map<int, int>& src);

//공통? 은 아니고 solution에 종속되지 않을 함수
bool CheckPrimeNumber(int input);
bool CheckStrToDigit(const char& singleDigit);
bool CompSingleDigit(const string& a, const string& b);

int solution(string numbers) {
    int answer = 0;
    bool bSuccess = false;
    string& input = numbers;
    vector<string> strNumbers;    //분리된 숫자를 저장
    map<int, int> newNumbers;        //분리된 문자를 바탕으로 숫자 생성한 숫자 저장

    //1. 분리 (+숫자 검증) & 2. 저장 
    bSuccess = SolutionCutEverySingleChar(strNumbers, input);
    if (bSuccess == false) {/* 잘못된 문자열 감지 */ };

    //오름차순 정렬 -> 빼도 될듯.
    sort(strNumbers.begin(), strNumbers.end(), less <string>());

    //3.생성가능한 모든 수 생성.
    //int test = atoi("0011"); -> test = 11 -> 쌉가능 편리하네....
    bSuccess =  SolutionMakeNumberBySingleDigit(newNumbers, strNumbers);
    if (bSuccess == false) { /* 넘버 생성 실패?! */ };

    //4. 소수 검사
    bSuccess =  SolutionCountPrimeNumber(answer, newNumbers);
    if (bSuccess == false) { /* 소수 검출 실패?! -> 파라미터 확인 */ };

    int a = 0;

    return answer;
}


/*
    [주의]
    의도하지 않은 문자열이 삽입되도 멈추지 않는다. ex) aBC102, -5432 등등
    단, 숫자들의 저장은 지속 된다.  ex)  {"1", "0", "2" }, { "5", "4", "3", "2" }
    대신 리턴값을 false가 된다.
     

    1. 주어진 문자을 한글자 분리
    2. 분리된 한 글자 숫자 인지 확인
    3. is(숫자)
        true  -> 저장
        false -> bResult = fale, (주의! 함수가 멈추지는 않는다)
    4. 1~3 반복(문자열에 전체 검사후 종료)
*/
bool SolutionCutEverySingleChar(vector<string>& _out, string& _input)
{
    bool bResult = true;
    bool bSuccess = false;
    vector<string>& out = _out;
    string& input = _input;

    for (size_t i = 0; i < input.size(); i++)
    {
        string single = input.substr(i, 1);
        const char* ch = single.c_str();

        bSuccess = CheckStrToDigit(ch[0]);
        if (bSuccess = true)
        {
            out.push_back(single);
        }
        else 
        {
            //한번 실패해도 문자열이 반복되기 때문에 별도의 체크 변수가 있다.
            bResult = false;
        }
    }

    return bResult;
}


string func1(map<int, int>& out, vector<string>& src)
{
    string result;
    for (int i = 0; i < src.size(); i++)
    {
        string temp = src[i];
        int iTemp = atoi(temp.c_str());
        out.insert(make_pair(iTemp, iTemp));
    }

    return result;
}



/*
    [주의]
    파라미터 vector<string> src의 멤버는
        1. 한자리  
        2. 양의 정수 { 0 ~ 9 }
    를 충종하는 집합이여야 한다.
        ex) { "1", "2", "3" } 같은 등등

*/
bool SolutionMakeNumberBySingleDigit(map<int, int>& out, vector<string>& src)
{
    bool bResult = false;
    map<int, int>& intgerMap = out;

    do{
        string sum;
        for (auto& it : src)
        {
            sum += it;
            int value = atoi(sum.c_str());               
            intgerMap.insert(make_pair(value, value) );
        }
    } while (next_permutation(src.begin(), src.end()));

    bResult = true;
    return bResult;
    
}

/*
    [parameter]


    [output]
    Prime Number 의 갯수

    [return]
    return false When src.size() == 0

*/
bool SolutionCountPrimeNumber(int& out, map<int, int>& src)
{
    bool bResult = false;
    map<int, int>& integerMap = src;
    int primeCount = 0;

    if (src.size() == 0) goto lb_return;

    for (auto& it : integerMap)
    {
        int value = it.first;
        
        if (value == 0) continue;
        if (value == 1) continue;

        bool isPrime = CheckPrimeNumber(value);
        if (isPrime == true)
        {
            primeCount++;
        }
    }

    out = primeCount;

    bResult = true;

lb_return:
    return bResult;
}


/*
    입력받은 수가 prime Number 인지 확인
    2 ~ sqrt(input) 까지 수로 input을 나눠본다.
    수학 이론상 제곱근까지만 나눠보면 prime number라고 한다.
*/
bool CheckPrimeNumber(int input)
{
    bool bResult = true;
    int square = static_cast<int>(sqrt(input));

    //2부터 시작
    for (int i = 2; i < square; i++)
    {
        int remainder = input % i;
        if (remainder == 0)
        {
            //나누어 떨어지는 수가 있다면 프라임 넘버가 아니다.
            bResult = false;
            break;
        }
    }

    return bResult;
}

//해당 문자가 정수로 전환 가능한지 체크한다. 
//해당 솔루션에서는 음수를 넣으면 안될 것이나
//다른 솔루션에서는 음수를 사용할 수도 있으니 막지는 않았다.
bool CheckStrToDigit(const char& singleDigit)
{
    bool bResult = false;
    if (isdigit(singleDigit) != 0)
    {
        bResult = true;
    }
    else if (singleDigit == '0')
    {
        bResult = true;
        //isdigit은 "0"을 검출하지 못한다.
    }

    return bResult;
}

/*
[주의]
검증된 벡터를 넣을 것.
벡터의 요소별 검증이 없다.
이미 검증된 벡터를 사용한다고 가정된 함수

[용도]
벡터에 저장된 문자열을 숫자로 변환 후, 오름차순 정렬

atoi()에 의한 exception 발생 가능성 존재.
*/
bool CompSingleDigit(const string& a, const string& b)
{
    int iA = atoi( a.c_str() );
    int iB = atoi( b.c_str() );

    return iA < iB;
}


int main()
{
    //return 5 { 7 , 17, 71, 107, 701 } 
    //string numbers = "1307";

    string numbers = "17";

    //string numbers = "002";

    int result = solution(numbers);

    printf("만들수 있는 소수 갯수 : %d \n", result);

    return 0;
}