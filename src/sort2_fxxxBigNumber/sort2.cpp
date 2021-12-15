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
bool comp2(const int& a, const int& b);
bool GetI(int& out, int index, int number);
bool GetNDigitNumber(int& result, int& outMoreDigit, int num, int nDigit);
bool GetDigit(int& out, int number);

string solution(vector<int> numbers) {
    string answer = "";
    size_t stringSize = 0;

    sort(numbers.begin(), numbers.end(), comp2);
    
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

//파라미터가 1000이하인지 검증하지 않는다. 
//파라미터 1000 검증이 완료된 상태라고 가정
/*
    1. 각각 몇자리 수인지 계산
    
    2. 자릿수 비교
    3. 큰쪽이 이김
    4. 같은 경우
     4_1. 다음 자릿수
     4_2. 다음 자릿수가 없는 경우는 그대로 유지
    

 */
bool comp(const int& a, const int& b) {
    bool bResult = false;
    int numberA = a;
    int numberB = b;
    int iA = 0;
    int iB = 0;

    for (int i = 0; i < 4; i++) {
        GetI(iA, i, numberA);
        GetI(iB, i, numberB);

        if ((iA < 0) || (iB < 0) ) {
            //두수의 곱이 음수일 경우
            //둘 중 하나 outofIndex
            if (iA == 0)
            {
                //bResult = false;
                break;
            }
            else if (iB == 0) {
                bResult = true;
                break;
            }

        }

        if (iA > iB) {
            bResult = true;
            break;
        }
        else if (iA < iB) {
            //bResult = false;
            break;
        }
        
        //두 수가 같을 때만 반복
    }
    
lb_return:
    return bResult;
}

bool comp2(const int& a, const int& b) {
    string strA = to_string(a);
    string strB = to_string(b);
    string firstA, firstB;
    

    firstA = strA + strB;
    firstB = strB + strA;

    int A = atoi(firstA.c_str());
    int B = atoi(firstB.c_str());

    return A > B;
}
//가장 큰자리 인덱스 0
/*
    [parameter]
    out     : src의 index번째 숫자 리턴
    index   : 구하길 원하는 자리 (가장 큰 자릿수 부터 0)
    number  : 계산할 대상이 될 수
    
    [return]
    bool : 함수 성공 여부

    ---------------중요------------------
    [outofIndex일 경우]
     out = -1

    ex)
    index   |   0123
    num     |   5872

        (num)   (index)
    숫자 5872에서 0번째 수는 5
    숫자 5872에서 2번째 수는 7
    숫자 5872에서 7번째 수는 5(가장 앞 자리 수)
    
*/
bool GetI(int& out, int index, int number) {
    bool bResult = false;
    int num = number;
    int digit = 0;
    int result = -1;
    int div = 1;

    if (number < 0) goto lb_return;

    GetDigit(digit, num);

    if (digit - 1 < index) {
        //가장 앞자리 수 리턴
        for (int i = 0; i < digit - 1; i++) {
            div *= 10;
        }
        //result = num / div;
        result = -1;
    }
    else {
        for (int i = 0; i < digit - index - 1; i++) {
            div *= 10;
        }
        int overOne = num / (div);
        result = overOne % 10;
    }
        
    bResult = true;
    out = result;
lb_return:
    return bResult;
}

bool GetNDigitNumber(int& result, int& outMoreDigit, int num, int nDigit) {
    bool bResult = false;
    int number = num;
    int iDigitA = 0;
    int moreA = 0;
    int cnt = 1;

    if (number < 0) goto lb_return;

    GetDigit(iDigitA, number);
    moreA = nDigit - iDigitA;

    for (int i = 0; i < moreA; i++) {
        cnt *= 10;
    }

    result = number * cnt;
    outMoreDigit = moreA;
    bResult = true;

lb_return:
    return bResult;
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
    //vector<int> arr = { 67, 676 };
    vector<int> arr = { 0, 0, 0, 0 };
    //vector<int> arr = { 3, 30, 34, 5, 9};
    //vector<int> arr = { 10, 101 };
    //vector<int> arr = { 100, 11, 1, 101 };

    string answer = solution(arr);
    printf("%s\n", answer.c_str());

    return 0;
}