/*
    (m, n) 행렬이 주어질때, 갈 수 있는 경우의 수를 1,000,000,007로 나눈 나머지 값을 구하시오.
    단, puddles배열에 들어있는 좌표에는 진입 할 수 없다.

    S--*--*--*
    |  |  |  |
    *--X--*--*
    |  |  |  |
    *--*--*--D 
    
    S : 시작 지점
    D : 목표 지점
    X : 갈 수 없는 지점
    * : 통과 가능 지점

    
*/

/*
    [solution]
    (m , n) 크기의 벡터를 사용하여 이동 가능한 가짓수 표시
    임의의 인덱스로 (i, j)로 접근 가능한 경우의 수는,
    (i, j) = (i-1, j) + (i, j-1) 이다.
    i = 0 혹은 j = 0일 경우는 기본적으로 1이 대입.
    단, puddles의 값에는 반드시 0이 대입된다.
    

    -----------------
    | S | 1 | 1 | 1 |
    -----------------
    | 1 | X | 1 | 2 |
    -----------------
    | 1 | 1 | 2 | E |
    -----------------

    E = 4

    매 루프마다 puddle값을 검사하기 싫으니,
    puddle에 해당하는 좌표에 -1을 대입한다.
    값이 -1인 경우 해당 좌표 계산을 하지 않는다.
    -> 0이하의 수가 허용되지 않는 경우.

    [단점]
    메모리를 (m * n) * int 사이즈 만큼 사용한다.

    [추가]
    -행렬에 들어간 값이 모두 모듈러 연산이 되어 있어야 한다.
    -사방이 막힌 경우가 존재한다. -> return 0
*/

#include <string>
#include <vector>
#include <memory.h>

#define PUDDLE -1
#define NUMBER 1000000007

using namespace std;


struct stWayToSchool
{
    int row;
    int col;
    int* pDatas;

};


bool WayToSchoolCreate(stWayToSchool* &pDest, int row, int col);                    //메모리 할당 및 초기화
void WayToShcoolDelete(stWayToSchool* &pDest);                                      //할당된 메모리 제거
bool WayToSchoolSetData(stWayToSchool* pDest, int value, int row, int col);         //해당 인덱스의 값 계산
bool WayToSchoolSetPuddles(stWayToSchool* pDest, vector<vector<int>>& puddles);     //이차원 벡터로 제시된 인덱스들을 puddle임을 기록
bool WayToSchoolIsPuddle(stWayToSchool* pDest, int row, int col);                   //해당 인덱스가 PUDDLE 인가?
int WayToSchoolGetData(stWayToSchool* pDest, int row, int col);
int WayToSchoolFindWay(stWayToSchool* pDest);

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;

    stWayToSchool* pNoWayHome = nullptr;

    //필요 메모리 할당 및 초기화
    WayToSchoolCreate(pNoWayHome, m, n);
    
    //지나가지 못하는 구역 설정
    WayToSchoolSetPuddles(pNoWayHome, puddles);   

    //값 구하기.
    answer = WayToSchoolFindWay(pNoWayHome);

    //메모리 삭제
    WayToShcoolDelete(pNoWayHome);

    return answer;
}

/*

    warnning 메모리 할당이 발생한다.  pDest가 nullptr이 아닐 경우, 메모리를 해제하고 재할당 한다. 할당한 메모리 내부에 다시 메모리를 할당하는 파트가 있다. 정해진 삭제 함수를 사용할 것.
*/
bool WayToSchoolCreate(stWayToSchool*& pDest, int row, int col)
{
    bool bResult = false;
    int size = 0;

    //파라미터 검사
    if (row < 0) goto lb_return;
    if (col < 0) goto lb_return;
    if (pDest != nullptr)
    {
        WayToShcoolDelete(pDest);
    }
    
    //메모리 할당
    pDest = new stWayToSchool;
    if (pDest == nullptr) goto lb_return;           //할당 실패
    
    //내부 메모리 할당.
    pDest->pDatas = new int[row * col];
    if (pDest->pDatas == nullptr) goto lb_return;   //할당 실패
    
    //초기화
    pDest->row = row;
    pDest->col = col;
    size = sizeof(int) * row * col;
    memset(pDest->pDatas, 0, size);
    
    pDest->pDatas[0] = 1;
    
    //함수 성공
    bResult = true;

lb_return:
    return bResult;
}

void WayToShcoolDelete(stWayToSchool*& pDest)
{
    if (pDest != nullptr)
    {
        //내부 할당된 메모리 제거
        delete[] pDest->pDatas;
        pDest->pDatas = nullptr;

        //메모리 제거
        delete pDest;
        pDest = nullptr;
    }
}

