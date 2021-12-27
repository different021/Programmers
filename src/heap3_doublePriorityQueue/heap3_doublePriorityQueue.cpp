/*
    [문제]
    벡터에 문자열로 명령어가 들어 있다.
    명령어 I는 공백 뒤에 이어지는 숫자를 삽입
    명령어 D일 경우 공백 뒤 이어지는 숫자가
         1일 경우 : 최대값 삭제
        -1일 경우 : 최소값 삭제

    명령어를 수행후 데이터의 최대값과 최소값을 리턴하시오.


    [파라미터]
    vector<string> operations : 명령어 벡터
    아래와 같은 커맨드가 들어 있다.

    [커맨드]
     I n    : 큐에 정수 n 삽입
     D 1    : 큐의 최대값 삭제
     D -1   : 큐의 최대값 삭제

    [리턴]
    vector<int> 
    (최대값, 최소값)을 리턴
    큐가 비어 있다면 (0, 0) 리턴
    
    [예제 1]
    parameter       return
    ["I 16","D 1"]	[0,0]
    
    I 16    : 16삽입          Que = { 16 }
    D 1     : 최대값 삭제      Que = {}
    비어 있으므로 return  (0, 0)

    [예제 2]
    parameter                       return
    ["I 7","I 5","I -5","D -1"]	    [7,5]

    I 7     : 7 삽입                  { 7 }
    I 5     : 5 삽입                  { 7, 5 }
    I -5    : -5삽입                  { 7, 5, - 5 }
    D -1    : 최소값 삭제(-5)          {7, 5 }

    return  (7 , 5)
        (최대값, 최소값)
    
    
    [제한사항]
    operations.size() : 1 ~ 1000000
    동일한 최대, 최소값이 존재할 경우 하나만 삭제.     ex) { 5, 5, 3, 4, 1, -1, -1 } 의 경우 5한개 또는 1 한개만 삭제.
    빈 큐에서는 연산을 무시한다.                      ex) { }  Nothing to do heapeen when I wonder

    [설명없는 케이스 ]
    1. 데이터가 하나인 경우   ex) { 1 } 
        최대 최소값을 같게 리턴하나?

*/

/*
    [포인트]
    1. 커맨드 파싱
        해당 명령어를 통해 동작이 정해진다.
    2. 앞 뒤 모두 제거가능한 자료구조
        D  1 : 최대값 삭제
        D -1 : 최소값 삭제
        I  n : n 삽입(n은 정수)

        크기별로 정렬되어 있는 편이 유리.
        우선순위큐를 사용할 경우 뒤를 제거하는것이 힘들다.
        디큐를 이용하면 앞뒤(최대, 최소) 제거에 유리
*/

/*
    [체크할 내용]
    dequeue
     장점 : 앞뒤 삭제 용의
     단점 : 
        삽입시 정렬안됨.
        지금 상황에서는 삽입마다 정렬해야한다.

    priority_queue
    장점 : 정렬되서 들어간다.
    단점 :
        마지막 데이터 삭제 힘듦(pop) 밖에 없다.
        (현 상황에서는, 앞뒤 모두에서 삭제가 일어난다.)

    앞뒤 삭제 및 데이터 삽입이 빈번하게 발생할 것으로 예상.
    디큐로 일단 구현해본다.

    파싱 필요, 
    std::string의 함수 확인할 것.

    [기능]
    
    1. 파싱
    명령어 구조 : (문자열+공백) + 숫자  
    공백까지 문자열을 읽고, 분석
    이후 숫자 처리
    (유효성 검사 + 명령어 확인)

    2. 큐
    정수의 크기로 정렬된 자료 구조
    앞뒤 삭제 가능
    빈 큐일때 삭제 명령 무시
*/

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

enum eOPERATION
{
    eOP_INPUT = 0,
    eOP_DELETE,
    eOP_MAX,
};

//예약된 명령어 -> 별도 관리
const string OPERATION_INPUT    = "I";
const string OPERATION_DELETE   = "D";

struct stOPERATION
{
    eOPERATION op;
    int value;
};

