/*
    ü���� ���� ��� �߻�
    ������ ü�������� ü�� Ȱ���� �Ϸ��� �Ѵ�.
    ���� ������ �ִ� �л���

    �⼮��ȣ�� ü�� ��
    ü���� ����� ������Ը� �뿩 ����
    ��) 3���� ������ 2��, 4�� ���Ը� �뿩 ����

    [�Ķ����]
    int n : ��ü �л���
    vector<int> lost    : �Ҿ���� �л��� �⼮��ȣ
    vector<int> reserve : ������ ü���� ���� ��ȣ

    [����]
    int : ü������ �����ϴ� �ִ� �л���

    [����]
    n : 2 ~ 30
    lost : 1 ~ n (�ߺ� ����)
    reserve : ������ ���� �ִ� �л���

    [����]
    ������ ì�ܿ� �л��� ���������� �� �ִ�.
    �̶�, �� �л��� ������ �Ծ�� �ϱ⶧���� �뿩���ִ� ���� �Ұ��� �ϴ�.

    [����]
    n	lost	reserve	    return
    5	[2, 4]	[1, 3, 5]	5
    5	[2, 4]	[3]	        4
    3	[3]	    [1]	        2
    
*/

/*
    1. ���� üũ
    2. ���� üũ ( ������ ������ ������ �������� �ű��.)
    3. �뿩 ���� üũ (����, �չ�ȣ, �޹�ȣ)

    1 ~ 2 �ݺ�
    
*/


#include <string>
#include <vector>

using namespace std;


enum eTargetBorrow
{
    eBorrowSelf = 0,
    eBorrowFront,
    eBorrowBack,
    eBorrowMAX,
};

struct stStudent
{
    
    int id;             //�⼮��ȣ
    int spareOwner;     //�����ϰ�� ������. 0 ����, -1 ���� �����, n ���� ���� �⼮ ��ȣ
    bool suit;
    bool spare;         //����

    stStudent()
    {
        suit = true;
        spare = false;
        spareOwner = 0;
    }
};

//student �Լ���
bool studentSetSpare(stStudent& student, bool hasSpare);
bool studentStolenSuit(stStudent& student);
bool studentBorrowSuit(stStudent& borrower, stStudent& lender);


//solution �Լ���
int solution(int n, vector<int> lost, vector<int> reserve);
bool solutionInit(stStudent* &pStudents, int numOfStudents);
bool solutionUpdateSpare(stStudent* pStudents, int numOfStudents, vector<int>& spare);
bool solutionUpdateLost(stStudent* pStudents, int numOfStudent, vector<int>& lost);
bool solutionBorrowSpare(stStudent& me, stStudent* pSmall, stStudent* pLarge); 
bool solutionBorrowSpareMaximum(stStudent* pStudents, int numOfStudnet);
int  solutionGetNumberOfStudentHasSuit(stStudent* pStudents, int numOfStudents);

int solution(int n, vector<int> _lost, vector<int> reserve) {
    int answer = 0;
    stStudent* pStudents = nullptr;
    int numOfStudents = n;
    vector<int>& lost = _lost;
    vector<int>& spare = reserve;

    if (n < 1) { /*invaild param*/ }
    else
    {   
        //�ʿ� ������ ����
        solutionInit(pStudents, numOfStudents); //�޸� �Ҵ� ���� ����
        //if(pStudents == nullptr) {/* �޸� �Ҵ� ���� */};
    }
    
    //���� üũ
    solutionUpdateSpare(pStudents, numOfStudents, spare);

    //���� üũ
    solutionUpdateLost(pStudents, numOfStudents, lost);

    //������ üũ
    solutionBorrowSpareMaximum(pStudents, numOfStudents);
    
    //���� ���� �ο�
    answer = solutionGetNumberOfStudentHasSuit(pStudents, numOfStudents);



    //Free Memory
    delete[] pStudents;

    return answer;
}


//�л� Ŭ���� �Լ� ����

/*
    @detail �л��� ����� ���� ��� ������Ʈ
*/
bool studentSetSpare(stStudent& student, bool hasSpare)
{
    student.spare = hasSpare;

    return student.spare;
}


/*
    @detail �л� ü���� ���� ����. ���� �ִٸ� ���� ����ϱ�� �Ѵ�.
    @param  student ���� ���� �л�
    @return �ᱹ ����� ü������ ������ true, ������ false
*/
bool studentStolenSuit(stStudent& student)
{
    student.suit = false;   //���� ����

    if (student.spare == true)  //���� ��� �ֳ�?
    {
        student.spare = false;  //�����̸� ����Ѵ�. �� �̻� ���� �ƴϴ�.
        student.suit = true;
    }

lb_return:
    return student.suit;    
}

/*
    @detail ���������� ������ ���� 
    @param  borrower ������ ���. lender �����ִ� ���
    @return �����ִ� ������� ������ �����Ѵ�. ������ ����� �̹� ������ �����Ѵ�. -> �ᱹ ������ ������ �Ͼ�� ����. �Ͼ�� ������ ����
*/
bool studentBorrowSuit(stStudent& borrower, stStudent& lender)
{
    bool bResult = false;
    
    if (borrower.suit = true) goto lb_return;   //���� �ʿ� ����.
    if (lender.spare = false) goto lb_return;   //������ ������ ����.

    borrower.suit = true;
    borrower.spareOwner = lender.id;    //���� ǥ��, ���������.

    studentSetSpare(lender, false);

lb_return:
    return bResult;
}

