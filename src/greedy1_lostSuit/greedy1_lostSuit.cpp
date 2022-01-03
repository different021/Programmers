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
    [solution]
    1. ���� üũ
    2. ���� üũ ( ������ ������ ������ �������� �ű��.)
    3. �뿩 ���� üũ (����, �չ�ȣ, �޹�ȣ)
        -> �뿩��, spare = false
        -> �뿩 ��� �ε��� ����
*/


#include <string>
#include <vector>

using namespace std;

struct stStudent
{
    bool suit;
    bool spare;         //����
    int id;             //�⼮��ȣ
    int spareOwner;     //�����ϰ�� ������. 0 ����, -1 ���� �����, n ���� ���� �⼮ ��ȣ

    stStudent()
    {
        suit = true;
        spare = false;
        id = -1;
        spareOwner = 0;
    }
};

//student �Լ���
void studentInitialize(stStudent& student, int id);
bool studentSetSpare(stStudent& student, bool hasSpare);
bool studentStolenSuit(stStudent& student);
bool studentBorrowSuit(stStudent& borrower, stStudent& lender);


//solution �Լ���
int solution(int n, vector<int> lost, vector<int> reserve);
bool solutionInitialize(vector<stStudent>& students, int numOfStudent);
bool solutionUpdateSpare(vector<stStudent>& students, vector<int>& spare);
bool solutionUpdateLost(vector<stStudent>& students, vector<int>& lost);
bool solutionBorrowSpare(stStudent& me, stStudent* pSmall, stStudent* pLarge); 
bool solutionBorrowSpareMaximum(vector<stStudent>& students);
int  solutionGetNumberOfStudentHasSuit(vector<stStudent>& students);

int solution(int n, vector<int> _lost, vector<int> reserve) {
    int answer = 0;
    //stStudent* students = nullptr;
    vector<stStudent> students;
    int MAX_STUDENT = n;
    vector<int>& lost = _lost;
    vector<int>& spare = reserve;

    if (n < 1) { /*invaild param*/ }
    else
    {   
        //�ʿ� ������ ����
        solutionInitialize(students, n); //�޸� �Ҵ� ���� ����
    }
    
    //���� üũ
    solutionUpdateSpare(students, spare);

    //���� üũ
    solutionUpdateLost(students, lost);

    //������ üũ
    solutionBorrowSpareMaximum(students);
    
    //���� ���� �ο�
    answer = solutionGetNumberOfStudentHasSuit(students);

    return answer;
}


//�л� Ŭ���� �Լ� ����

/*
    @detail ������ �ʱ�ȭ �ڵ�
    @param  student destination id keyValue
    @return void
*/
void studentInitialize(stStudent& student, int id)
{
    student.id = id;
    student.suit = true;
    student.spare = false;
    student.spareOwner = 0;
}

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
    
    if (borrower.suit == true) goto lb_return;   //���� �ʿ� ����.
    if (lender.spare == false) goto lb_return;   //������ ������ ����.

    borrower.suit = true;
    borrower.spareOwner = lender.id;    //���� ǥ��, ���������.

    //lender.spare = false;
    studentSetSpare(lender, false);
    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail �޸� �Ҵ� �� �ʱ�ȭ(�⼮��ȣ �Է�)
    @param student �ʱ�ȭ ��ų �迭, n ������ �л� ��.
