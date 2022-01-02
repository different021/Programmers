/*
    테두리가 갈색, 내부가 노란색으로 칠해진 격자모양 카펫
    노란색 외부를 갈색이 1줄로 감싸고 있는 형태이다.

    갈색, 노란색 각각의 숫자가 주어질때, 카펫의 가로세로 크기를 리턴하시오

    [param]
    brown  : int
    yellow : int

    [제한사항]
    brown : 8 ~ 5000
    yellow: 1 ~ 2000000
    가로 >= 세로

    예1) 
    [B][B][B][B][B][B]
    [B][Y][Y][Y][Y][B]
    [B][B][B][B][B][B]

    [파라미터]
    brown  : 14
    yellow : 4

    [return]
    가로 : 6
    세로 : 3

    예2)
    [B][B][B][B]
    [B][Y][Y][B]
    [B][Y][Y][B]
    [B][B][B][B]

    [파라미터]
    brown  : 12
    yellow : 4

    [return]
    가로 : 4
    세로 : 4
*/

/*
    내부는 노란색.
    외부는 갈색

    갈색은 (yWidth + 2) * 2 + yHeight * 2 = (yWidth + 2 + yHiehgt) * 2
    노란색의 크기에 따라 변한다.
    노란색의 높이에 따라 가로가 정해진다.

    (고정)            (1부터 차례대로 대입)
    yTotal = yWidth * yHeight
    yWidth = yTotal / yHeight
    

    [갈색] 
    bTotal = (yWidth + 2 + yHeight) * 2
    bTotal = (yTotal/yHeight + 2 + yHeight) * 2

    //높이에 대해 정리해서 2차방정식을 만들어서 풀수 있다.
    //문제는 완전 탐색을 요구. 노랑이 1부터 쭉 찾아가는 방식을 채택했다.

    [solution]
    1. 노란색 높이를 1부터 차례로 찾을때까지 1씩 증가시키며 계산
    2. 노란색이 높이로 나누어지지 않으면 continue (직사각형이라서)
    3. 노란색의 너비 계산
    4. 노란색의 높이와 너비를 이용해 갈색 갯수 계산
    4. 4번의 결과가 파라미터로 받아온 갈색의 총 갯수와 같다면 break;
    높이를 하나씩 높여가면 반복

*/

#include <string>
#include <vector>

using namespace std;

#define BROWN_MAX   5000
#define YELLOW_MAX  2000000

/**
* @details brown이 yellow를 한줄로 감싸고 있다. 추어진 갈색, 노란색 수로 직사각형의 가로, 세로 크기를 구한다.
* @param[in] brown 갈색 사각형의 갯수(노란색의 외간을 1줄로 둘러 싸고 있는 모양)
* @param[in] yellow 노란색 사각형 갯수
* @retrun vector<int>
*/
vector<int> solution(int _brown, int _yellow) {
    vector<int> answer;
    int yellow = _yellow;
    int brown = _brown;
    int tatal = brown + yellow;
    int yHeight = 0;

    while (true)
    {
        yHeight++;

        //무한루프 방지
        if (yHeight > YELLOW_MAX)
        {
            //예외처리
            //답을 찾지 못함.
            break;
        }

        //2. 높이로 나누어 떨어지지 않으면 skip
        if ((yellow % yHeight) != 0) continue;

        //3. 노란색 너비 계산
        int yWidth = static_cast<int>(yellow / yHeight);

        //4. 노란색을 이용하여 갈색의 총 갯수 계산
        int brownTotal = (yWidth + 2 + yHeight) * 2;

        //5. 4번의 결과가 갈색과 파라미터로 들어온 값과 같다면 break; 
        if (brownTotal == brown)
        {
            //찾음
            int width = yWidth + 2;
            int height = yHeight + 2;
            answer.push_back( width );
            answer.push_back( height );
            
            break;
        }
    }//while(true)

    return answer;
}

int main()
{

    //[4, 3]
    int brown = 10;
    int yellow = 2;
    //8	    1[3, 3]
    //24	24[8, 6]

    vector<int> result = solution(10, 2);

    for (auto& it : result)
    {
        printf("%d \n", it);
    }

    return 0;
}