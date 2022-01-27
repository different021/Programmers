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
    cur
    next 
    ���� ����. �� ������Ʈ
    next���� ���� ���� ������ ������. 

    next�� �������� ����
    ���� ���� next�� passed ����
    n�� �ݺ�

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
//    int times;          //�ɻ翡 �ɸ��� ��
//    int passed;         //�ɻ��� ��
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
//    //if (pOffice != nullptr) { /*���� ���н�, ó�� �ڵ�*/ };
//    
//    //�ʱ�ȭ
//    for (auto& it : times)
//    {
//        if (index > size)
//        {
//            //����ó�� �߰�
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
//    @detail dest �ʱ�ȭ. �Ա��ɻ翡 �Ÿ��� �ð��� �Է��� �ٰ�.
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
//    @detail �ɻ��� ��� �߰�. passed 1����, cur, next, ����.
//*/
//int ImmigrationIncreasePassed(Immigration& dest)
//{
//    int curValue = 0;
//    dest.passed++;                                      //�Ա� �ɻ��� ���� ����
//    dest.cur += static_cast<uint_t>(dest.times);        //���� �ο�����
//    dest.next += static_cast<uint_t>(dest.times);       //�Ѹ� �� �ϸ� �󸶳� �ɸ���?
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
    1. �ο� �й�.
    2. �ִ밪 ã��.

    [�ο��й�]
    vector<int> times 
    ���� ������ ��� �� �ջ�
    �ջ��� ���� ����(1/inverseSum)
    �� ������Ʈ�� ����(1/a)

    �й跮 = n * ( (1/a) / (1/inverseSum) )
    
    

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
    quotes.reserve(n);      //�����Ҵ� ����
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
        quotes.push_back(people);       //�ּ� �ο� ��ġ ��, �߰� ��ġ.
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