/*
    @detail 해당 인덱스(row, col)의 값을 value로 설정 해준다.
    @return 함수 성공 여부
    @warnning 파라미터 값이 적절하지 않은 경우 함수 실패 
*/
bool WayToSchoolSetData(stWayToSchool* pDest, int value, int row, int col) 
{
    bool bResult = false;
    int rowSize = 0;
    if (pDest == nullptr) goto lb_return;
    if (pDest->pDatas == nullptr) goto lb_return;
    if (value < PUDDLE) goto lb_return;
    if (row < 0) goto lb_return;
    if (col < 0) goto lb_return;

    rowSize = pDest->row;
    pDest->pDatas[rowSize * col + row] = value % NUMBER;

    bResult = true;

lb_return:
    return bResult; 
}

/*
    @detail    지나가지 못하는 지역을 표시 하는 함수
    @return    함수 성공 여부 리턴
    @warnning  파라미터가 적절하지 않은 경우 return false
    @todo      puddles 내부값 체크하는 로직 추가할 것.
*/
bool WayToSchoolSetPuddles(stWayToSchool* pDest, vector<vector<int>>& puddles)
{
    bool bResult = false;
    //Bad Parameter
    if (pDest == nullptr) goto lb_return;       
    if (puddles.size() == 0) goto lb_return;

    for (auto& it : puddles)
    {
        vector<int>& puddle = it;
        int row = puddle.at(0) - 1;
        int col = puddle.at(1) - 1;
        WayToSchoolSetData(pDest, PUDDLE, row, col);
    }

    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail 해당 인덱스가 PUDDLE 인지 검사.
*/
bool WayToSchoolIsPuddle(stWayToSchool* pDest, int row, int col)
{
    bool bResult = false;
    int data = 0;
    if (pDest == nullptr) goto lb_return;
    if (row < 0) goto lb_return;
    if (col < 0) goto lb_return;

    data = WayToSchoolGetData(pDest, row, col);
    if (data == PUDDLE) bResult = true;

lb_return:
    return bResult;
}

/*
    @deail 입력한 인덱스의 값을 찾아 준다.
    @return 실패시 -1 리턴, PUDDLE일 경우, 1리턴. 나머지 경우는 해당 인덱스까지 도달 가능한 경우의 수 리턴
*/
int WayToSchoolGetData(stWayToSchool* pDest, int row, int col)
{
    int result = -1;
    int rowSize = 0;
    int colSize = 0;
    int index = 0;
    if (pDest == nullptr) goto lb_return;
    if (pDest->pDatas == nullptr) goto lb_return;
    if (row < 0) goto lb_return;
    if (col < 0) goto lb_return;

    rowSize = pDest->row;
    colSize = pDest->col;
    index = rowSize * col + row;

    result = pDest->pDatas[index];      

lb_return:
    return result;
}

/*
    @detail 윗 줄부터 가능한수 찾기

*/
int WayToSchoolFindWay(stWayToSchool* pDest)
{
    int result = -1;
    int rowSize = 0;
    int colSize = 0;
    if (pDest == nullptr) goto lb_return;
    
    rowSize = pDest->row;
    colSize = pDest->col;

    //가로 첫줄
    for (int row = 1; row < rowSize; row++)
    {
        int col = 0;
        int left = WayToSchoolGetData(pDest, row - 1, col);

        if (!WayToSchoolIsPuddle(pDest, row, col))
            WayToSchoolSetData(pDest, left, row, col);
    }

    //세로 첫줄
    for (int col = 1; col < colSize; col++)
    {
        int row = 0;
        int up = WayToSchoolGetData(pDest, row, col - 1);

        if (!WayToSchoolIsPuddle(pDest, row, col))
            WayToSchoolSetData(pDest, up, row, col);
    }

    //나머지 영역 계산
    for (int col = 1; col < colSize; col++)
    {
        for (int row = 1; row < rowSize; row++)
        {
            int up = WayToSchoolGetData(pDest, row, col-1);
            int left = WayToSchoolGetData(pDest, row - 1, col);

            if (up == PUDDLE) up = 0;
            if (left == PUDDLE) left = 0;
            int sum = up + left;
            
            if(!WayToSchoolIsPuddle(pDest, row, col))
                WayToSchoolSetData(pDest, sum, row, col);
        }
    }
    
    result = WayToSchoolGetData(pDest, rowSize - 1, colSize - 1);

lb_return:
    return result;
}

int main()
{
    //return 4
    int m = 4;
    int n = 3;
    vector<vector<int>> puddles = { {2, 2} };

    int result = solution(m, n, puddles);



    printf("RESUlT : %d\n", result);

    return 0;
}