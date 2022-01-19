/*
    ���� N�� �̿��Ͽ� number�� ����ÿ�
    -��Ģ ����� ���� N�� �̿��Ͽ� number�� ������ �Ѵ�.
    -���� N�� ����ϴ� �ּ� Ƚ���� �����Ͻÿ�

    [����]
    N = 5, number = 12
    12 = 5 + 5 + (5 / 5) + (5 / 5)      N ��� : 6ȸ   
    12 = 55 / 5 + 5 / 5                 N ��� : 5ȸ
    12 = (55 + 5) / 5                   N ��� : 4ȸ

    �ּ� ��� 4ȸ

    [���� ����]
    N : 1 ~ 9
    number = 1 ~ 32000
    ���� : ��ȣ�� ��Ģ ���� ����
    ������ ����� ������ ����
    �ּҰ��� 8 �̻� �� ��� -1 ����
*/


/*
    [������ �ൿ]
    1. ��Ģ ����
    3. ���� ����
    2. ��ȣ (���� �ݱ� ���� ��) - ��Ģ���꿡 ���ÿ� ���Ե��� �ʴ´�.
*/

/*
    1. �ּ� ��� �� Ȯ���� ���� �ʺ� �켱 Ž��
    2. 
    ���꿡 ���� enum �� ����.
    enum�� Ȱ���� state�� ����
    Ŭ�������� ���� ����
    ���¸� statePool���� �˻�
    ���ο� ���´� que.push
    
    
*/

/*
    1. �ʺ�켱 Ž��
    2. ���ο� ���� ���� �� ������ƮǮ�� �ֱ�.
    
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
    //��� ����. 
    //���� �� 8���� ���� �����Ŷ� �Ͽ� ���������� �������� ���ɿ� ���� ��������.
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

//���� �����ڸ� ����� �־�����, ��ü�� ���� �����Ͽ�, ���ο� ���۷����͸� �߰��ϴ� ������� ���ηο� ���¸� ������ ��.
bool cExpression::AddOperation(const string& op)
{
    bool bResult = false;

    operationArray.push_back(op);

    bResult = true;
    return bResult;
}


//operationPool - �켱 ������ ����� ���ڿ�
void operationInitailze(unordered_map<string, int>& operationPool);

int solution(int _N, int _number) {
    int answer = -1;
    int N = _N;
    int number = _number;
    unordered_map<string, int> operations;
    unordered_map<string, cExpression> statePool;
    cExpression exp;
    cExpression test;

    //������ �켱 ���� ����
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