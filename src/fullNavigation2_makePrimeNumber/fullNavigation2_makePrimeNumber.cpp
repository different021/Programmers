
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
    [solution]
    1. �־��� ���ڿ� �и� (+���ڰ� �´��� ����)
    2. �и��� ���� ����
    3. ����� ���ڸ� ������ ���ο� �� ����
    4. ������ �� �Ҽ����� ����
    5. �Ҽ� ���� ī��Ʈ & ����
*/

/*
    [�� ����]
    ���ڸ� �̿��� ���� ������ ��� ���ڸ� �����ϴ� ���
    
    vector<string> src 
    [������ �Ķ����]
    1. src�� 1�ڸ� ������ string���·� ����Ǿ� �ִ٤�.
    2. src�� ������������ ���ĵǾ� �ִ�.


    src[i]

*/
/*
    [�Ҽ� �˻�]

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
    sort(strNumbers.begin(), strNumbers.end(), CompSingleDigit);

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
        //���ڿ� �� ������.
        string last;

        //��������
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
    //1��
    //func1(out, src);
    for (int i = 0; i < src.size(); i++)
    {
        string temp1;
        temp1 = src[i];
        int iTemp = atoi(temp1.c_str());
        out.insert(make_pair(iTemp, iTemp));
    }

    //2��
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
    
    //3��
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

    //4��    
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

//������ ������ ������ �ѹ��� ��ϱ��?
//���� �⼧�� ���ؼ���
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
    //return 5 { 7 , 17k 71, 107, 701 } 
    string numbers = "1307";

    int result = solution(numbers);

    printf("����� �ִ� �Ҽ� ���� : %d \n", result);

    return 0;
}