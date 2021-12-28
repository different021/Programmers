/*
 [�������� ���� ����]
 ���� ������ ������ �����.
 ���ڸ��� ������ ��� ����� �ִ�.
 ������ ���� �Ķ���ͷ� ���� ������, 3�� ���� ���� ���� ����� �����ΰ�?

 1�� : { 1, 2, 3. 4. 5 }�� �ݺ�
 2�� : { 2, 1, 2, 3, 2, 4, 2, 5 } �ݺ�
 3�� : { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 } �ݺ�

 %�����ڴ� ������ ������ ������� �ظ�.

 [�Ķ����]
 vector<int> ������ ���

 [����]
 vector<int> ������ ���� ���� ���� �л��� ��ȣ ����

 [���� ����]
 answers.size() : ~ 10000
 ���� ������ : 1 ~ 5
 ���� ���� ���� ����� �ټ��� ���, �������� ����
*/


/*
    [solution]
    1. �ʱ�ȭ 
        ���� ���信 ���� ������ ����. �迭�� ����.
    2. ���� üũ (% ������ ���) -> Ư�� ������ ���� ���� �ۼ��Ѵ�. ���Ͽ� ���� %�����ڷ� ����
    3. ����� Ȯ��
    4. �ִ� ������ ����
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//students
class cStudentNoMathInLife
{   
    bool m_bIsCheck;    //ä���ߴ�?
    int m_id;           //�л� ��ȣ
    int m_iGrade;       //���
    vector<int> m_pattern;

public:
    cStudentNoMathInLife();     //nothing
    ~cStudentNoMathInLife();    //nothing
    bool Initialize(int id, vector<int>& randomSheet);  //�ݺ� ���� �Է��Ͽ� �ʱ�ȭ
    bool Check(vector<int>& answerSheet);       //ä��
    int GetGrade() const;                             //ä�� ���
    int GetId() const;
};

//��� �� �Լ�
//����� ��������
//������, id ���� ����
bool compStdentByGrade(const cStudentNoMathInLife& stu1, const cStudentNoMathInLife& stu2)
{
    bool bResult = false;
    
    int grade1 = stu1.GetGrade();
    int grade2 = stu2.GetGrade();

    if ( grade1 > grade2)
    {
        bResult = true;
    }
    else if (grade1 == grade2)
    {
        if (stu1.GetId() < stu2.GetId())
        {
            //id�� �ĺ����̶� ������ �ȵȴ�.
            bResult = true;
        }
    }

    return bResult;
}

//solution
vector<int> solution(vector<int> answers);
bool solutionInitailize(vector<cStudentNoMathInLife>& students, vector<vector<int>>& patterns);
bool solutionGrading(vector<cStudentNoMathInLife>& students, vector<int>& answers);
bool solutionSortByGrade(vector<cStudentNoMathInLife>& students);
bool solutionGetFristPlaces(vector<int>& out, vector<cStudentNoMathInLife>& students);

vector<int> solution(vector<int> answers) {
    bool bSuccess = false;                      
    vector<int> firstPlace;                     //return value
    vector<cStudentNoMathInLife> students;      //
    
    //Data
    vector<vector<int>> noMathInMyLifesAnswer = {
        { 1, 2, 3, 4, 5 },
        { 2, 1, 2, 3, 2, 4, 2, 5 },
        { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 }
    };

    //1. �ʱ�ȭ. 
    bSuccess = solutionInitailize(students, noMathInMyLifesAnswer);
    if (bSuccess == false) { /*�ʱ�ȭ ����*/ }


    //2. ���� üũ
    bSuccess = solutionGrading(students, answers);
    if (bSuccess == false) { /*����ó��*/ }


    //3. ������ ����(��������)
    bSuccess = solutionSortByGrade(students);
    if (bSuccess == false) { /*����ó��*/ }


    //4. ����(1��, ������ ���� ����)
    bSuccess = solutionGetFristPlaces(firstPlace, students);
    if (bSuccess == false) { /*����ó��*/ }


    return firstPlace;
}

/*
    [�Ķ����]
    students(output) : �����
    patterns(input)  : �л����� ��� �ۼ� ����

    [����]
    �Լ� ���� ����
*/
bool solutionInitailize(vector<cStudentNoMathInLife>& students, vector<vector<int>>& patterns)
{
    bool bResult = false;
    int id = 1;
    if (patterns.size() == 0) goto lb_return;

    for (auto& it : patterns)
    {
        cStudentNoMathInLife student;
        student.Initialize(id, it);
        students.push_back(student);
        id++;
    }

    bResult = true;

lb_return:
    return bResult;
}

