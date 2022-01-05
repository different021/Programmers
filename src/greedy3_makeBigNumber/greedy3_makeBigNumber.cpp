/*
    � ������ k���� ���� ���� ������, ���� ū ���� ���Ͻÿ�.

    [param]
    string number   : � ��
    int k           : ������ ����

    [return]
    int             : number���� k���� ���� ���� ��, ���� ū ��

    [����]
    number  : 1924
    k       : 2

    ���� ������ �� :  [19, 12, 14, 92, 94, 24]

    return  : 94 (���� ū ��)

    1924�� �ΰ��� ���ڸ� ���� �ϸ�, 2�ڸ� ���� �ȴ�. 
    ���� ������ ���ڸ� ���� 19, 12, 14, 92, 94, 24 �̴�.
    �� ��, ���� ū ���� 94


    [���� ����]
    number.size : 1 ~ 10000000
    k           : 1 < k < number.size

*/

/*
    [solution]
    1. ������ ���� ��� ���� ��, ����
    2. ���� �� ��� ����.

    �� ��� ��� ������ �ٲ� ���� ����.
    �ٸ� �߰��� ���� �ٲ� �� �ִ�.

    [��� 1]
    1. ���� ������ ��� �� ���� 
    2. �������� ����

    ����. ���ڰ� Ŀ���� ��� ���� ������ ���ϰ� �ִ�. ���� ũ�� (1 ~ 1000000)
    �ڸ����� ū ����� Ż��.


    [��� 2] -> ä��
    1. i���� k��° ���� �� �� ���� ū �� ã��
    2. ���� ū�� ���� �� n�� ����
    3. i ��° �� Ȯ��
    (i + 1)��°���� 2 ~ 3 �ݺ�

    [i��° �ڸ��� Ȯ�� ���]
    1. ���� �ڸ����� ������ ���ڰ� ���ٸ� ���� ����.
    2. i��° ������ d���� �� �� ���� ū ���� ã�´�.
    3. ���� ū �� ���� ���� ���ڵ��� ����
    
    
    nubmer = 1942, k = 2

    string�� i��° ���� k ��° �� �ִ밪�� �ε��� n ã�� 
    
    
    string 
    
    ("1942", 2) �� 0���� 1���� �� �ִ밪 9 �ε��� 1
    ("942, 1)  0�� �ε��� 1�� ����
    0�� �ε��� Ȯ��,

    ("942", 1) 1�� �ε��� ���� 


    
    <���� �۾�>
    string�� �ϳ��ϳ� int�� ��ȯ
    �߰� ������ ������ �ڷᱸ���� �ִ´�.
    ����Ʈ�� ������ ��������
    ����Ʈ�� �ε��� ���ٿ� ������ ���� �ִ�.
    �ε��� ���ٿ� �����ϵ��� ���� ���

    <���� �۾�>
    ���ڵ��� ���ڿ��� �ٲپ� ����.
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
    int num = k;        //������ ����

    //�Ķ���� ���� ��ƾ �߰�.
    /* �Ķ���� ���� */

    //number�� ����ϱ� ���� ���·� ����
    bool bSuccess = solutionInitialize(numList, number);
    if (bSuccess == false) { /*�ʱ�ȭ ���� �ڵ� ���ڿ��� ���ڰ� �ƴ� ���� ���� �ִ� ��츦 ���� �ǽ�*/ };

    bSuccess = solutionGetBiggestNumber(answer, numList, num);

    return answer;
}

/*
    @detail ���н� out = 0, ������ 0�϶��� out = 0, return���� �Լ��� ��ȯ ���� ���θ� �˷��ش�.
    @param  out : output, pChar : src
    @return �Լ� ���� ���� 0�ϰ�� �˻�.     
*/
bool GetDigit(int& out, char* pChar)
{
    bool bResult = true;

    int num = atoi(pChar);  
    if (num == 0)   //���н� 0����
    {
        if (*pChar != '0')  bResult = false;
    }

    //return
    out = num;

lb_return:
    return bResult;
}

/*
    @detail     �־��� ���ڿ�(������ ���ڷ� �̷����)�� ���ڷ� ��ȯ�Ͽ� ����Ʈ�� �־��ִ� �Լ�.
    @param      out : _number�� ���ڷ� ��ȯ�ؼ� �־��ִ� ����Ʈ(output), _number ���ڷ� �ٲ��� ���ڿ�(���ڿ� ���� ���� ��� ���ڷ� ��ȯ �����ؾ��Ѵ�.)
    @return     �Լ� ���� ����. ��� ���� 
    @warning    _number�� ���ڷ� ��ȯ���� ���ϴ� ��� return false; ������ �������� �ʴ´�.
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
        if (bSuccess == false) { bResult = false; /* ��ȯ ���н� ó�� ��� �߰� */ };
        out.push_back(num);     //�������� ����
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