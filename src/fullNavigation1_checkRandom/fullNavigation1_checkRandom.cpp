/*
 [수포자의 수학 시험]
 수학 시험을 찍기로한 세사람.
 각자만의 고유한 찍기 방식이 있다.
 문제의 답을 파라미터로 전달 받을때, 3중 가장 많이 맞춘 사람은 누구인가?

 1번 : { 1, 2, 3. 4. 5 }의 반복
 2번 : { 2, 1, 2, 3, 2, 4, 2, 5 } 반복
 3번 : { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 } 반복

 %수포자는 수학을 포기한 사람들의 준말.

 [파라미터]
 vector<int> 문제의 답안

 [리턴]
 vector<int> 문제를 가장 많이 맞춘 학생의 번호 벡터

 [제한 사항]
 answers.size() : ~ 10000
 정답 객관식 : 1 ~ 5
 가장 맞이 맞춘 사람이 다수일 경우, 오름차순 리턴
*/


/*
    [solution]
    1. 초기화 
        각자 정답에 대한 패턴이 존재. 배열로 저장.
    2. 정답 체크 (% 연산자 사용) -> 특정 패턴을 갖고 답을 작성한다. 패턴에 대해 %연산자로 접근
    3. 정답수 확인
    4. 최다 정답자 리턴
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//students
class cStudentNoMathInLife
{   
    bool m_bIsCheck;    //채점했니?
    int m_id;           //학생 번호
    int m_iGrade;       //결과
    vector<int> m_pattern;

public:
    cStudentNoMathInLife();     //nothing
    ~cStudentNoMathInLife();    //nothing
    bool Initialize(int id, vector<int>& randomSheet);  //반복 패턴 입력하여 초기화
    bool Check(vector<int>& answerSheet);       //채점
    int GetGrade() const;                             //채점 결과
    int GetId() const;
};

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
            //id는 식별값이라 같으면 안된다.
            bResult = true;
        }
    }

    return bResult;
}

//solution
vector<int> solution(vector<int> answers);
bool solutionInitailize(vector<cStudentNoMathInLife>& students, vector<vector<int>>& patterns);
bool solutionCheckStudentsSheet(vector<cStudentNoMathInLife>& students, vector<int>& answers);
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

    //1. 초기화. 
    bSuccess = solutionInitailize(students, noMathInMyLifesAnswer);
    if (bSuccess == false) { /*초기화 실패*/ }


    //2. 정답 체크
    bSuccess = solutionCheckStudentsSheet(students, answers);
    if (bSuccess == false) { /*예외처리*/ }


    //성적이 높은순으로 정렬
    bSuccess = solutionSortByGrade(students);
    if (bSuccess == false) { /*예외처리*/ }


    //1등자들 리턴
    bSuccess = solutionGetFristPlaces(firstPlace, students);
    if (bSuccess == false) { /*예외처리*/ }


    return firstPlace;
}

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

bool solutionCheckStudentsSheet(vector<cStudentNoMathInLife>& students, vector<int>& patterns)
{
    bool bResult = true;

    if (patterns.size() == 0)
    {
        bResult = false;
        goto lb_return;
    }

    students.reserve(patterns.size());

    for (auto& it : students)
    {
        bool bSuccess = it.Check(patterns);
        if (bSuccess == false)
        {
            //체점 실패?
            //예외처리 추가
            bResult = false;
        }
    }

lb_return:
    return bResult;
}

bool solutionSortByGrade(vector<cStudentNoMathInLife>& students)
{
    bool bResult = false;

    if (students.size() == 0) goto lb_return;

    sort(students.begin(), students.end(), compStdentByGrade);

    bResult = true;

lb_return:
    return bResult;
}

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

//결과 비교
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

    printf("[결과] \n");
    for (auto& it : result)
    {
        printf("%d \n", it);
    }
    

    return 0;
}