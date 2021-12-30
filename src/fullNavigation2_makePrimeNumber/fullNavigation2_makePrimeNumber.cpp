
/*
    ���ڷ� �̷���� ���ڿ��� �̿��� �Ҽ�(prime number)�� ������

    [�Ķ����]
    string : ���ڷ� �̷���� ���ڿ�

    [����]
    int : �־��� ���ڿ��� ���� �� �ִ� �Ҽ� ����

    [����]
    numbers.size() : 1 ~ 7
    numbers �� 0 ~ 9 ������ ���ڸ����� �̷�� �� �ִ�.
    "013" �� 0, 1, 3�� �̿��� ����� �ִ� �Ҽ��� ã����� ��
    { 3, 13, 31 } 3���� �Ҽ��� ����� �ִ�.

    [����1]
    numbers     return 
    "17"        3
    
    { 7, 17, 71 } 3���� �Ҽ��� ���� �� �ִ�.

    [����2]
    numbers     return
    "011"       2

    { 11, 101 } 2���� �Ҽ��� ���� �� �ִ�.

*/

/*
    [SOLUTION]
    1. �־��� ���ڿ��� �ϳ��� �ɰ���. (+ ���� ���� ����)
    2. ���� (%�ʼ�%)
    3. ������ ��� �� ����
    4. ������ �� map�� ���� (�ߺ�����)
    5. map�� ����� ��� ���� ���� �Ҽ� �˻�
    6. ����
*/

/*
    [�� ����]
    ���ڸ� �̿��� ���� ������ ��� ���ڸ� �����ϴ� ���
    
    vector<string> src 
    [������ �Ķ����]
    1. src�� 1�ڸ� ������ string���·� ����Ǿ� �ִ٤�.
    2. src�� ������������ ���ĵǾ� �ִ�.
        
    next_permutation �Լ��� �̿��ؼ� ǰ. ���ϳ�.
    ������ ���� ������������ ���ĵǾ� �־���Ѵ�.
    ���� ������ �̵��ϸ� �����ϱ� ������ ���ĵǾ� ���� �ʴٸ� �߰����� ���

*/

/*
    [�Ҽ� �˻�]
    bool CheckPrimeNumber(int input);

    input�� 2 ~ input�� ������ ������ ���� ������ Ȯ��
    


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

//����? �� �ƴϰ� solution�� ���ӵ��� ���� �Լ�
bool CheckPrimeNumber(int input);
bool CheckStrToDigit(const char& singleDigit);
bool CompSingleDigit(const string& a, const string& b);

int solution(string numbers) {
    int answer = 0;
    bool bSuccess = false;
    string& input = numbers;
    vector<string> strNumbers;    //�и��� ���ڸ� ����
    map<int, int> newNumbers;        //�и��� ���ڸ� �������� ���� ������ ���� ����

    //1. �и� (+���� ����) & 2. ���� 
    bSuccess = SolutionCutEverySingleChar(strNumbers, input);
    if (bSuccess == false) {/* �߸��� ���ڿ� ���� */ };

    //�������� ���� -> ���� �ɵ�.
    sort(strNumbers.begin(), strNumbers.end(), less <string>());

    //3.���������� ��� �� ����.
    //int test = atoi("0011"); -> test = 11 -> �԰��� ���ϳ�....
    bSuccess =  SolutionMakeNumberBySingleDigit(newNumbers, strNumbers);
    if (bSuccess == false) { /* �ѹ� ���� ����?! */ };

    //4. �Ҽ� �˻�
    bSuccess =  SolutionCountPrimeNumber(answer, newNumbers);
    if (bSuccess == false) { /* �Ҽ� ���� ����?! -> �Ķ���� Ȯ�� */ };

    int a = 0;

    return answer;
}


/*
    [����]
    �ǵ����� ���� ���ڿ��� ���Եǵ� ������ �ʴ´�. ex) aBC102, -5432 ���
    ��, ���ڵ��� ������ ���� �ȴ�.  ex)  {"1", "0", "2" }, { "5", "4", "3", "2" }
    ��� ���ϰ��� false�� �ȴ�.
     

    1. �־��� ������ �ѱ��� �и�
    2. �и��� �� ���� ���� ���� Ȯ��
    3. is(����)
        true  -> ����
        false -> bResult = fale, (����! �Լ��� �������� �ʴ´�)
    4. 1~3 �ݺ�(���ڿ��� ��ü �˻��� ����)
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
            //�ѹ� �����ص� ���ڿ��� �ݺ��Ǳ� ������ ������ üũ ������ �ִ�.
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
    [����]
    �Ķ���� vector<string> src�� �����
        1. ���ڸ�  
        2. ���� ���� { 0 ~ 9 }
    �� �����ϴ� �����̿��� �Ѵ�.
        ex) { "1", "2", "3" } ���� ���

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
    Prime Number �� ����

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
    �Է¹��� ���� prime Number ���� Ȯ��
    2 ~ sqrt(input) ���� ���� input�� ��������.
    ���� �̷л� �����ٱ����� �������� prime number��� �Ѵ�.
*/
bool CheckPrimeNumber(int input)
{
    bool bResult = true;
    int square = static_cast<int>(sqrt(input));

    //2���� ����
    for (int i = 2; i < square; i++)
    {
        int remainder = input % i;
        if (remainder == 0)
        {
            //������ �������� ���� �ִٸ� ������ �ѹ��� �ƴϴ�.
            bResult = false;
            break;
        }
    }

    return bResult;
}

//�ش� ���ڰ� ������ ��ȯ �������� üũ�Ѵ�. 
//�ش� �ַ�ǿ����� ������ ������ �ȵ� ���̳�
//�ٸ� �ַ�ǿ����� ������ ����� ���� ������ ������ �ʾҴ�.
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
        //isdigit�� "0"�� �������� ���Ѵ�.
    }

    return bResult;
}

/*
[����]
������ ���͸� ���� ��.
������ ��Һ� ������ ����.
�̹� ������ ���͸� ����Ѵٰ� ������ �Լ�

[�뵵]
���Ϳ� ����� ���ڿ��� ���ڷ� ��ȯ ��, �������� ����

atoi()�� ���� exception �߻� ���ɼ� ����.
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

    printf("����� �ִ� �Ҽ� ���� : %d \n", result);

    return 0;
}