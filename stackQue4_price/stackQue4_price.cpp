/*
    초 단위로 기록된 가격이 들어있는 배열이 제공된다.
    각 초별로 제시된 가격이 유지된 시간을 배열로 저장해 리턴하시오.
    단, 이미 지난 시간에 대한 고려는 하지 않는다.

    [예제]
    price               return
    [1, 2, 3, 2, 3]	    [4, 3, 1, 1, 0]
    
    [설명] 
    산 뒤 몇초 뒤에 가격이 떨어졌는가. (산 가격보다 떨어진 시점 구하기)

    [parameter]
    vector<int> 각 초별 가격

    [return]
    각 초의 순각 가격이 현재 보다 높거나 같은 시간을 리턴

    [제한사항]
    price       : 1 ~ 10000
    prices.size : 2 ~ 100000

    [메모]
    출제자는 국어 능력에 문제가 있다.
    

    간단하게 사고 몇초뒤 떨어지는가.

*/

/*
    [solution]
    1. 일단 que에 때려 박는다.
    2. 첫번째를 값을 pop()
    3. 값을 하나씩 pop()
    4. 이전 값이 첫번째 값보다 크면 cnt++;
    2~3 반복
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