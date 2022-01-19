/*
    숫자 N만 이용하여 number를 만드시오
    -사칙 연산과 숫자 N을 이용하여 number를 만들어야 한다.
    -숫자 N을 사용하는 최소 횟수를 리턴하시오

    [예제]
    N = 5, number = 12
    12 = 5 + 5 + (5 / 5) + (5 / 5)      N 사용 : 6회   
    12 = 55 / 5 + 5 / 5                 N 사용 : 5회
    12 = (55 + 5) / 5                   N 사용 : 4회

    최소 사용 4회

    [제한 사항]
    N : 1 ~ 9
    number = 1 ~ 32000
    수식 : 괄호와 사칙 연산 가능
    나누기 연산시 나머지 무시
    최소값이 8 이상 일 경우 -1 리턴
*/


/*
    [가능한 행동]
    1. 사칙 연산
    3. 연속 숫자
    2. 괄호 (열기 닫기 순서 쌍) - 사칙연산에 스택에 포함되지 않는다.
*/

/*
    1. 최소 사용 값 확신을 위한 너비 우선 탐색
    2. 
    연산에 대한 enum 값 지정.
    enum을 활용한 state값 생성
    클래스에서 상태 생성
    상태를 statePool에서 검색
    새로운 상태는 que.push
    
    
*/

/*
    1. 너비우선 탐색
    2. 새로운 상태 생성 후 스테이트풀에 넣기.
    
*/


#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct cExpression
{
public:
    int id; //for test
    vector<string> operationArray;


public:
    cExpression();
    cExpression(const cExpression&);
    string GetState();
    void CopyTo(cExpression& out);
    bool AddOperation(const string& op);
};

cExpression::cExpression()
{
    //Nothing.
}

cExpression::cExpression(const cExpression& src)
{
    //멤버 복사. 
    //문제 상 8개를 넘지 않을거라 하여 복사하지만 많아지면 성능에 문제 생길지도.
    operationArray.assign(src.operationArray.begin(), src.operationArray.end());
    //operationArray = src.operationArray;
}

string cExpression::GetState()
{
    string result = "";
    for (auto& it : operationArray)
    {
        result + it;
    }

    return result;
}

void cExpression::CopyTo(cExpression& out)
{
    out = *this;
}

//복사 생성자를 만들어 주었으니, 객체를 복사 생성하여, 새로운 오퍼레이터를 추가하는 방식으로 새로로운 상태를 생성할 것.
bool cExpression::AddOperation(const string& op)
{
    bool bResult = false;

    operationArray.push_back(op);

    bResult = true;
    return bResult;
}


//operationPool - 우선 순위가 저장된 문자열
void operationInitailze(unordered_map<string, int>& operationPool);

int solution(int _N, int _number) {
    int answer = -1;
    int N = _N;
    int number = _number;
    unordered_map<string, int> operations;
    unordered_map<string, cExpression> statePool;
    cExpression exp;
    cExpression test;

    //연산자 우선 순위 설정
    operationInitailze(operations);

    


    return answer;
}

void operationInitailze(unordered_map<string, int>& operationPool)
{
    operationPool.insert(make_pair("+", 0));
    operationPool.insert(make_pair("-", 0));
    operationPool.insert(make_pair("*", 1));
    operationPool.insert(make_pair("/", 1));
    operationPool.insert(make_pair("_", 2));
}



int main()
{
    int N = 5;
    int number = 12;
    int result = solution(N, number);
    
    printf("%d\n", result);

    return 0;
}