bool comp(const int& a, const int& b)
{
    return a > b;
};

class cOperationDeque
{
    map<string, eOPERATION> operationList;            //예약어 리스트
    deque<int> que;

    //interface function
public:
    bool inputOperation(string operation);
    bool getResult(vector<int>& out);

    //class fuctions
    cOperationDeque();
    ~cOperationDeque();

    bool initalizeOperationList();

private:
    bool checkOperation(stOPERATION& out, string input);        //유효성 감사, 성공시 명령 만들기
    bool findOperation(eOPERATION& op, string str);
    bool excuteOperation(stOPERATION& op);                      //명령에 따라 동작

    bool push(int input);
    bool pop(int value);    //only 1 or -1 (pop MAX : 1, pop MIN : -1)
    
    const int front();        //return (가장 큰값)    비었을 경우 return 0
    const int back();         //return (가장 작은 값) 비었을 경우 return 0
};

/*
    [LOGIC]
    1. 파라미터 유효성 검사
    2. 유효할 시 명령어 생성
    3. 생성한 명령어 실행
*/
bool cOperationDeque::inputOperation(string _input)
{
    bool bResult = false;
    bool bSuccess = false;
    string& input = _input;
    stOPERATION op;

    //1. 유효성 검사 -> 성공시 명령어 제작
    bSuccess = checkOperation(op,input);
    if (bSuccess == false) goto lb_return;

    //3. 명령어 실행
    bSuccess = excuteOperation(op);
    if (bSuccess != true) goto lb_return;

    bResult = true;

lb_return:
    return bResult;
}

/*
    [기능]
    현재 큐의 최대값과 최소값을 담아 리턴
    큐가 비어있을 경우 (0, 0) 리턴

    [LOGIC]
    1. out.push(que.front)
    2. out.push(que.back)

    [output] 
    (최대값, 최소값0
    (que.front, que.back)

    [return]
    큐가 비어있지 않을 경우 true;
*/
bool cOperationDeque::getResult(vector<int>& out)
{
    bool bResult = false;
    
    //front(), back() 함수에서 유효성 검사 함. 또해도 문제는 없을듯.
    int max = front();
    int min = back();

    out.push_back(max);
    out.push_back(min);

    return bResult;
}

cOperationDeque::cOperationDeque()
{
    //Nothing
}

cOperationDeque::~cOperationDeque()
{
    //Nothing
}

bool cOperationDeque::initalizeOperationList()
{
    bool bResult = false;

    //커맨드가 추가 되어도 자동으로 되는 로직 추가할것.
    operationList.insert( { OPERATION_INPUT, eOP_INPUT } );
    operationList.insert( { OPERATION_DELETE, eOP_DELETE } );

    return bResult;
}


//음수값 검사 안됨...
bool isNumber(const string& str)
{
    bool bResult = true;
    const char* num = str.c_str();

    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(num[i]) == 0)
        {
            if (i == 0)
            {
                if (num[i] == '-')
                {
                    continue;
                }
                else
                {
                    bResult = false;
                    break;
                }
            }

        }
        
    }
    //for (char const& c : str)
    //{
    //    if (isdigit(c) == 0)
    //    {
    //        //숫자가 아닌 문자 존재
    //        bResult = false;
    //        break;
    //        
    //    }
    //}

    return bResult;
}

