/*
    [조이스틱]
    과거 오락실 게임은 기록을 세우면 이름을 입력하는 창이 나왔다.
    당연히 키보드가 없으니 조이스틱을 이용해 이름을 입력하고는 했다.
    위저보드에서 입력하는 방법도 있었으나
    
    AAAA

    등으로 입력된 문자열을 조이 스틱으로 바꾸는 경우도 있다.

    조이스틱을 입력을 하면 다음과 같이 반응한다.
    위 : 다음 문자.
    아래 : 이전 문자.
    오른쪽 : 오른쪽 문자
    왼쪽 : 왼쪽 문자

    로 이동 했다.
    이때 A에서 이전 문자 (아래) 입력시 Z
    가장 앞 문자에서 왼쪽 입력시 가장 끝 문자로 이동 하게 된다.

    입력 받은 문자열을 입력하는 가장 적은 횟수를 구하라

    "INPUT" 이라는 문자열을 입력하면 AAAAA(5글자)로 시작한다.

    [파라미터]
    string name : 입력할 문자열
    
    [출력]
    int : 최소 입력횟수

*/


/*
    알파뱃 순서  필요 조작 획수
    A       0       0
    B       1       1
    C       2       2
    D       3       3
    E       4       4
    F       5       5
    G       6       6
    H       7       7
    I       8       8
    J       9       9
    K       10      10
    L       11      11
    M       12      12  상 이동 유리
    N       13      13  상화 이동 상관없음
    O       14      12  하 이동 유리
    P       15      11
    Q       16      10
    R       17      9  
    S       18      8
    T       19      7
    U       20      6
    V       21      5
    W       22      4
    X       23      3
    Y       24      2
    Z       25      1
*/

/*
    [상하 이동 유불리]
    A ~ M 까지의 문자는 (상) 이동 유리
    N ~ Z 까지의 문자는 (하) 이동 유리


    [좌우 이동 유불리]

    AAAA    -> KAAN
    AAA     -> CAABN

    첫문자 제외
    prefix의 연속된 A와

    suffix의 연손된 A 갯수 비교


        KADBBDAA
    ->  ADBBDAA  (앞문자(K) 제거 )
    prefix: 연속 A 1개
    suffix: 연속 A 2개

    앞부분 부터 시작되는 연속된 A가 적은 쪽 우선 탐색 

    prefix의 연속 A가 적다 -> 우 이동 
    suffix의 연속 A가 적다 -> 좌 이동



*/

/*
    [solution]
    1. 문자열 좌우 이동 유불리 및 횟수 판단
    2. 문자열 상하 이동 유불리 및 횟수 판단
    3. 리턴 (1, 2) 결과 합산
    
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

//문자별 조작 횟수 저장된 map
void OperationNumberInitialize(map<char, int>& OperationNumberPerChar);

//solution class
int solution(string name);
int solutionGetNumberOfLateralMovement(string input);           //문자열 종이동 수
int solutionGetNumberOfVerticalMovementString(map<char, int>& OperationNumberPerChar, string& input);   //문자열 횡이동 수
int solutionGetNumberOfVerticalMovementSingleChar(map<char, int>& OperationNumberPerChar, const char input);  //문자 하나 횡이동 수

int solution(string name) {
    map<char, int> operationNumberPerChar;        //문자별 필요 조작 횟수 저장
    int answer = 0;
    string& input = name;
    

    OperationNumberInitialize(operationNumberPerChar);
    
    //횡이동 필요 횟수 계산
    int nReteralMove = solutionGetNumberOfLateralMovement(input);
    int nVerticalMove = solutionGetNumberOfVerticalMovementString(operationNumberPerChar, input);

    answer = nReteralMove + nVerticalMove;

    return answer;
}


/*
    @detail 각 문자를 입력하는데 필요한 종이동 횟수 (조이스틱 상하 조작)
    @param  operationNumberPerChar 초기화 시킬 대상
    @return void
*/
void OperationNumberInitialize(map<char, int>& operationNumberPerChar)
{
    char ch = 'A';
    int numberOfOperation = 0;

    //우이동 문자
    for (int i = 0; i < 13; i++)
    {
        operationNumberPerChar.insert( make_pair(ch, i) );
        ch++;
    }

    //좌이동 문자
    for (int i = 13; i > 0; i--)
    {
        operationNumberPerChar.insert(make_pair(ch, i));
        ch++;
    }

    //우이동 문자
    char smallCh = 'a';
    for (int i = 0; i < 13; i++)
    {
        operationNumberPerChar.insert(make_pair(smallCh, i));
        smallCh++;
    }

    //좌이동 문자
    for (int i = 13; i > 0; i--)
    {
        operationNumberPerChar.insert(make_pair(smallCh, i));
        smallCh++;
    }
}

