/*
    [대털]
    도둑이 어떻게 알았는지 집집 마다 얼마를 보유하고 있는지 알고 있다.
    왜 그런지는 모르겠지만, 연속된 집이 털리면 경보가 울리게 되어있다.
    경보를 울리지 않고 털 수 있는 최대값을 찾아라.

    
    [제한]
    money.size : 3 ~ 1000000
    money : 0 ~ 1000

    [예제]
    money           return
    {1, 2, 3, 1}    4

    0번집과 2번 집을 털때 가장 큰 값. (1 + 3) 

*/

/*
    [solution]
    1. 메모리 영역 두개 사용
        - 0번 ~ n번까지 최대값 저장하는 메모리 영역 - N0
        - 1번 ~ n번까지 최대값 저장하는 메모리 영역 - N1
    2. 두 가지 경우의 수 비교 (n > 3)
        - money[N]  + N1(n-2)
        - money[N-1]+ N0(n-3)

    3. 큰 수가 N0(n) 이 된다.

    N0, N1, N2가 필요하게 된다.

*/


#include <string>
#include <vector>

using namespace std;

int solution(vector<int> money) {
    int answer = 0;
    return answer;
}