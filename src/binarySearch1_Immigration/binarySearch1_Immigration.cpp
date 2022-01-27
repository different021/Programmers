/*
    [�Ա��ɻ�]
    n���� �Ա� �ɻ��Ҷ�, �ɸ��� �ּ� �ð��� ���϶�.
    ��, �Ա� �ɻ��� �ɻ�� ���� �ð��� �ٸ���. 
    �̴� vector<int> ���·� ���� �ȴ�.

    [����]
    n : 1 ~ 1000,000,000
    times : 1 ~ 1,000,000,000
    times.size : 1 ~ 100,000

*/


/*
    [solution]
    ���ϰ��� �ϴ� ���� (�ּ�)�ð�. 
    �ð��� ���� ���̳ʸ� ��ġ
    �ش� �ð� ���� �ִ��� ó�� ������ ���� ���Ѵ�.

    ���ʽ��� : 0 ~ (timesMax * n) 
    mid = (timeMax * n + 0) / 2

    1. mid �ð� �� �ִ� ó�� ���� ���Ѵ�.
    2. �ִ� ó���� N�� ��
     N < ó����(mid) -> �� ���� �ð��� �ɸ���. 0 ~ mid Ž��
     N > ó����(mid) -> �� ���� �ð��� �ʿ��ϴ�. mid ~ end Ž��
    3. 2�� ������ ã���� ���� �ݺ�


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
            //answer 5, 6 ���ÿ� ����.
            goto lb_return;
        }
    }

    answer = mid + 1;

lb_return:
    return answer;
}


/*
    @detail �Է��� ���� �ð� ���� �ִ� ó������ ���ϴ� �Լ�
    @param  limit : ���� �ð�. time 1����� ó���ϴ� �ð��� ����� ����
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