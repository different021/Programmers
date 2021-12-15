/*
    0 �̻��� ���� �迭�� ��ġ�Ͽ� ���� ū �� �����

    ex)
     input :
        [6, 10, 2] (int number[])
     return: 6210  (char* answer)

     [6102, 6210, 1062, 1026, 2610, 2106] ������ ��

     number �迭 ���� 1 ~ 100000
     number ũ�� 0 ~ 1000

     ���ڰ� �ʹ� Ŭ �� ������ ���ڿ��� ����


    ex)
     numbers	        return
    [6, 10, 2]	        "6210"
    [3, 30, 34, 5, 9]	"9534330"

*/

/*
    //solution
    ���õ� ���ڸ� ���� ū �ڸ����� �ڸ����� ���� ū ����
    ���ٸ� �ι�° �� ��

    1. vector�� ��´�.
    2. �����Ѵ�.
    3. ����� char*�� ����

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
        //ù��° ���� 0�̸� ��� 0�̴�.
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
    ���õ� �� ������ Ÿ���� ������ ������ ����� �Լ�


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
    
    //�����÷� ����å �߰��� ��.
    GetDigit(nDigitTail, tail);             //�ڸ��� Ȯ��
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
    if (n < 0) goto lb_return;     //���� �������� ��ȿ�� �Լ�

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