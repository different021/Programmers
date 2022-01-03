/*
    체육복 도난 사건 발생
    여별의 체육복으로 체육 활동을 하려고 한다.
    수업 가능한 최대 학생수

    출석번호는 체격 순
    체격이 비슷한 사람에게만 대여 가능
    예) 3번의 여분은 2번, 4번 에게만 대여 가능

    [파라미터]
    int n : 전체 학생수
    vector<int> lost    : 잃어버린 학생들 출석번호
    vector<int> reserve : 여분의 체육복 보유 번호

    [리턴]
    int : 체육복을 착용하는 최대 학생수

    [제한]
    n : 2 ~ 30
    lost : 1 ~ n (중복 없음)
    reserve : 여벌을 갖고 있는 학생수

    [주의]
    여벌을 챙겨온 학생도 도난당했을 수 있다.
    이때, 이 학색은 본인이 입어야 하기때문에 대여해주는 것이 불가능 하다.

    [예시]
    n	lost	reserve	    return
    5	[2, 4]	[1, 3, 5]	5
    5	[2, 4]	[3]	        4
    3	[3]	    [1]	        2
    
*/

/*
    [solution]
    1. 여벌 체크
    2. 도난 체크 ( 여벌이 있으면 여벌을 본인으로 옮긴다.)
    3. 대여 가능 체크 (본인, 앞번호, 뒷번호)
        -> 대여시, spare = false
        -> 대여 대상 인덱스 저장
*/


#include <string>
#include <vector>

using namespace std;

struct stStudent
{
    bool suit;
    bool spare;         //여벌
    int id;             //출석번호
    int spareOwner;     //여벌일경우 소유자. 0 본인, -1 본인 스페어, n 여벌 주인 출석 번호

    stStudent()
    {
        suit = true;
        spare = false;
        id = -1;
        spareOwner = 0;
    }
};

//student 함수들
void studentInitialize(stStudent& student, int id);
bool studentSetSpare(stStudent& student, bool hasSpare);
bool studentStolenSuit(stStudent& student);
bool studentBorrowSuit(stStudent& borrower, stStudent& lender);


//solution 함수들
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
        //필요 데이터 생성
        solutionInitialize(students, n); //메모리 할당 로직 포함
    }
    
    //여벌 체크
    solutionUpdateSpare(students, spare);

    //도난 체크
    solutionUpdateLost(students, lost);

    //빌리기 체크
    solutionBorrowSpareMaximum(students);
    
    //수업 가능 인원
    answer = solutionGetNumberOfStudentHasSuit(students);

    return answer;
}


//학생 클래스 함수 시작

/*
    @detail 생성후 초기화 코드
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
    @detail 학생의 스페어 보유 어부 없데이트
*/
bool studentSetSpare(stStudent& student, bool hasSpare)
{
    student.spare = hasSpare;

    return student.spare;
}


/*
    @detail 학생 체육복 도난 당함. 스페어가 있다면 스페어를 사용하기로 한다.
    @param  student 도난 당한 학생
    @return 결국 사용할 체육복이 있으면 true, 없으면 false
*/
bool studentStolenSuit(stStudent& student)
{
    student.suit = false;   //도난 당함

    if (student.spare == true)  //스페어가 요기 있네?
    {
        student.spare = false;  //스페이를 사용한다. 더 이상 스페어가 아니다.
        student.suit = true;
    }

    return student.suit;    
}

/*
    @detail 누구가에게 빌리는 행위 
    @param  borrower 빌리는 사람. lender 빌려주는 사람
    @return 빌려주는 사람에게 없으면 실패한다. 빌리는 사람이 이미 있으면 실패한다. -> 결국 빌리는 행위가 일어나면 성공. 일어나지 않으면 실패
*/
bool studentBorrowSuit(stStudent& borrower, stStudent& lender)
{
    bool bResult = false;
    
    if (borrower.suit == true) goto lb_return;   //빌릴 필요 없다.
    if (lender.spare == false) goto lb_return;   //빌려줄 물건이 없다.

    borrower.suit = true;
    borrower.spareOwner = lender.id;    //주인 표시, 돌려줘야지.

    //lender.spare = false;
    studentSetSpare(lender, false);
    bResult = true;

lb_return:
    return bResult;
}

