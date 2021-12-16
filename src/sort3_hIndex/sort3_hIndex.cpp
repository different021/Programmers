
/*

    �������� ���꼺�� ������� ��Ÿ���� ��ǥ H-Index

    n���� �� ��, h�� �̻� �ο�� ���� h����� �Ҷ�,
    h���� �ִ밪�� H-index��� �Ѵ�.
    ���� �ο�Ƚ���� �� vector<int> citations�� �־�����,
    H-Index�� ���Ͽ� �����϶�

    [parameter]
    vector<int> citations

    [return]
    int



    ex)
    citations	        return
    [3, 0, 6, 1, 5]	    3

    3ȸ �̻� �ο�� �� 3�� (�ο�Ƚ��: 3, 6, 5 )
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const int& a, const int& b);
bool  GetHindex(int& out, vector<int>& citations);

int solution(vector<int> citations) {
    int answer = 0;

    bool bSuccess = GetHindex(answer, citations);

    return answer;
}

//������ ���� ���� ������ ����
bool comp(const int& a, const int& b)
{
    return (a > b);
}

//���ο��� ���ñ��� ����
/*
    1. �ο�Ƚ���� ���� ������ ����
    2. ���� ���� �ο�� Ƚ���� �������� �ο�� Ƚ���� �ε����� Ȯ��
    3. ũ�ų� ������ ����

*/
bool  GetHindex(int& out, vector<int>& citations) {
    bool bResult = false;
    int hIndex = 0;
    int citaSize = citations.size();
    int i = 0;

    //�߸��� �Ķ����
    if (citaSize == 0) goto lb_return;

    //�ο�Ƚ���� ���� ������ ����
    sort(citations.begin(), citations.end(), comp);

    i = *(citations.begin());
    for (; i > 0; i-- ) 
    {
        
        if (i < citaSize) {
            int useageOfIndex = citations.at(i - 1);
            if (useageOfIndex >= i)
            {
                hIndex = i;
                break;
            }
        }
        else {
            //������ �ε��� �˻�
            int lastData = citations.back();
            if (lastData >= i)
            {
                //n�� ���� �� ����.
                hIndex = citaSize;
            }
            break;
        }
    }

    bResult = true;
    out = hIndex;

lb_return:
    return bResult;
}


int main()
{
    vector<int> citations = { 3, 0, 6, 1, 5 };
    int result = solution(citations);

    printf("H-Index : %d\n", result);

    return 0;
}