/*
    [설명]
    해당 문장을 파싱.
    우리의 명령어 체계와 일치 여부 검사
    
    [return]
    일치할 경우 true

    [주의]
    Check only Parameter invaildate

    [함수명 변경 고려]
    checkInput

    [LOGIC]
    공백을 기준으로 자른다.
    공백이 없으면 잘못된 명령어
    공백 앞의 문자가 D나 I가 아니면 잘못된 명령어
    공백 뒤의 문자가 숫자가 아니면 잘못된 명령어

    //함수명 변경 고려. 목적이 명확하지 않은 이름.
*/
bool cOperationDeque::checkOperation(stOPERATION& out, string _input)
{
    bool bResult = false;
    string input = _input;
    string spaceFront;  //공백 전
    string spaceBack;   //공백 후
    eOPERATION eOP = eOP_MAX;
    int value = 0;

    size_t spacePos = input.find(" ");
    if (spacePos == string::npos) goto lb_return;

    spaceFront = input.substr(0, spacePos);
    spaceBack = input.substr(spacePos + 1, input.size());

    //spaceFront가 명령어인지 확인하는 과정
    bResult = findOperation(eOP, spaceFront);
    if (bResult == false) goto lb_return;

    //spaceBack이 숫자인지 확인하는 과정
    //isNumeber는 음수를 검출하지 못한다. -> 수정. 
    //stoi는 실패시 익셉션을 발생 시킨다.
    if (isNumber(spaceBack) == false) goto lb_return;
    value = stoi(spaceBack);
    
    //결과값 저장
    out.op = eOP;
    out.value = value;

    //모든 과정 성공
    bResult = true;

lb_return:
    return bResult;
}

//입력한 명령어가 존재하는지 명령어 리스트에서 검사.
bool cOperationDeque::findOperation(eOPERATION& op, string input)
{
    bool bResult = false;
    
    auto operation = operationList.find(input);
    if (operation == operationList.end()) goto lb_return;
    op = operation->second;
    bResult = true;

lb_return:
    return bResult;
}

//Not Implements
bool cOperationDeque::excuteOperation(stOPERATION& op)
{
    bool bResult = true;

    switch (op.op)
    {
    case eOP_INPUT:
        bResult = push(op.value);
        break;
    
    case eOP_DELETE:
        bResult = pop(op.value);
        break;

    default:
        //예약된 작업중에 없다?
        //aseert(false);
        bResult = false;
        break;
    }

    return bResult;
}


//
bool cOperationDeque::push(int input)
{
    bool bResult = true;
    que.push_back(input);
    sort(que.begin(), que.end(), comp);

    return bResult;
}

//[개선 필요]파라미터 검사 효율 및 확장 유연성 떨어짐
bool cOperationDeque::pop(int value)
{
    bool bResult = true;
    int val = value;
    
    if (que.size() == 0) goto lb_return;

    if (val == 1)
    {
        //최대값 제거.
        que.pop_front();
    }
    else if (val == -1)
    {
        //최소값 제거
        que.pop_back();
    }
    else
    {
        //잘못된 파라미터
        bResult = false;
    }

lb_return:
    return bResult;
}

const int cOperationDeque::front()
{
    int iResult = 0;
    if (que.size() == 0) goto lb_return;
    iResult = que.front();

lb_return:
    return iResult;
}

const int cOperationDeque::back()
{
    int iResult = 0;
    if (que.size() == 0) goto lb_return;
    iResult = que.back();

lb_return:
    return iResult;
}


vector<int> solution(vector<string> operations) {
    vector<int> answer;
    cOperationDeque opHandler;
    size_t safeCnt = 0;
    //커맨드 초기화
    opHandler.initalizeOperationList();

    
    //함수화?
    for (auto& it : operations)
    {
        bool bSuccess = opHandler.inputOperation(it);       //핵심 함수
        if (bSuccess == false)
        {
            //실패 -> 잘못된 파라미터
            //assert(false);
            break;
        }
        safeCnt++;
    }

    //커맨드 실행 검증.
    if (operations.size() != safeCnt)
    {
        //asert(false);
        //잘못 된 명령어 등의 오류 가능성 존재.
        int a = 0;
    }

    bool bSuccess = opHandler.getResult(answer);
    {
        //함수 실패
    }

    return answer;
}






int main()
{

    //return (0, 0)
    //vector<string> operations = { "I 16", "D 1" };

    //[7, 5]
    vector<string> operations = { "I 7", "I 5", "I -5", "D -1" };

    //(0, 0)
    //vector<string> operations = { "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" };
      
    vector<int> result = solution(operations);


    //결과 출력
    printf("결과값은 : \n");
    for (auto& it : result)
    {
        printf("%d \n", it);
    }


    return 0;
}