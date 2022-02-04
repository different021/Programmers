/*
    [¡�˴ٸ�]
    0�� distance ���̿� ¡�˴ٸ��� �ִ�.
    ¡�˴ٸ��� �Ÿ��� ǥ�õ� �迭�� �־� ����.
    n���� ���� �����Ѵ�.
    ¡�˴ٸ� ���̰Ÿ��� �Ÿ��� �ּҰ��� �ִ밡 �ǵ��� ����� �����Ͻÿ�

    [����]
    distance   : 1 ~ 1000000000
    rocks.size : 1 ~ 50000
    n : 1 ~ rocks.size

    [���õ� ����]
    ������ ������ ��ġ	�� ���� ������ �Ÿ�	�Ÿ��� �ּڰ�
    [21, 17]	        [2, 9, 3, 11]	        2
    [2, 21]	            [11, 3, 3, 8]	        3
    [2, 11]	            [14, 3, 4, 4]	        3
    [11, 21]	        [2, 12, 3, 8]	        2
    [2, 14]	            [11, 6, 4, 4]	        4

    ������ �ּҰ� �� �ִ밪 4.

*/

/*
    [solution]
    0. ���� �迭 ����(��������)
    1. [dist , rock] ���� ���ο� ������ ���� �����.
    2. dist ���� ���� ���� ���� (������ rock���� ���� ������)
    3. dist�� ���� ���� ���� rock ȹ��
    4. rock���� rocks�� ���˻�
    5. rocks���� �յ� ���� ���Ͽ� �μ��� ���� ���� ������ ����
        (��, 0 Ȥ�� distance���� ������ �� ����)
    6. dist���� ���ŵ� �� �ݿ�
    
    n�� ������ ���� �ݺ�.

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

    //rock ����
    sort(rocks.begin(), rocks.end());

    //�Ÿ� ������ ����
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
    
    //�Ÿ� ������ ����
    sort(vDist.begin(), vDist.end(), rockManagerSortByPrevDist);

    //���� ���� ��
    auto it = vDist.begin();
    
    int rock = it->rock;
    auto target = find(rocks.begin(), rocks.end(), rock);   //Binary Search�� ���� �� �κ�.

    if (*target == *rocks.begin())
    {
        //ù��° ���� ���
        //-> ���� �� ����
        
        
    }
    else if (*target == end)
    {
        //������ ���� ���
        //-> �� �� ����
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