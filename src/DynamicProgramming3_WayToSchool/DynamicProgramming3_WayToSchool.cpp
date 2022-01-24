/*
    (m, n) ����� �־�����, �� �� �ִ� ����� ���� 1,000,000,007�� ���� ������ ���� ���Ͻÿ�.
    ��, puddles�迭�� ����ִ� ��ǥ���� ���� �� �� ����.

    S--*--*--*
    |  |  |  |
    *--X--*--*
    |  |  |  |
    *--*--*--D 
    
    S : ���� ����
    D : ��ǥ ����
    X : �� �� ���� ����
    * : ��� ���� ����

    
*/

/*
    [solution]
    (m , n) ũ���� ���͸� ����Ͽ� �̵� ������ ������ ǥ��
    ������ �ε����� (i, j)�� ���� ������ ����� ����,
    (i, j) = (i-1, j) + (i, j-1) �̴�.
    i = 0 Ȥ�� j = 0�� ���� �⺻������ 1�� ����.
    ��, puddles�� ������ �ݵ�� 0�� ���Եȴ�.
    

    -----------------
    | S | 1 | 1 | 1 |
    -----------------
    | 1 | X | 1 | 2 |
    -----------------
    | 1 | 1 | 2 | E |
    -----------------

    E = 4

    �� �������� puddle���� �˻��ϱ� ������,
    puddle�� �ش��ϴ� ��ǥ�� -1�� �����Ѵ�.
    ���� -1�� ��� �ش� ��ǥ ����� ���� �ʴ´�.
    -> 0������ ���� ������ �ʴ� ���.

    [����]
    �޸𸮸� (m * n) * int ������ ��ŭ ����Ѵ�.

    [�߰�]
    -��Ŀ� �� ���� ��� ��ⷯ ������ �Ǿ� �־�� �Ѵ�.
    -����� ���� ��찡 �����Ѵ�.
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

bool WayToSchoolCreate(stWayToSchool* &pDest, int row, int col);                    //�޸� �Ҵ� �� �ʱ�ȭ
void WayToShcoolDelete(stWayToSchool* &pDest);                                      //�Ҵ�� �޸� ����
bool WayToSchoolSetData(stWayToSchool* pDest, int value, int row, int col);         //�ش� �ε����� �� ���
bool WayToSchoolSetPuddles(stWayToSchool* pDest, vector<vector<int>>& puddles);     //������ ���ͷ� ���õ� �ε������� puddle���� ���
bool WayToSchoolIsPuddle(stWayToSchool* pDest, int row, int col);                   //�ش� �ε����� PUDDLE �ΰ�?
int WayToSchoolGetData(stWayToSchool* pDest, int row, int col);
int WayToSchoolFindWay(stWayToSchool* pDest);

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;

    stWayToSchool* pNoWayHome = nullptr;

    //�ʿ� �޸� �Ҵ� �� �ʱ�ȭ
    WayToSchoolCreate(pNoWayHome, m, n);
    
    //�������� ���ϴ� ���� ����
    WayToSchoolSetPuddles(pNoWayHome, puddles);   

    //�� ���ϱ�.
    answer = WayToSchoolFindWay(pNoWayHome);

    //�޸� ����
    WayToShcoolDelete(pNoWayHome);

    return answer;
}

/*

    warnning �޸� �Ҵ��� �߻��Ѵ�.  pDest�� nullptr�� �ƴ� ���, �޸𸮸� �����ϰ� ���Ҵ� �Ѵ�. �Ҵ��� �޸� ���ο� �ٽ� �޸𸮸� �Ҵ��ϴ� ��Ʈ�� �ִ�. ������ ���� �Լ��� ����� ��.
*/
bool WayToSchoolCreate(stWayToSchool*& pDest, int row, int col)
{
    bool bResult = false;
    int size = 0;

    //�Ķ���� �˻�
    if (row < 0) goto lb_return;
    if (col < 0) goto lb_return;
    if (pDest != nullptr)
    {
        WayToShcoolDelete(pDest);
    }
    
    //�޸� �Ҵ�
    pDest = new stWayToSchool;
    if (pDest == nullptr) goto lb_return;           //�Ҵ� ����
    
    //���� �޸� �Ҵ�.
    pDest->pDatas = new int[row * col];
    if (pDest->pDatas == nullptr) goto lb_return;   //�Ҵ� ����
    
    //�ʱ�ȭ
    pDest->row = row;
    pDest->col = col;
    size = sizeof(int) * row * col;
    memset(pDest->pDatas, 0, size);
    
    pDest->pDatas[0] = 1;
    
    //�Լ� ����
    bResult = true;

lb_return:
    return bResult;
}

void WayToShcoolDelete(stWayToSchool*& pDest)
{
    if (pDest != nullptr)
    {
        //���� �Ҵ�� �޸� ����
        delete[] pDest->pDatas;
        pDest->pDatas = nullptr;

        //�޸� ����
        delete pDest;
        pDest = nullptr;
    }
}

/*
    @detail �ش� �ε���(row, col)�� ���� value�� ���� ���ش�.
    @return �Լ� ���� ����
    @warnning �Ķ���� ���� �������� ���� ��� �Լ� ���� 
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
    @detail    �������� ���ϴ� ������ ǥ�� �ϴ� �Լ�
    @return    �Լ� ���� ���� ����
    @warnning  �Ķ���Ͱ� �������� ���� ��� return false
    @todo      puddles ���ΰ� üũ�ϴ� ���� �߰��� ��.
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
    @detail �ش� �ε����� PUDDLE ���� �˻�.
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
    @deail �Է��� �ε����� ���� ã�� �ش�.
    @return ���н� -1 ����, PUDDLE�� ���, 1����. ������ ���� �ش� �ε������� ���� ������ ����� �� ����
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
    @detail �� �ٺ��� �����Ѽ� ã��

*/
int WayToSchoolFindWay(stWayToSchool* pDest)
{
    int result = -1;
    int rowSize = 0;
    int colSize = 0;
    if (pDest == nullptr) goto lb_return;
    
    rowSize = pDest->row;
    colSize = pDest->col;

    //���� ù��
    for (int row = 1; row < rowSize; row++)
    {
        int col = 0;
        int left = WayToSchoolGetData(pDest, row - 1, col);

        if (!WayToSchoolIsPuddle(pDest, row, col))
            WayToSchoolSetData(pDest, left, row, col);
    }

    //���� ù��
    for (int col = 1; col < colSize; col++)
    {
        int row = 0;
        int up = WayToSchoolGetData(pDest, row, col - 1);

        if (!WayToSchoolIsPuddle(pDest, row, col))
            WayToSchoolSetData(pDest, up, row, col);
    }

    //������ ���� ���
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