/*
    @detail 횡이동 횟수를 구해주는 함수
    @param  input 입력하고자하는 문자열
    @return int 횡이동 횟수
    @warning 리턴값은 문자열의 사이즈를 넘을 수 없다.
*/
int solutionGetNumberOfLateralMovement(string input)
{
    int nResult = 0;
    string& str = input;
    char* target = nullptr;
    size_t size = input.size();
    size_t half = static_cast<size_t>(size) / 2;
    int cntOfPreifxA = 0;
    int cntOfSuffixA = 0;
    int notmoveCount = 0;

    bool bMoveLeft = false;    //좌 이동 할까요?

    if (size < 3)
    {
        nResult = size - 1;
        goto lb_return;
    }

    //GetCountOfConsecutiveA
    for (int i = 1; i < half + 1; i++)
    {
        char ch = str[i];
        if (ch == 'A')
        {
            cntOfPreifxA++;
        }
        else
        {
            //연속되지 않으면 의미 없다?
            break;
        }
    }
    

    //GetCountOfConsecutiveABack
    for (int i = size - 1; i > half; i--)
    {
        if (str[i] == 'A')
        {
            cntOfSuffixA++;
        }
        else
        {
            //연속된 수만 센다.
            break;
        }
    }

    
    if (cntOfPreifxA > cntOfSuffixA)
    {
        //좌이동이 횟수가 더 적다.
        bMoveLeft = true;   
    }

    if (bMoveLeft)
    {
        //오른쪽의
        //연속된 A 만큼 이동할 필요가 없어진다.
        for (int i = 1; i < size; i++)
        {
            if (str[i] != 'A') break;
            notmoveCount++;
        }

    }
    else
    {
        //오른쪽 이동
        for (int i = size - 1; i > 0; i--)
        {
            if (str[i] != 'A') break;
            notmoveCount++;
        }
    }

    nResult = size - 1 - notmoveCount;

lb_return:
    return nResult;
}

/*
    @detail 문자열 전체에 대해 종이동 수의 총합 계산
    @param  input 종이동 횟수를 알고싶은 문자열
    @return int 총 종이동 횟수
*/
int solutionGetNumberOfVerticalMovementString(map<char, int>& OperationNumberPerChar, string& input)
{
    int nResult = 0;
    string& name = input;
    size_t size = name.size();

    for (int i = 0; i < size; i++)
    {
        char ch = input[i];
        int num = solutionGetNumberOfVerticalMovementSingleChar(OperationNumberPerChar, ch);
        nResult += num;
    }

    return nResult;
}

/*
    @detail 문자 하나에 대한 종이동 수 
    @param  input 종이동 횟수를 알고싶은 문자 하나
    @return int 종이동 횟수
*/
int solutionGetNumberOfVerticalMovementSingleChar(map<char, int>& OperationNumberPerChar, const char input)
{
    int nResult = 0;

    OperationNumberPerChar.find(input);

    map<char, int>::iterator itr = OperationNumberPerChar.find(input);
    if (itr != OperationNumberPerChar.end())
    {
        nResult = itr->second;
    }

    return nResult;
}

int main()
{
    //56
    //string name = "JEROEN";

    //23
    //string name = "JAN";

    //string name = "AAA";

    // 7 
    string name = "ABAAB";

    int result = solution(name);

    printf("결과값 : %d \n", result);

    return 0;
}