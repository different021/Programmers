/*
    숫자 N만 이용하여 number를 만드시오
    -사칙 연산과 숫자 N을 이용하여 number를 만들어야 한다.
    -숫자 N을 사용하는 최소 횟수를 리턴하시오

    [예제]
    N = 5, number = 12
    12 = 5 + 5 + (5 / 5) + (5 / 5)      N 사용 : 6회   
    12 = 55 / 5 + 5 / 5                 N 사용 : 5회
    12 = (55 + 5) / 5                   N 사용 : 4회

    최소 사용 4회

    [제한 사항]
    N : 1 ~ 9
    number = 1 ~ 32000
    수식 : 괄호와 사칙 연산 가능
    나누기 연산시 나머지 무시
    최소값이 8 이상 일 경우 -1 리턴
*/


/*
    [가능한 행동]
    1. 사칙 연산
    3. 연속 숫자
    2. 괄호 (열기 닫기 순서 쌍) - 사칙연산에 스택에 포함되지 않는다. -> 신경 쓸 필요없다.
*/

/*
    생성 가능한 값을 set에 저장
    1개로 생성 가능한 숫자 생성 -> s(1)
    2개로 생성 가능한 숫자 집합 생성 -> s(2) = s(1) + s(1) 
    3개로 생성 가능한 숫자 집합 생성 -> s(3) = s(1) + s(2) , s(2) + s(1)
    4개로 생성 가능한 숫자 집합 생성 -> s(4) = s(1) + s(3), s(2) + s(2), s(3) + s(1)
    ...
    7까지 반복

    각 단계 생성 후, target이 존재하는지 검사, 없으면 다음 단계 생성

*/

/*
    [operator]
    1. +
    2. -
    3. *
    4. /

    5. 연속된 숫자(별도 추가)
 */



#include <string>
#include <vector>
#include <set>

using namespace std;

#define MAX_LAYER 8

int solution(int N, int number) {
    int answer = -1;
    int basicNumber = N;
    int target = number;
    int num = basicNumber;

    vector<set<int>> pool;
    pool.reserve(MAX_LAYER);
    
    for (int i = 0; i < MAX_LAYER; i++)
    {
        set<int> temp;
        pool.push_back(temp);
    }
    
    //1개로 생성할 수 있는 수 생성
    pool[0].insert(basicNumber);

    //타겟 인지 확인
    if (pool[0].find(target) != pool[0].end())
    {
        //find
        answer = 1;
        goto lb_return;
    }

    //2개 이상으로 생성하는 로직 
    for (int i = 1; i < MAX_LAYER; i++)
    {
        //자릿수 추가
        num = num * 10 + basicNumber;
        pool[i].insert(num);

        for (int j = 0; j < i; j++)
        {
            for (set<int>::iterator it = pool[j].begin(); it != pool[j].end(); it++)
            {
                int num1 = *it;
                for (set<int>::iterator it_opp = pool[i - (j + 1)].begin(); it_opp != pool[i - (j + 1)].end(); it_opp++)
                {
                    int num2 = *it_opp;

                    // + 연산
                    int newNum = num1 + num2;
                    pool[i].insert(newNum);

                    // - 연산
                    newNum = num1 - num2;
                    pool[i].insert(newNum);

                    // * 연산
                    newNum = num1 * num2;
                    pool[i].insert(newNum);

                    // / 연산
                    if (num2 != 0)
                    {
                        int div = num1 / num2;
                        pool[i].insert(div);
                    }
                    
                }

            }
            
        }

        //find target
        if (pool[i].find(target) != pool[i].end())
        {
            //find
            answer = i + 1;
            break;
        }
    }

lb_return:
    return answer;
}


int main()
{
    ////return 4
    //int N = 5;
    //int number = 12;

    //-1
    int N = 5;
    int number = 5555555;

    int result = solution(N, number);

    printf("input : %d\n", N);
    printf("target: %d\n", number);
    printf("최소값: %d\n", result);

    return 0;
}