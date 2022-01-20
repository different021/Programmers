#include <vector>
#include <string>

using namespace std;

class cToken
{
    int n;
    int value;                  //��� ���
    int numberOfN;              //N�� ���� Ƚ��
    vector<string> expression;  //��� ��

public:
    cToken();
    cToken(int input);
    cToken(const cToken& src);

    int GetValue();
    int CalValue();
    bool AddExpression(string exp);     //�ùٸ� ���̈� �˻��ϰ� ������.
};

cToken::cToken()
{
    n = 0;
    value = 0;
    numberOfN = 0;
}

cToken::cToken(int input)
{
    n = input;
    value = n;
    numberOfN = 1;
}

/*
    @warnning  Copy Vector
*/
cToken::cToken(const cToken& src)
{
    n = src.n;
    value = src.value;
    expression = src.expression;
}

int cToken::GetValue()
{
    return n;
}

int cToken::CalValue()
{
    int result = n;
    //��� ����
    for (auto& it : expression)
    {
        string& exp = it;

        if (it.compare("+") == 0)
        {
            result += n;
        }
        else if (it.compare("-") == 0)
        {
            result -= n;
        }
        else if (it.compare("*") == 0) {
            result *= n;
        }
        else if (it.compare("/") == 0) {
            if (n != 0) result /= n;
            else
            {
                //Divid By Zero
            }
        }
        else if (it.compare(".") == 0)
        {
            //����ó�� �߰�. -> ���ӵ� ������ ���� �����ϴ�.
            result = result * 10 + n;
        }
        else
        {
            //�� ��Ȳ������ 5���� ��� �� ������������ �ȵȴ�.
            //assert(false);
        }
    }

    value = result;
    return result;
}

bool cToken::AddExpression(string exp)
{
    bool bResult = true;
    expression.push_back(exp);

    return bResult;
}
