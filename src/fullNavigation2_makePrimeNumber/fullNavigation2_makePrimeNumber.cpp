
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
    [solution]
    1. 주어진 문자열 분리 (+숫자가 맞는지 검증)
    2. 분리된 숫자 저장
    3. 저장된 숫자를 조합해 새로운 수 생성
    4. 생성된 수 소수인지 검증
    5. 소수 갯수 카운트 & 리턴
*/

/*
    [수 생성]
    문자를 이용해 생성 가능한 모든 숫자를 생성하는 방식
    
    vector<string> src 
    [검증된 파라미터]
    1. src는 1자리 정수가 string형태로 저장되어 있다ㅏ.
    2. src는 오름차순으로 정렬되어 있다.


    src[i]

*/
/*
    [소수 검사]

*/


#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>

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
    sort(strNumbers.begin(), strNumbers.end(), CompSingleDigit);

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

map<string, int> g_test;

void makeRecursive(deque<string>& out, queue<string> str, int left)
{
    queue<string> standby = str;
    
    if (left != 0)
    {
        while ( !standby.empty() )
        {
            string temp = standby.front();
            standby.pop();
            out.push_back(temp);

            left--;

            makeRecursive(out, standby, left);
        }
    }
    else
    {
        //문자열 다 나열함.
        string last;

        //빌때까지
        while ( !out.empty() )
        {
            last += out.front();
            out.pop_front();
            
        }

        g_test.insert( make_pair(last, atoi(last.c_str())) );
    }
}

//
//
bool SolutionMakeNumberBySingleDigit(map<int, int>& out, vector<string>& src)
{
    bool bResult = false;
    queue<string> que;
    deque<string> temp;

    for (auto& it : src)
    {
        que.push(it);
    }

    makeRecursive(temp, que, que.size());

    return bResult;
/*
    //1뽑
    //func1(out, src);
    for (int i = 0; i < src.size(); i++)
    {
        string temp1;
        temp1 = src[i];
        int iTemp = atoi(temp1.c_str());
        out.insert(make_pair(iTemp, iTemp));
    }

    //2뽑
    for (int j = 0; j < src.size(); j++)
    {
        for (int i = 0; i < src.size(); i++)
        {
            if (i == j) continue;
            string temp = src[i] + src[j];
            int iTemp = atoi(temp.c_str());
            out.insert(make_pair(iTemp, iTemp));
        }
    }
    
    //3뽑
    for (int k = 0; k < src.size(); k++)
    {
        for (int j = 0; j < src.size(); j++)
        {
            for (int i = 0; i < src.size(); i++)
            {
                if (i == j) continue;
                if (j == k) continue;
                string temp = src[i] + src[j] + src[k];
                int iTemp = atoi(temp.c_str());
                out.insert(make_pair(iTemp, iTemp));
            }
        }
    }

    //4뽑    
    for (int l = 0; l < src.size(); l++)
    {
        string temp4 = src[l];
        for (int k = 0; k < src.size(); k++)
        {
            string temp3 = temp4 + src[k];
            if (k == l) continue;
            for (int j = 0; j < src.size(); j++)
            {
                string temp2 = temp3 + src[j];
                if (j == k) continue;
                for (int i = 0; i < src.size(); i++)
                {
                    if (i == j) continue;
                    string temp1 = temp2 + src[i];
                    //temp = src[i] + src[j] + src[k] + src[l];
                    int iTemp = atoi(temp1.c_str());
                    out.insert(make_pair(iTemp, iTemp));
                }
            }
        }
    }

    for (int i = 0; i < src.size(); i++)
    {

    }
    */

    
}

//생성된 숫자중 프라임 넘버는 몇개일까요?
//성능 향샹을 의해서는
//
bool SolutionCountPrimeNumber(int& out, map<int, int>& src)
{
    bool bResult = false;

    return bResult;
}


//CheckPrimeNumber();


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
    //return 5 { 7 , 17k 71, 107, 701 } 
    string numbers = "1307";

    int result = solution(numbers);

    printf("만들수 있는 소수 갯수 : %d \n", result);

    return 0;
}