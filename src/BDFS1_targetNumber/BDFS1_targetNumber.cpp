/*
    n���� ���� �ƴ� �������� �ִ�.
    �� �������� ������ �ٲ��� �ʰ�, ���ϰų� ���� Ÿ�� �ѹ��� ������� �Ѵ�.
    ���� �� �ִ� ����� ���� ���� �Ͻÿ�.

    [����]
    numbers             target
    [1, 1, 1, 1, 1]     3

    -1+1+1+1+1 = 3
    +1-1+1+1+1 = 3
    +1+1-1+1+1 = 3
    +1+1+1-1+1 = 3
    +1+1+1+1-1 = 3

    return 5

    [�׽�Ʈ ���̽�]    
    numbers	            target	return
    [1, 1, 1, 1, 1]	    3	    5
    [4, 1, 2, 1]	    4	    2

    [���ѻ���]
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
    @detail ��͸� Ȱ���� target�� ����� ����� ������ ���ϴ� �Լ�
    @param  out : count
    @return return ������� �հ�.
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