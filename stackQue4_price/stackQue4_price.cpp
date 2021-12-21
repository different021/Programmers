/*
    초 단위로 기록된 가격이 들어있는 배열이 제공된다.
    각 초별로 제시된 가격이 유지된 시간을 배열로 저장해 리턴하시오.
    단, 이미 지난 시간에 대한 고려는 하지 않는다.

    [예제]
    price               return
    [1, 2, 3, 2, 3]	    [4, 3, 1, 1, 0]
    
    [설명] 
    산 시점으로부터 최초 손해인 시점은 몇 초 뒤인가? (산 가격보다 떨어진 시점은 몇초 뒤인가? -> 안떨어 졌을 수도 있다.)
    이런 개념이 주식에 없는데. 주식에 갖다 끼워 맞추니까 이해가 더 안되었다.

    [parameter]
    vector<int> 각 초별 가격

    [return]
    각 초의 순각 가격이 현재 보다 높거나 같은 시간을 리턴

    [제한사항]
    price       : 1 ~ 10000
    prices.size : 2 ~ 100000

    [메모]
    출제자는 국어 능력에 문제가 있다.
    문제를 바로 이해하는데 오랜 시간이 걸렸다.
    테스트 케이스를 더 주던지. 
    주석 추가와 보다 효율적인 방법 연구가 필요하다. 
    하지만 출제자가 선사한 빅엿으로 여기까지만 한다.
    할 마음이 안난다. 이런 간단한 문제를 몇시간 동안 국어분석했다. 그냥 하지말껄.
*/

/*
    [solution]
    1. 첫번째 값과 다른 모든 값을 비교 (index가 낮은 순)
    3. 첫번째 값보다 낮은 경우 브레이크
    4. 카운트 기록 (return용 벡터에)
    5. 다음 요소로 이동 (index++)

    1 ~ 5 반복

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