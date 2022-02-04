/*
    n개의 음이 아닌 정수들이 있다.
    이 정수들의 순서를 바꾸지 않고, 더하거나 빼서 타겟 넘버를 만들려고 한다.
    만들 수 있는 방법의 수를 리턴 하시오.

    [예시]
    numbers             target
    [1, 1, 1, 1, 1]     3

    -1+1+1+1+1 = 3
    +1-1+1+1+1 = 3
    +1+1-1+1+1 = 3
    +1+1+1-1+1 = 3
    +1+1+1+1-1 = 3

    return 5

    [테스트 케이스]    
    numbers	            target	return
    [1, 1, 1, 1, 1]	    3	    5
    [4, 1, 2, 1]	    4	    2

    [제한사항]
    number.size     : 2 ~ 20
    number          : 1 ~ 50
    target Number   : 1 ~ 1000

*/

/*
  [solution]  
  1.

*/


#include <string>
#include <vector>

using namespace std;

/*
    @detail 재귀를 활용한 target을 만드는 방법의 갯수를 구하는 함수
    @param  out : count
    @return return 현재까지 합계.
*/
int reqursive(int& out, vector<int>& src, int _depth, int sum, int target)
{
    int result = sum;
    int depth = _depth + 1;
    if (depth < src.size())
    {
        reqursive(out, src, depth, result + src.at(depth), target);
        reqursive(out, src, depth, result - src.at(depth), target);
    }
    else
    {
        if (result == target) 
            out++;
    }

    return result;
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int count = 0;
    int depth = 0;
    reqursive(count, numbers, depth, numbers.at(0), target);
    reqursive(count, numbers, depth, -numbers.at(0), target);
    
    answer = count;

    return answer;
}


int main()
{
    //return 5
    int target = 3;
    vector<int> numbers = { 1, 1, 1, 1, 1 };
    int result = solution(numbers, target);

    printf("%d\n", result);

    return 0;
}