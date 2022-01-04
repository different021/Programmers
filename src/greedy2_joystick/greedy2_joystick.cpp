/*
    [���̽�ƽ]
    ���� ������ ������ ����� ����� �̸��� �Է��ϴ� â�� ���Դ�.
    �翬�� Ű���尡 ������ ���̽�ƽ�� �̿��� �̸��� �Է��ϰ�� �ߴ�.
    �������忡�� �Է��ϴ� ����� �־�����
    
    AAAA

    ������ �Էµ� ���ڿ��� ���� ��ƽ���� �ٲٴ� ��쵵 �ִ�.

    ���̽�ƽ�� �Է��� �ϸ� ������ ���� �����Ѵ�.
    �� : ���� ����.
    �Ʒ� : ���� ����.
    ������ : ������ ����
    ���� : ���� ����

    �� �̵� �ߴ�.
    �̶� A���� ���� ���� (�Ʒ�) �Է½� Z
    ���� �� ���ڿ��� ���� �Է½� ���� �� ���ڷ� �̵� �ϰ� �ȴ�.

    �Է� ���� ���ڿ��� �Է��ϴ� ���� ���� Ƚ���� ���϶�

    "INPUT" �̶�� ���ڿ��� �Է��ϸ� AAAAA(5����)�� �����Ѵ�.

    [�Ķ����]
    string name : �Է��� ���ڿ�
    
    [���]
    int : �ּ� �Է�Ƚ��

*/


/*
    ���Ĺ� ����  �ʿ� ���� ȹ��
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
    M       12      12  �� �̵� ����
    N       13      13  ��ȭ �̵� �������
    O       14      12  �� �̵� ����
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
    [���� �̵� ���Ҹ�]
    A ~ M ������ ���ڴ� (��) �̵� ����
    N ~ Z ������ ���ڴ� (��) �̵� ����
*/

/*
    [�¿� �̵� ���Ҹ�]
    1. �� �̵� (�⺻)
    2. �� �̵� 
    3. �� �̵� ��, �� �̵�
    4. �� �̵� ��, �� �̵�


    ABAAB

    AAAA    -> KAAN
    AAA     -> CAABN

    ù���� ����
    prefix�� ���ӵ� A��

    suffix�� ���յ� A ���� ��


        KADBBDAA
    ->  ADBBDAA  (�չ���(K) ���� )
    prefix: ���� A 1��
    suffix: ���� A 2��

    �պκ� ���� ���۵Ǵ� ���ӵ� A�� ���� �� �켱 Ž�� 

    prefix�� ���� A�� ���� -> �� �̵� 
    suffix�� ���� A�� ���� -> �� �̵�



*/

/*
    [solution]
    1. ���ڿ� �¿� �̵� ���Ҹ� �� Ƚ�� �Ǵ�
    2. ���ڿ� ���� �̵� ���Ҹ� �� Ƚ�� �Ǵ�
    3. ���� (1, 2) ��� �ջ�
    
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

//���ں� ���� Ƚ�� ����� map
void OperationNumberInitialize(map<char, int>& OperationNumberPerChar);

//solution class
int solution(string name);
int solutionGetNumberOfLateralMovement(string input);           //���ڿ� ���̵� ��
int solutionGetNumberOfVerticalMovementString(map<char, int>& OperationNumberPerChar, string& input);   //���ڿ� Ⱦ�̵� ��
int solutionGetNumberOfVerticalMovementSingleChar(map<char, int>& OperationNumberPerChar, const char input);  //���� �ϳ� Ⱦ�̵� ��

int solution(string name) {
    map<char, int> operationNumberPerChar;        //���ں� �ʿ� ���� Ƚ�� ����
    int answer = 0;
    string& input = name;
    

    OperationNumberInitialize(operationNumberPerChar);
    
    //Ⱦ�̵� �ʿ� Ƚ�� ���
    int nReteralMove = solutionGetNumberOfLateralMovement(input);
    int nVerticalMove = solutionGetNumberOfVerticalMovementString(operationNumberPerChar, input);

    answer = nReteralMove + nVerticalMove;

    return answer;
}


/*
    @detail �� ���ڸ� �Է��ϴµ� �ʿ��� ���̵� Ƚ�� (���̽�ƽ ���� ����)
    @param  operationNumberPerChar �ʱ�ȭ ��ų ���
    @return void
*/
void OperationNumberInitialize(map<char, int>& operationNumberPerChar)
{
    char ch = 'A';
    int numberOfOperation = 0;

    //��
    for (int i = 0; i < 13; i++)
    {
        operationNumberPerChar.insert( make_pair(ch, i) );
        ch++;
    }

    //�Ʒ�
    for (int i = 13; i > 0; i--)
    {
        operationNumberPerChar.insert(make_pair(ch, i));
        ch++;
    }

    //�ҹ���
    char smallCh = 'a';
    //����Ű ��
    for (int i = 0; i < 13; i++)
    {
        operationNumberPerChar.insert(make_pair(smallCh, i));
        smallCh++;
    }

    //����Ű �Ʒ�
    for (int i = 13; i > 0; i--)
    {
        operationNumberPerChar.insert(make_pair(smallCh, i));
        smallCh++;
    }
}

