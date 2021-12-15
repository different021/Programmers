/*
    0 이상의 정수 배열을 배치하여 가장 큰 수 만들기

    ex)
     input :
        [6, 10, 2] (int number[])
     return: 6210  (char* answer)

     [6102, 6210, 1062, 1026, 2610, 2106] 가능한 수

     number 배열 길이 1 ~ 100000
     number 크기 0 ~ 1000

     숫자가 너무 클 수 있으니 문자열로 리턴


    ex)
     numbers	        return
    [6, 10, 2]	        "6210"
    [3, 30, 34, 5, 9]	"9534330"

*/

/*
    //solution
    제시된 숫자를 가장 큰 자리수의 자리수로 정렬 큰 순서
    같다면 두번째 수 비교

    1. vector에 담는다.
    2. 정렬한다.
    3. 결과값 char*에 쓰기

*/

#include <string>
#include <vector>
#include <algorithm>

#define MAX_DIGIT 4

using namespace std;

bool comp(const int& a, const int& b);
int AppendInt(const int& head, const int& tail);

bool GetDigit(int& out, int number);

string solution(vector<int> numbers) {
    string answer = "";
    size_t stringSize = 0;

    sort(numbers.begin(), numbers.end(), comp);
    
    if (numbers.at(0) == 0) {
        //첫번째 수가 0이면 모두 0이다.
        answer += to_string(0);
        goto lb_return;
    }
    
    for (auto it : numbers) {
        int num = it;
        answer += to_string(num);
    }

lb_return:
    return answer;
}

bool comp(const int& a, const int& b) {
    bool bResult = false;
    int A = 0;
    int B = 0;
    
    if (a == 0)
    {
        goto lb_return;
    }

    if (b == 0) {
        bResult = true;
        goto lb_return;
    }

    if (a == b) {
        goto lb_return;
    }

    A = AppendInt(a, b);
    B = AppendInt(b, a);

    if (A > B)
        bResult = true;

lb_return:
    return bResult;;
}

/*
    제시된 두 정수형 타입을 연결한 정수를 만드는 함수


*/
int AppendInt(const int& head, const int& tail)
{
    int nResult = -1;
    int nMul = 1;
    int nDigitTail = 0;

    if (head < 0) goto lb_return;
    if (tail < 0) goto lb_return;
    if (head == 0 && tail == 0) 
    {
        nResult = 0;
        goto lb_return;
    }
    
    //오버플로 예방책 추가할 것.
    GetDigit(nDigitTail, tail);             //자리수 확인
    for (int i = 0; i < nDigitTail; i++) 
    {
        nMul *= 10;
    }

    nResult = head * nMul + tail;

lb_return:
    return nResult;
}

bool GetDigit(int& out, int number) {
    bool bResult = false;
    int n = number;
    int digit = 0;
    if (n < 0) goto lb_return;     //양의 정수에만 유효한 함수

    while ( n != 0) {
        n = n / 10;
        digit++;
    }

    bResult = true;
    out = digit;

lb_return:
    return bResult;
}

int main()
{
    //vector<int> arr = { 3, 30 };
    //vector<int> arr = { 0, 0, 0, 1 };
    //vector<int> arr = { 67, 676, 677 };   //67767676
    vector<int> arr = { 67, 676 };
    //vector<int> arr = { 0, 0, 0, 0 };
    //vector<int> arr = { 3, 30, 34, 5, 9};
    //vector<int> arr = { 10, 101 };
    //vector<int> arr = { 100, 11, 1, 101 };

    string answer = solution(arr);
    printf("%s\n", answer.c_str());

    return 0;
}