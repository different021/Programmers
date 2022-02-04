/*
    [징검다리]
    0과 distance 사이에 징검다리가 있다.
    징검다리의 거리가 표시된 배열이 주어 졌다.
    n개의 돌을 제거한다.
    징검다리 사이거리의 거리중 최소값이 최대가 되도록 만들어 리턴하시오

    [제한]
    distance   : 1 ~ 1000000000
    rocks.size : 1 ~ 50000
    n : 1 ~ rocks.size

    [제시된 설명]
    제거한 바위의 위치	각 바위 사이의 거리	거리의 최솟값
    [21, 17]	        [2, 9, 3, 11]	        2
    [2, 21]	            [11, 3, 3, 8]	        3
    [2, 11]	            [14, 3, 4, 4]	        3
    [11, 21]	        [2, 12, 3, 8]	        2
    [2, 14]	            [11, 6, 4, 4]	        4

    생성된 최소값 중 최대값 4.

*/

/*
    [solution]
    0. 들어온 배열 정렬(오름차순)
    1. [dist , rock] 묶은 새로운 데이터 구조 만든다.
    2. dist 기준 오름 차순 정렬 (같으면 rock값이 낮은 순으로)
    3. dist가 가장 낮은 값의 rock 획득
    4. rock값을 rocks에 서검색
    5. rocks에서 앞뒤 값을 비교하여 두수의 차가 작은 쪽으로 제거
        (단, 0 혹은 distance값은 제거할 수 없다)
    6. dist에서 제거된 값 반영
    
    n개 제거할 동안 반복.

*/

#include <string>
#include <vector>
#include <algorithm>

#define UNTOUCHABLE -1

using namespace std;

struct stDist
{
    int dist;
    int rock;
};

bool rockManagerSortByPrevDist(stDist& r1, stDist& r2)
{
    bool bResult = false;
    if (r1.dist < r2.dist)
    {
        bResult = true;
    }
    else if (r1.dist == r2.dist)
    {
        if (r1.rock < r2.rock) bResult = true;
    }

    return bResult;
}


int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    vector<stDist> vDist;
    
    int start = 0;
    int end = distance;
    
    rocks.push_back(end);
    size_t size = rocks.size();

    vDist.reserve(size - 1);    //

    //rock 정렬
    sort(rocks.begin(), rocks.end());

    //거리 데이터 생성
    int prev = 0;
    for (int i = 0; i < size; i++)
    {
        stDist temp;
        int rock = rocks.at(i);
        temp.dist = rock - prev;
        temp.rock = rock;
        vDist.push_back(temp);

        prev = rock;
    }
    
    //거리 데이터 정렬
    sort(vDist.begin(), vDist.end(), rockManagerSortByPrevDist);

    //가장 작은 값
    auto it = vDist.begin();
    
    int rock = it->rock;
    auto target = find(rocks.begin(), rocks.end(), rock);   //Binary Search로 변경 할 부분.

    if (*target == *rocks.begin())
    {
        //첫번째 값일 경우
        //-> 현재 돌 제거
        
        
    }
    else if (*target == end)
    {
        //마지막 값일 경우
        //-> 앞 돌 제거
        target--;

    }

    int a = 0;

    return answer;
}

int main()
{
    //return 4;
    int distance = 25;
    vector<int> rocks = { 2, 14, 11, 21, 17 };
    int n = 2;

    int result = solution(distance, rocks, n);

    printf("%d\n", result);

    return 0;
}