*/
bool solutionInitialize(vector<stStudent>& students, int n)
{
    bool bResult = false;

    if (n < 1) goto lb_return;


    for (int i = 0; i < n; i++)
    {
        stStudent stu;
        studentInitialize(stu, i + 1);
        students.push_back(stu);
    }

    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail ������ ü������ �ִ� �л� ��Ȳ ������Ʈ
    @param  students �л� �迭, numOfStudents �л� �� spare, ������ ü������ �ִ� �л� �⼮��ȣ ����Ʈ
    @return �Լ� ���� ����, ��ȿ���� ���� �Ķ���� �Է½� ����
*/
bool solutionUpdateSpare(vector<stStudent>& students, vector<int>& spare)
{
    bool bResult = false;
    
    if (students.size() < 0) goto lb_return;

    for (auto& it : spare)
    {
        int index = it - 1;
        if (index < 0) continue;
        studentSetSpare(students.at(index), true);    //���� ����. -> vector��ȯ. �ε��� ����.
    }

lb_return:
    return bResult;
}

/*
    @detail ü������ ���� ���� �л��� suit�� false�� �ٲ��ش�.
    @param  student �л���, lost ü������ ���� ���� ������� �⼮��ȣ��(int)
*/
bool solutionUpdateLost(vector<stStudent>& students, vector<int>& lost)
{
    bool bResult = false;
    int max = students.size();

    if (students.size() == 0) goto lb_return;

    for (auto& it : lost)
    {
        int index = it - 1;
        if (index > max)
        {
            //�߸��� ������.
            //�߸��� �����͸� ���� ��� ������ �����͸� ó���ϰ� ������ϳ�? �׳� �ٷ� ������ϳ�?
            goto lb_return;
        }

        //����
        studentStolenSuit(students.at(index));    //���� ���� üũ, ������ ������ ��ȯ.
    }

    
lb_return:
    return bResult;
}

/*
    @detail �������� �յ� ��ȣ���� ������ ����
    @detail �չ�ȣ �л� Ȥ�� �޹�ȣ �л����� ü���� ������. �� Ȥ�� �� ��ȣ�� ������, NULL (3 �Ķ���� ��ο� ������ ��ȯ ���ɼ��� �ִ�. ����.)
    @param  me ����, pSmall �� ��ȣ(NULL ���), pLarge �� ��ȣ(NULL ����)
    @return �� Ȥ�� �� ��ȣ�� ü���� �����⸦ �����ϸ� true, �Ѵ� ������ ����
    @warnning �� �� ��ȣ�� ���� ���(index�� �հ� ���� �չ�ȣ �޹�ȣ�� ����. �̰�� �׳� nullptr�� ���� �ȴ�.)
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

    //�չ�ȣ�� �����µ� ���� �� ���,
    //�޹�ȣ���� ������.
    if (pLarge != nullptr)
    {
        if (bSuccess == false)
        {
            bSuccess = studentBorrowSuit(me, *pLarge);
        }
    }
    
lb_return:
    return bSuccess;
}


/*
    @detail �������� �� �ִ� �ִ� ���ڷ� �л��� ���� ü������ ������ ����
    @param  students �л��� �迭, numOfStudent �л� ��
    @return �߸��� �Ķ���� �Է½� false
*/
bool solutionBorrowSpareMaximum(vector<stStudent>& students)
{
    bool bResult = false;
    int num = students.size();

    stStudent* pTemp = nullptr;
    

    for(size_t i = 0; i < students.size(); i++)
    {
        size_t small = i - 1;
        size_t large = i + 1;
        stStudent* pSmall = nullptr;
        stStudent* pLarge = nullptr;
        
        //�ε����� ��ȿ�� �˻�.
        if (i > 0)  pSmall = &students[small];        
        if (i < students.size() - 1) pLarge = &students[large];
        if (i == 1)
        {
            int a = 3;
        }
        bool isBorrow = solutionBorrowSpare(students.at(i), pSmall, pLarge);
        int a = 1;
    }

    return bResult;
}

/*
    @detail ü������ Ȯ���� �ִ� �л� ��. 
    @return int ü������ Ȯ����(student.suit == true)�� �л� �� ����
*/
int  solutionGetNumberOfStudentHasSuit(vector<stStudent>& students)
{
    int answer = 0;
    int max = students.size();
    if (max < 0) goto lb_return;

    for (auto& it : students)
    {
        if (it.suit == true)
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
    /*int n = 5;
    vector<int> lost = { 2, 4 };
    vector<int> reserve = { 1, 3, 5 };*/

    //return 4
    int n = 5;
    vector<int> lost = { 2, 4 };
    vector<int> reserve = { 3 };


    int result = solution(n, lost, reserve);

    printf("�ִ밪 : %d \n", result);
}