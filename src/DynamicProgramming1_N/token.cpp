#include <vector>
#include <string>

using namespace std;

class cToken
{
    int n;
    int value;                  //계산 결과
    int numberOfN;              //N이 사용된 횟수
    vector<string> expression;  //계산 식

public:
    cToken();
    cToken(int input);
    cToken(const cToken& src);

    int GetValue();
    int CalValue();
    bool AddExpression(string exp);     //올바른 값이닞 검사하고 넣을것.
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
    //계산 과정
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
            //예외처리 추가. -> 연속된 숫에만 적용 가능하다.
            result = result * 10 + n;
        }
        else
        {
            //현 상황에서는 5가지 경우 중 나오지않으면 안된다.
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