int GetCountOfConsecutivePrefixA(string str)
{
    int result = 0;
    char ch = 'A';
    size_t half = static_cast<size_t>(str.size()) / 2;

    for (int i = 1; i < half + 1; i++)
    {
        if (str[i] == ch)
        {
            result++;
        }
        else
        {
            //���ӵ��� ������ �ǹ� ����?
            break;
        }
    }

    return result;
}

int GetCountOfConsecutiveSuffixA(string str)
{
    int nResult = 0;
    size_t size = str.size();
    size_t half = static_cast<size_t>(str.size()) / 2;

    for (int i = size - 1; i > half; i--)
    {
        if (str[i] == 'A')
        {
            nResult++;
        }
        else
        {
            //���ӵ� ���� ����.
            break;
        }
    }

    return nResult;
}

int GetCountContinueA(string str)
{
    int nReturn = 0;
    int temp = 0;
    char ch = 'A';

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != ch)
        {
            nReturn = (nReturn > temp) ? nReturn : temp;
            temp = 0;
        }
        else
        {
            temp++;
        }
        
    }

    nReturn = (nReturn > temp) ? nReturn : temp;

    return nReturn;
}

/*
    @detail Ⱦ�̵� Ƚ���� �����ִ� �Լ�
    @param  input �Է��ϰ����ϴ� ���ڿ�
    @return int Ⱦ�̵� Ƚ��
    @warning ���ϰ��� ���ڿ��� ����� ���� �� ����.
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
    int midOfContinueA = 0;

    bool bMoveLeft = false;    //�� �̵� �ұ��?

    if (size < 3)
    {
        nResult = size - 1;
        goto lb_return;
    }

    midOfContinueA = GetCountContinueA(str);

    //GetCountOfConsecutivePrefixA
    cntOfPreifxA = GetCountOfConsecutivePrefixA(str);

    //GetCountOfConsecutiveSuffixA
    cntOfSuffixA = GetCountOfConsecutiveSuffixA(str);
    
    //�Լ�ȭ?
    if (midOfContinueA >= half)
    {
        //n�� ���� �� ���� ���Ѵ�.
        int small, big = 0;
        int prefix = 0, suffix = 0;

        //�ո鿡 
        for (int i = half; i > 0; i--)
        { 
            char chA = 'A';
            if (str[i] != chA)
            {
                prefix = i;
                break;
            }
        }


        for (int i = half; i < size; i++)
        {
            char chA = 'A';
            if (str[i] != chA)
            {
                suffix = size - i;
                break;
            }
        }

        if (prefix > suffix)
        {
            small = suffix;
            big = prefix;
        }
        else
        {
            small = prefix;
            big = suffix;
        }


        nResult = 2 * small + big;
        goto lb_return;
    }
    
    //�Լ�ȭ?
    if (cntOfPreifxA > cntOfSuffixA)
    {
        //���̵��� Ƚ���� �� ����.
        bMoveLeft = true;   
    }

    if (bMoveLeft)
    {
        //��������
        //���ӵ� A ��ŭ �̵��� �ʿ䰡 ��������.
        for (int i = 1; i < size; i++)
        {
            if (str[i] != 'A') break;
            notmoveCount++;
        }

    }
    else
    {
        //������ �̵�
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
    @detail ���ڿ� ��ü�� ���� ���̵� ���� ���� ���
    @param  input ���̵� Ƚ���� �˰���� ���ڿ�
    @return int �� ���̵� Ƚ��
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
    @detail ���� �ϳ��� ���� ���̵� �� 
    @param  input ���̵� Ƚ���� �˰���� ���� �ϳ�
    @return int ���̵� Ƚ��
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

    //0
    //string name = "AAA";

    //5 
    string name = "ABAAB";

    int result = solution(name);

    printf("����� : %d \n", result);


    //string test = "AKCAAAAAAABVAAA";
    //int small = GetCountContinueA(test);
    //printf("���ӵ� A�׽�Ʈ : %d", small);

    return 0;
}