/*
    @detail 메모리 할당 및 초기화(출석번호 입력)
    @param student 초기화 시킬 배열, n 생성할 학생 수.
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
    @detail 여분의 체육복이 있는 학생 상황 없데이트
    @param  students 학생 배열, numOfStudents 학색 수 spare, 여분의 체육복이 있는 학색 출석번호 리스트
    @return 함수 실패 여부, 유효하지 않은 파라미터 입력시 실패
*/
bool solutionUpdateSpare(vector<stStudent>& students, vector<int>& spare)
{
    bool bResult = false;
    
    if (students.size() < 0) goto lb_return;

    for (auto& it : spare)
    {
        int index = it - 1;
        if (index < 0) continue;
        studentSetSpare(students.at(index), true);    //여분 있음. -> vector변환. 인덱스 검증.
    }

lb_return:
    return bResult;
}

/*
    @detail 체육복을 도난 당한 학색을 suit를 false로 바꿔준다.
    @param  student 학생들, lost 체육복을 도난 당한 학행들의 출석번호들(int)
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
            //잘못된 데이터.
            //잘못된 데이터를 만난 경우 나머지 데이터를 처리하고 멈춰야하나? 그냥 바로 멈춰야하나?
            goto lb_return;
        }

        //도난
        studentStolenSuit(students.at(index));    //도난 여부 체크, 여분이 있으면 전환.
    }

    
lb_return:
    return bResult;
}

/*
    @detail 개개인이 앞뒤 번호에게 빌리는 행위
    @detail 앞번호 학생 혹은 뒷번호 학생에게 체육복 빌리기. 앞 혹은 뒤 번호가 없으면, NULL (3 파라미터 모두에 데이텨 변환 가능성이 있다. 높다.)
    @param  me 본인, pSmall 앞 번호(NULL 허용), pLarge 뒷 번호(NULL 혀용)
    @return 앞 혹은 뒤 번호에 체육복 빌리기를 성공하면 true, 둘다 없으면 실패
    @warnning 앞 뒤 번호가 없는 경우(index의 앞과 끝은 앞번호 뒷번호가 없다. 이경우 그냥 nullptr이 들어가면 된다.)
*/
bool solutionBorrowSpare(stStudent& me, stStudent* pSmall, stStudent* pLarge)
{
    bool bSuccess = false;

    //본인 전환은 도둑 맞은 것을 업데이트 했을 때 실시함.
    //앞번호부터 확인
    if (pSmall != nullptr)
    {
        bSuccess = studentBorrowSuit(me, *pSmall);
        if (bSuccess == true) goto lb_return;
    }

    //앞번호에 빌리는데 실패 할 경우,
    //뒷번호한테 빌린다.
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
    @detail 수업받을 수 있는 최대 숫자로 학생들 끼리 체육복을 빌리는 행위
    @param  students 학생들 배열, numOfStudent 학생 수
    @return 잘못된 파라미터 입력시 false
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
        
        //인덱스가 유효성 검사.
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
    @detail 체육복을 확보한 최대 학생 수. 
    @return int 체육복을 확보한(student.suit == true)인 학생 수 리턴
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
    //return 5 - > 테스트 케이스 실패 다시 검토.
    /*int n = 5;
    vector<int> lost = { 2, 4 };
    vector<int> reserve = { 1, 3, 5 };*/

    //return 4
    int n = 5;
    vector<int> lost = { 2, 4 };
    vector<int> reserve = { 3 };


    int result = solution(n, lost, reserve);

    printf("최대값 : %d \n", result);
}