/*
    �Էµ� ������� ä��
    
    [�Ķ����]
    students(output)    : ������ ü������(bool)�� ����
    answers             : ���� �񱳸� ���� Grading

    [����]
    �Լ� ��������;
    1. �Ķ���� ��ȿ��
    2. ���� �л� ä�� ���� �˻�

*/
bool solutionGrading(vector<cStudentNoMathInLife>& _students, vector<int>& _answers)
{
    bool bResult = true;
    vector< cStudentNoMathInLife>& students = _students;
    vector<int>& answers = _answers;
    
    if (students.size() == 0)
    {
        bResult = false;
        goto lb_return;
    }

    if (answers.size() == 0)
    {
        bResult = false;
        goto lb_return;
    }

    students.reserve(answers.size());

    for (auto& it : students)
    {
        bool bSuccess = it.Check(answers);
        if (bSuccess == false)
        {
            //ü�� ����?
            //����ó�� �߰�
            bResult = false;
        }
    }

lb_return:
    return bResult;
}

/*
    ���������� ����(��������)
    ������, id�� ��������
*/
bool solutionSortByGrade(vector<cStudentNoMathInLife>& students)
{
    bool bResult = false;

    if (students.size() == 0) goto lb_return;

    sort(students.begin(), students.end(), compStdentByGrade);

    bResult = true;

lb_return:
    return bResult;
}

/*
    [����]
    ������� ���ĺ��� �� ��.
    
    [�Ķ����]
    out(output)             : 1���� id�� ����(������ �ټ� ����)
    students(input)         : ������ ��ϵǾ� �ִ�.

    [����]
    �Լ� ��������
    1. �л��� ������ ����

*/
bool solutionGetFristPlaces(vector<int>& out, vector<cStudentNoMathInLife>& students)
{
    bool bResult = false;
    int highestGrade = 0;
    if (students.size() == 0) goto lb_return;

    highestGrade = students.at(0).GetGrade();
    for (auto& it : students)
    {
        int grade = it.GetGrade();
        if (highestGrade == grade)
        {
            out.push_back(it.GetId());
        }
        else
        {
            break;
        }
    }

    bResult = true;

lb_return:
    return bResult;
}

cStudentNoMathInLife::cStudentNoMathInLife()
{
    
}

cStudentNoMathInLife::~cStudentNoMathInLife()
{

}

bool cStudentNoMathInLife::Initialize(int _id, vector<int>& pattern)
{
    bool bResult = false;
    int id = _id;
    vector<int>& sheet = pattern;

    if (id < 0) goto lb_return;
    if (sheet.size() == 0) goto lb_return;

    m_bIsCheck  = false;
    m_id        = id;
    m_iGrade    = -1;

    m_pattern = sheet;

lb_return:
    return bResult;
}

//��� ��
bool cStudentNoMathInLife::Check(vector<int>& answerSheet)
{
    bool bResult = false;
    vector<int>& answers = answerSheet;
    size_t size = m_pattern.size();
    int index = 0;

    if (size == 0) goto lb_return;
    if (answers.size() == 0) goto lb_return;

    //reset
    if (m_iGrade != 0)
    {
        m_bIsCheck = false;
        m_iGrade = 0;
    }

    for (auto& it : answers)
    {
        int myAnswer = m_pattern.at( index % size );
        int answer = answers.at(index);

        if (myAnswer == answer)
        {
            m_iGrade++;
        }
        index++;
    }

    bResult = true;

lb_return:
    return bResult;
}

int cStudentNoMathInLife::GetGrade() const
{
    return m_iGrade;
}

int cStudentNoMathInLife::GetId() const
{
    return m_id;
}

int main()
{
    //return { 1 }
    //vector<int> answers = { 1, 2, 3, 4, 5 }; 

    //return { 1,2, 3} 
    vector<int> answers = { 1, 3, 2, 4, 2 };

    vector<int> result = solution(answers);

    printf("[���] \n");
    for (auto& it : result)
    {
        printf("%d \n", it);
    }
    

    return 0;
}