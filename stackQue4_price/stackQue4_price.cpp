/*
    �� ������ ��ϵ� ������ ����ִ� �迭�� �����ȴ�.
    �� �ʺ��� ���õ� ������ ������ �ð��� �迭�� ������ �����Ͻÿ�.
    ��, �̹� ���� �ð��� ���� ����� ���� �ʴ´�.

    [����]
    price               return
    [1, 2, 3, 2, 3]	    [4, 3, 1, 1, 0]
    
    [����] 
    �� �������κ��� ���� ������ ������ �� �� ���ΰ�? (�� ���ݺ��� ������ ������ ���� ���ΰ�? -> �ȶ��� ���� ���� �ִ�.)
    �̷� ������ �ֽĿ� ���µ�. �ֽĿ� ���� ���� ���ߴϱ� ���ذ� �� �ȵǾ���.

    [parameter]
    vector<int> �� �ʺ� ����

    [return]
    �� ���� ���� ������ ���� ���� ���ų� ���� �ð��� ����

    [���ѻ���]
    price       : 1 ~ 10000
    prices.size : 2 ~ 100000

    [�޸�]
    �����ڴ� ���� �ɷ¿� ������ �ִ�.
    ������ �ٷ� �����ϴµ� ���� �ð��� �ɷȴ�.
    �׽�Ʈ ���̽��� �� �ִ���. 
    �ּ� �߰��� ���� ȿ������ ��� ������ �ʿ��ϴ�. 
    ������ �����ڰ� ������ ������ ��������� �Ѵ�.
    �� ������ �ȳ���. �̷� ������ ������ ��ð� ���� ����м��ߴ�. �׳� ��������.
*/

/*
    [solution]
    1. ù��° ���� �ٸ� ��� ���� �� (index�� ���� ��)
    3. ù��° ������ ���� ��� �극��ũ
    4. ī��Ʈ ��� (return�� ���Ϳ�)
    5. ���� ��ҷ� �̵� (index++)

    1 ~ 5 �ݺ�

    it doesn't use stack or que,
    and has low effiency.

*/


#include <string>
#include <vector>

using namespace std;

bool CountUpper(vector<int> prices);

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    
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