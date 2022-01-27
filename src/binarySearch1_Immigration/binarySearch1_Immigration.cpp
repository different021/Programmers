/*
    [입국심사]
    n명을 입국 심사할때, 걸리는 최소 시간을 구하라.
    단, 입국 심사대는 심사대 마다 시간이 다르다. 
    이는 vector<int> 형태로 전달 된다.

    [제한]
    n : 1 ~ 1000,000,000
    times : 1 ~ 1,000,000,000
    times.size : 1 ~ 100,000

*/


/*
    [solution]
    구하고자 하는 것은 (최소)시간. 
    시간에 대한 바이너리 서치
    해당 시간 내에 최대한 처리 가능한 수를 구한다.

    최초시작 : 0 ~ (timesMax * n) 
    mid = (timeMax * n + 0) / 2

    1. mid 시간 당 최대 처리 수를 구한다.
    2. 최대 처리수 N과 비교
     N < 처리량(mid) -> 더 적은 시간이 걸린다. 0 ~ mid 탐색
     N > 처리량(mid) -> 더 많은 시간이 필요하다. mid ~ end 탐색
    3. 2번 과정을 찾을때 까지 반복


*/

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits.h>

using namespace std;

typedef long long ll_t;

ll_t GetMaxPassed(size_t limit, vector<int>& times);

long long solution(int n, vector<int> times)
{
    ll_t answer = 0;
    ll_t passed = 0;
    ll_t target = static_cast<ll_t>(n);
    int  slowOfficer = *max_element(times.begin(), times.end());
    ll_t maximumTime = static_cast<ll_t>(slowOfficer) * target;

    ll_t start = 0;
    ll_t end = maximumTime;
    ll_t mid = 0;

    while (true)
    {
        mid = static_cast<ll_t>(start + end) / 2;
        passed = GetMaxPassed(mid, times);
        if (passed == 5)
        {
            int a = 0;
        }

        if (mid < start) break;
        if (mid > end) break;
        if (mid > maximumTime) break;
        if (mid < 0) break;

        if (passed >= target)
        {
            //   here        
            //s---------mid----------e
            end = mid - 1;
        }
        else if (passed < target)
        {
            //                here
            //s---------mid----------e
            start = mid + 1;
        }
        else if (passed == target)
        {
            answer = mid;
            //n = 5, times = { 5, 5, 5, 5, 5 }
            //answer 5, 6 동시에 존재.
            goto lb_return;
        }
    }

    answer = mid + 1;

lb_return:
    return answer;
}


/*
    @detail 입력한 단위 시간 동안 최대 처리량을 구하는 함수
    @param  limit : 단위 시간. time 1사람당 처리하는 시간이 저장된 벡터
*/
ll_t GetMaxPassed(size_t limit, vector<int>& times)
{
    ll_t result = 0;
    if (limit == 0) goto lb_return;
    for (auto& it : times)
    {
        if (it != 0)
        {
            ll_t passed = static_cast<ll_t>(limit) / it;
            result += passed;
        }
    }

lb_return:
    return result;
}


int main()
{
    //28
    /*int n = 6;
    vector<int> times = { 7, 10 };
    */
    //21
    /*int n = 8;
    vector<int> times = { 5, 7, 12 };*/

    //int  n = 10;
    //vector<int> times = { 1, 100, 4 };
    
    /*int  n = 4;
    vector<int> times = { 10, 7, 15 };*/

    int  n = 5;
    vector<int> times = { 5, 5, 5 };

    long long result = solution(n, times);

    printf("%lld\n", result);

    return 0;
}