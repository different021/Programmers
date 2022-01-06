/*
    
    최대 정원 2명, 무게 제한 limit(param2) 보트를 이용해
    다양한 몸무게의 사람들(param1)을 구출 할때, 필요한 보트의 최소 갯수

    [param]
    무게 제한 int limit
    사람들 몸무게 vector<int> = { }

    [return]
    필요 최소 보트 갯수

    [제한사항]
    people.size     : 1 ~ 50000
    people.weight   : 40 ~ 240
    boat.limit      : 40 ~ 240
    보트의 무게 제한은 사람들의 몸무게 보다 항상 크다. -> 구출 못하는 경우는 없다.
*/

/*
    [예시]
    people	            limit	return
    [70, 50, 80, 50]	100	    3
    [70, 80, 50]	    100	    3
*/

/*
    [solution]
    1. 무게를 오름 차순 정렬
    2. (limit - 40)의 몸무게는 1인당 한개의 보트 필요 (무조건 한개, 제거)
    3. 두명 탑승 가능한 인원 중 가장 무거운 인원과 가장 가벼운 인원을 매칭하여 탑승 가능한지 검사.
        ->2명 탑승 가능  : 탑승 가능한 두명은 제거
        ->2명 탑승 불가능: 뒷 사람만 제거
    4. 3번 반복

*/

#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

#define PEOPLE_WEIGHT_MIN 40
#define PEOPLE_WEIGHT_MAX 240

#define BOAT_LIMIT_MIN 40
#define BOAT_LIMIT_MAX 240

int GetSingleBoatPeople(deque<int>& out, vector<int>& people, int threshold);

/*
    @detail     사람들을 구출하는 최소 보트 수를 구한다.
    @warnning   people을 오름차순으로 정렬하는 로직이 포함되어 있다. 
*/
int solution(vector<int> people, int limit) {
    int answer = 0;
    deque<int> left;
    int boatLimit = limit;
    int weight_Threshold = boatLimit - PEOPLE_WEIGHT_MIN;   //이 값을 초과하는 사람들은 무조건 보트를 한개 사용 해야 한다.
    int boatInSingle = 0;
    int boatInDoble = 0;
    int boatInTemp = 0;

    //1. 오름 차순 정렬
    sort(people.begin(), people.end());

    //2. 혼자 타야하는 사람들 과 같이 탈 수도 있는 사람들 분류 -> left에 있는 사람들만 검증하면 된다.
    boatInSingle = GetSingleBoatPeople(left, people, weight_Threshold);

    //3. 무거운 사람부터. 모두 빌때까지.
    while( !left.empty() )
    {
        //남은 사람이 2명이 안되면 1개에 태울 수 밖에
        if (left.size() < 2)
        {
            boatInTemp++;
            left.pop_front();   //size == 1 이면, 오해를 일으킬 수 있다.
            break;
        }

        int heavy = left.front();
        int light = left.back();
        
        if ( heavy + light <= limit )
        {
            //두명이 같이 탈 수 있는 경우
            boatInDoble++;
            left.pop_back();
            left.pop_front();
        }
        else
        {
            //한명 밖에 못태우는 경우
            left.pop_front();
            boatInTemp++;
        }
    }

    answer = boatInDoble + boatInSingle + boatInTemp;

    return answer;
}


/*
    @detail 무게 제한으로 혼자서 보트에 탑승해야만 하는 사람들 추려낸다.
    @param  out : 두명 탈 수도 있는 사람 리스트, people : 원본 소스 threshold : 두명 탈 수 있는 임계치
    @return 혼자 타야만 하는 사람들 숫자.
*/
int GetSingleBoatPeople(deque<int>& out, vector<int>& people, int threshold)
{
    int countBoatInSingle = 0;

    for (auto& it : people)
    {
        int weight = it;
        if (weight > threshold) break;

        out.push_front(it);  //무거운 사람부터 검사할 거라 앞으로 넣는다.
    }

    //1인당 1개의 보트가 필요한 사람들 (수치적으로 확정적인 사람들)
    countBoatInSingle = people.size() - out.size();

    return countBoatInSingle;
}



int main()
{
    //return	3
    /*vector<int> people = { 70, 50, 80, 50 }; 
    int limit = 100;*/

    vector<int> people = { 70, 50, 80 };
    int limit = 100;


    int result = solution(people, limit);

    printf("필요 보트 수 : %d\n", result);

    return 0;
}