/*
    @detail �޸� �Ҵ� �� �ʱ�ȭ(�⼮��ȣ �Է�)
*/
bool solutionInit(stStudent* &pStudents, int n)
{
    bool bResult = false;

    if (n < 1) goto lb_return;
    if (pStudents != nullptr)
    {
        //�����Ϳ� ���� ������ ����.
        delete[] pStudents;
        pStudents = nullptr;
    }

    pStudents = new stStudent[n];

    for (int i = 0; i < n - 1; i++)
    {
        pStudents[i].id = i + 1;
        
    }

    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail ������ ü������ �ִ� �л� ��Ȳ ������Ʈ
    @param  pStudents �л� �迭 numOfStudents �л� �� spare ������ ü������ �ִ� �л� �⼮��ȣ ����Ʈ
    @return �Լ� ���� ����, ��ȿ���� ���� �Ķ���� �Է½� ����
*/
bool solutionUpdateSpare(stStudent* pStudents, int numOfStudents, vector<int>& spare)
{
    bool bResult = false;
    int max = numOfStudents - 1;
    if (pStudents == nullptr) goto lb_return;
    if (max < 0) goto lb_return;

    for (auto& it : spare)
    {
        int index = it - 1;
        studentSetSpare(pStudents[index], true);    //���� ����.
    }


lb_return:
    return bResult;
}

/*

*/
bool solutionUpdateLost(stStudent* pStudents, int numOfStudent, vector<int>& lost)
{
    bool bResult = false;
    int max = numOfStudent - 1;

    if (pStudents == nullptr) goto lb_return;
    if (max < 0) goto lb_return;

    for (auto& it : lost)
    {
        int index = it - 1;
        if (index > max)
        {
            //�߸��� ������.
            //�߸��� �����͸� ���� ��� ������ �����͸� ó���ϰ� ������ϳ�? �׳� �ٷ� ������ϳ�?
            goto lb_return;
        }

        //�л� ����Ʈ �� üũ �߰�.

        //����
        studentStolenSuit(pStudents[index]);    //���� ���� üũ, ������ ������ ��ȯ.
    }

    
lb_return:
    return bResult;
}

/*
    @detail �������� �յ� ��ȣ���� ������ ����
    @detail �չ�ȣ �л� Ȥ�� �޹�ȣ �л����� ü���� ������. �� Ȥ�� �� ��ȣ�� ������, NULL (3 �Ķ���� ��ο� ������ ��ȯ ���ɼ��� �ִ�. ����.)
    @param  me ����, pSmall �� ��ȣ(NULL ���), pLarge �� ��ȣ(NULL ����)
    @return �� Ȥ�� �� ��ȣ�� ü���� �����⸦ �����ϸ� true, �Ѵ� ������ ����
*/
bool solutionBorrowSpare(stStudent& me, stStudent* pSmall, stStudent* pLarge)
{
    bool bSuccess = false;
    //���� ��ȯ�� ���� ���� ���� ������Ʈ ���� �� �ǽ���.
    //�չ�ȣ���� Ȯ��
    if (pSmall != nullptr)
    {
        bSuccess = studentBorrowSuit(me, *pSmall);
        if (bSuccess == true) goto lb_return;
    }

    //�չ�ȣ�� �����µ� ����.
    //�޹�ȣ�� ������.
    if (bSuccess == false)
    {
        bSuccess = studentBorrowSuit(me, *pLarge);
    }

lb_return:
    return bSuccess;
}


/*
    @detail �������� �� �ִ� �ִ� ���ڷ� �л��� ���� ü������ ������ ����
    @param  pStudents �л��� �迭, numOfStudent �л� ��
    @return �߸��� �Ķ���� �Է½� false
*/
bool solutionBorrowSpareMaximum(stStudent* pStudents, int numOfStudnet)
{
    bool bResult = false;
    int num = numOfStudnet;
    for (int i = 0; i < num; i++)
    {
        int small = i - 1;
        int large = i + 1;
        stStudent* pSmall = nullptr;
        stStudent* pLarge = nullptr;
        
        //�ε����� ��ȿ�� �˻�.
        if (small > -1)  pSmall = &pStudents[small];        
        if (large < num) pLarge = &pStudents[large];

        solutionBorrowSpare(pStudents[i], pSmall, pLarge);
    }

    return bResult;
}

int  solutionGetNumberOfStudentHasSuit(stStudent* pStudents, int numOfStudents)
{
    int answer = 0;
    int max = numOfStudents - 1;
    if (numOfStudents < 0) goto lb_return;
    if (pStudents == nullptr) goto lb_return;

    for (int i = 0; i < max; i++)
    {
        if (pStudents[i].suit == true)
        {
            answer++;
        }
    }

lb_return:
    return answer;
}

int main()
{
    //return 5 - > �׽�Ʈ ���̽� ���� �ٽ� ����.
    int n = 5;
    vector<int> lost = { 2, 4 };
    vector<int> reserve = { 1, 3, 5 };

    int result = solution(n, lost, reserve);

    printf("�ִ밪 : %d \n", result);
}