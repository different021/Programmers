/*
    �� ������ ��ϵ� ������ ����ִ� �迭�� �����ȴ�.
    �� �ʺ��� ���õ� ������ ������ �ð��� �迭�� ������ �����Ͻÿ�.
    ��, �̹� ���� �ð��� ���� ����� ���� �ʴ´�.

    [����]
    price               return
    [1, 2, 3, 2, 3]	    [4, 3, 1, 1, 0]
    
    [����] 
    �� �� ���� �ڿ� ������ �������°�. (�� ���ݺ��� ������ ���� ���ϱ�)

    [parameter]
    vector<int> �� �ʺ� ����

    [return]
    �� ���� ���� ������ ���� ���� ���ų� ���� �ð��� ����

    [���ѻ���]
    price       : 1 ~ 10000
    prices.size : 2 ~ 100000

    [�޸�]
    �����ڴ� ���� �ɷ¿� ������ �ִ�.
    

    �����ϰ� ��� ���ʵ� �������°�.

*/

/*
    [solution]
    1. �ϴ� que�� ���� �ڴ´�.
    2. ù��°�� ���� pop()
    3. ���� �ϳ��� pop()
    4. ���� ���� ù��° ������ ũ�� cnt++;
    2~3 �ݺ�
*/


#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool CountUpper(vector<int> prices);

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    queue<int> que;
    
    int count = 0;
    for (vector<int>::iterator it = prices.begin(); it != prices.end(); it++)
    {
        int first = *it;
        int last = first;

        for (vector<int>::iterator innerIt = it + 1; innerIt != prices.end(); innerIt++)
        {
            
            int cur = *innerIt;
            if (last < first)
            {
                break;
            }

            count++;
            last = cur;
        }

        answer.push_back(count);
        count = 0;
    }

    return answer;
}

bool CountUpper(vector<int> prices)
{
    bool bResult = false;
    vector<int> answer;
    for (vector<int>::iterator it = prices.begin(); it != prices.end(); it++)
    {
        int count = 0;
        int current = *it;

        count = count_if(it + 1, prices.end(), [current](int val) { return current <= val; });

        answer.push_back(count);
    }

    return bResult;
}



int main()
{
                         //{ 4, 3, 1, 1, 0 }
    //vector<int> prices = { 1, 2, 3, 2, 3 };
                       
                //return { 5, 4, 1, 2, 1, 0 }
    //vector<int> prices = { 1, 2, 3, 2, 3, 1 };

                       //{ 6, 5, 1, 3, 2, 1, 0 }
    vector<int> prices = { 1, 2, 3, 2, 3, 3, 1 }; 

    vector<int> result = solution(prices);

    printf("RESULT : \n");
    for (auto& it : result)
    {
        printf("%d \n", it);
    }

    return 0;
}