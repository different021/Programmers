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
    cur
    next 
    값을 유지. 및 없데이트
    next값이 가장 낮은 곳으로 보낸다. 

    next를 기준으로 정렬
    가장 낮은 next에 passed 증가
    n번 반복

*/
//
//
//
//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//typedef long long uint_t;
//
//struct Immigration
//{
//    long long next;
//    long long cur;      //
//    int times;          //심사에 걸리는 수
//    int passed;         //심사한 수
//};
//
//bool ImmigrationCompByLessNextValue(const Immigration& ins1, const Immigration& ins2);
//bool ImmigrationInitalize(Immigration& dest, int times);
//int ImmigrationIncreasePassed(Immigration& dest);
//
////pOffice
//uint_t OfficeSortByLessNextValue(vector<Immigration>& dest);
//uint_t OfficeSortByLessNextValue(Immigration* pDest, int size);
//
//long long solution(int n, vector<int> times) {
//    long long answer = 0;
//    int size = static_cast<int>(times.size());
//    Immigration* pOffice = new Immigration[size];
//    int index = 0;
//    //if (pOffice != nullptr) { /*말록 실패시, 처리 코드*/ };
//    
//    //초기화
//    for (auto& it : times)
//    {
//        if (index > size)
//        {
//            //예외처리 추가
//            break;
//        }
//        ImmigrationInitalize(pOffice[index], it);
//        index++;
//    }
//
//    for (int i = 0; i < n; i++)
//    {
//        answer = ImmigrationIncreasePassed(pOffice[0]);
//        OfficeSortByLessNextValue(pOffice, size);
//    }
//
//    delete[] pOffice;
//    pOffice = nullptr;
//
//    return answer;
//}
//
//bool ImmigrationCompByLessNextValue(const Immigration& ins1, const Immigration& ins2)
//{
//    bool bResult = false;
//
//    if (ins1.next < ins2.next) bResult = true;  
//
//    return bResult;
//}
//
///*
//    @detail dest 초기화. 입국심사에 거리는 시간을 입력해 줄것.
//*/
//bool ImmigrationInitalize(Immigration& dest, int times)
//{
//    bool bResult = false;
//    if (times < 0) goto lb_return;
//
//    dest.times =times;
//    dest.passed = 0;
//    dest.cur = 0;
//    dest.next = static_cast<uint_t>(times);
//
//    bResult = true;
//
//lb_return:
//    return bResult;
//}
//
///*
//    @detail 심사한 사람 추가. passed 1증가, cur, next, 증가.
//*/
//int ImmigrationIncreasePassed(Immigration& dest)
//{
//    int curValue = 0;
//    dest.passed++;                                      //입국 심사한 갯수 증가
//    dest.cur += static_cast<uint_t>(dest.times);        //현재 인원까지
//    dest.next += static_cast<uint_t>(dest.times);       //한명 더 하면 얼마나 걸릴까?
//
//    return dest.cur;
//}
//
//
//uint_t OfficeSortByLessNextValue(vector<Immigration>& dest)
//{
//    uint_t llResult = 0;
//
//    sort(dest.begin(), dest.end(), ImmigrationCompByLessNextValue);
//    llResult = dest.at(0).cur;
//
//    return llResult;
//}
//
//
//uint_t OfficeSortByLessNextValue(Immigration* pDest, int size)
//{
//    uint_t llResult = 0;
//    
//    sort(pDest, pDest + size, ImmigrationCompByLessNextValue);
//    llResult = pDest[0].cur;
//
//    return llResult;    
//}
//
//


/*
    [solution]
    1. 인원 분배.
    2. 최대값 찾기.

    [인원분배]
    vector<int> times 
    벡터 내부의 모든 값 합산
    합산한 값의 역수(1/inverseSum)
    각 엘리먼트의 역수(1/a)

    분배량 = n * ( (1/a) / (1/inverseSum) )
    
    

*/

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef long long uint_t;


long long solution(int n, vector<int> times) 
{
    long long answer = 0;
    double inverseSum = 0;
    vector<int> quotes;
    vector<int> result;
    quotes.reserve(n);      //업무할당 비율
    result.reserve(n);      //

    for (auto& it : times)
    {
        int timePerPerson = it;
        double personPerTime = (static_cast<double>(1) / timePerPerson);
        inverseSum += static_cast<double>(1) / it;
    }


    for (auto& it : times)
    {
        double temp = static_cast<double>(n) * ( static_cast<double>(1) / it) / inverseSum;
        int people = static_cast<int>(temp);
        quotes.push_back(people);       //최소 인원 배치 후, 추가 배치.
    }

    int sum = accumulate(quotes.begin(), quotes.end(), 0);
    int left = n - sum;


    int max = 0;
    for (int i = 0; i < quotes.size(); i++)
    {
        uint_t takes = static_cast<uint_t>(quotes.at(i)) * times.at(i);
        max = (max > takes) ? max : takes;
    }
    
    answer = max;

    return answer;
}


int main()
{
    //28
    //int n = 6;
    //vector<int> times = { 7, 10 };
    
    //21
    int n = 8;
    vector<int> times = { 5, 7, 12 };

    long long result = solution(n, times);

    printf("%lld\n", result);

    return 0;
}