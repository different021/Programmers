/*
    [����]
    ���Ϳ� ���ڿ��� ��ɾ ��� �ִ�.
    ��ɾ� I�� ���� �ڿ� �̾����� ���ڸ� ����
    ��ɾ� D�� ��� ���� �� �̾����� ���ڰ�
         1�� ��� : �ִ밪 ����
        -1�� ��� : �ּҰ� ����

    ��ɾ ������ �������� �ִ밪�� �ּҰ��� �����Ͻÿ�.


    [�Ķ����]
    vector<string> operations : ��ɾ� ����
    �Ʒ��� ���� Ŀ�ǵ尡 ��� �ִ�.

    [Ŀ�ǵ�]
     I n    : ť�� ���� n ����
     D 1    : ť�� �ִ밪 ����
     D -1   : ť�� �ִ밪 ����

    [����]
    vector<int> 
    (�ִ밪, �ּҰ�)�� ����
    ť�� ��� �ִٸ� (0, 0) ����
    
    [���� 1]
    parameter       return
    ["I 16","D 1"]	[0,0]
    
    I 16    : 16����          Que = { 16 }
    D 1     : �ִ밪 ����      Que = {}
    ��� �����Ƿ� return  (0, 0)

    [���� 2]
    parameter                       return
    ["I 7","I 5","I -5","D -1"]	    [7,5]

    I 7     : 7 ����                  { 7 }
    I 5     : 5 ����                  { 7, 5 }
    I -5    : -5����                  { 7, 5, - 5 }
    D -1    : �ּҰ� ����(-5)          {7, 5 }

    return  (7 , 5)
        (�ִ밪, �ּҰ�)
    
    
    [���ѻ���]
    operations.size() : 1 ~ 1000000
    ������ �ִ�, �ּҰ��� ������ ��� �ϳ��� ����.     ex) { 5, 5, 3, 4, 1, -1, -1 } �� ��� 5�Ѱ� �Ǵ� 1 �Ѱ��� ����.
    �� ť������ ������ �����Ѵ�.                      ex) { }  Nothing to do heapeen when I wonder

    [������� ���̽� ]
    1. �����Ͱ� �ϳ��� ���   ex) { 1 } 
        �ִ� �ּҰ��� ���� �����ϳ�?

*/

/*
    [����Ʈ]
    1. Ŀ�ǵ� �Ľ�
        �ش� ��ɾ ���� ������ ��������.
    2. �� �� ��� ���Ű����� �ڷᱸ��
        D  1 : �ִ밪 ����
        D -1 : �ּҰ� ����
        I  n : n ����(n�� ����)

        ũ�⺰�� ���ĵǾ� �ִ� ���� ����.
        �켱����ť�� ����� ��� �ڸ� �����ϴ°��� �����.
        ��ť�� �̿��ϸ� �յ�(�ִ�, �ּ�) ���ſ� ����
*/

/*
    [üũ�� ����]
    dequeue
     ���� : �յ� ���� ����
     ���� : 
        ���Խ� ���ľȵ�.
        ���� ��Ȳ������ ���Ը��� �����ؾ��Ѵ�.

    priority_queue
    ���� : ���ĵǼ� ����.
    ���� :
        ������ ������ ���� ����(pop) �ۿ� ����.
        (�� ��Ȳ������, �յ� ��ο��� ������ �Ͼ��.)

    �յ� ���� �� ������ ������ ����ϰ� �߻��� ������ ����.
    ��ť�� �ϴ� �����غ���.

    �Ľ� �ʿ�, 
    std::string�� �Լ� Ȯ���� ��.

    [���]
    
    1. �Ľ�
    ��ɾ� ���� : (���ڿ�+����) + ����  
    ������� ���ڿ��� �а�, �м�
    ���� ���� ó��
    (��ȿ�� �˻� + ��ɾ� Ȯ��)

    2. ť
    ������ ũ��� ���ĵ� �ڷ� ����
    �յ� ���� ����
    �� ť�϶� ���� ��� ����
*/

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

enum eOPERATION
{
    eOP_INPUT = 0,
    eOP_DELETE,
    eOP_MAX,
};

//����� ��ɾ� -> ���� ����
const string OPERATION_INPUT    = "I";
const string OPERATION_DELETE   = "D";

struct stOPERATION
{
    eOPERATION op;
    int value;
};

bool comp(const int& a, const int& b)
{
    return a > b;
};

class cOperationDeque
{
    map<string, eOPERATION> operationList;            //����� ����Ʈ
    deque<int> que;

    //interface function
public:
    bool inputOperation(string operation);
    bool getResult(vector<int>& out);

    //class fuctions
    cOperationDeque();
    ~cOperationDeque();

    bool initalizeOperationList();

private:
    bool checkOperation(stOPERATION& out, string input);        //��ȿ�� ����, ������ ��� �����
    bool findOperation(eOPERATION& op, string str);
    bool excuteOperation(stOPERATION& op);                      //��ɿ� ���� ����

    bool push(int input);
    bool pop(int value);    //only 1 or -1 (pop MAX : 1, pop MIN : -1)
    
    const int front();        //return (���� ū��)    ����� ��� return 0
    const int back();         //return (���� ���� ��) ����� ��� return 0
};

/*
    [LOGIC]
    1. �Ķ���� ��ȿ�� �˻�
    2. ��ȿ�� �� ��ɾ� ����
    3. ������ ��ɾ� ����
*/
bool cOperationDeque::inputOperation(string _input)
{
    bool bResult = false;
    bool bSuccess = false;
    string& input = _input;
    stOPERATION op;

    //1. ��ȿ�� �˻� -> ������ ��ɾ� ����
    bSuccess = checkOperation(op,input);
    if (bSuccess == false) goto lb_return;

    //3. ��ɾ� ����
    bSuccess = excuteOperation(op);
    if (bSuccess != true) goto lb_return;

    bResult = true;

lb_return:
    return bResult;
}

/*
    [���]
    ���� ť�� �ִ밪�� �ּҰ��� ��� ����
    ť�� ������� ��� (0, 0) ����

    [LOGIC]
    1. out.push(que.front)
    2. out.push(que.back)

    [output] 
    (�ִ밪, �ּҰ�0
    (que.front, que.back)

    [return]
    ť�� ������� ���� ��� true;
*/
bool cOperationDeque::getResult(vector<int>& out)
{
    bool bResult = false;
    
    //front(), back() �Լ����� ��ȿ�� �˻� ��. ���ص� ������ ������.
    int max = front();
    int min = back();

    out.push_back(max);
    out.push_back(min);

    return bResult;
}

cOperationDeque::cOperationDeque()
{
    //Nothing
}

cOperationDeque::~cOperationDeque()
{
    //Nothing
}

bool cOperationDeque::initalizeOperationList()
{
    bool bResult = false;

    //Ŀ�ǵ尡 �߰� �Ǿ �ڵ����� �Ǵ� ���� �߰��Ұ�.
    operationList.insert( { OPERATION_INPUT, eOP_INPUT } );
    operationList.insert( { OPERATION_DELETE, eOP_DELETE } );

    return bResult;
}


//������ �˻� �ȵ�...
bool isNumber(const string& str)
{
    bool bResult = true;
    const char* num = str.c_str();

    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(num[i]) == 0)
        {
            if (i == 0)
            {
                if (num[i] == '-')
                {
                    continue;
                }
                else
                {
                    bResult = false;
                    break;
                }
            }

        }
        
    }
    //for (char const& c : str)
    //{
    //    if (isdigit(c) == 0)
    //    {
    //        //���ڰ� �ƴ� ���� ����
    //        bResult = false;
    //        break;
    //        
    //    }
    //}

    return bResult;
}

/*
    [����]
    �ش� ������ �Ľ�.
    �츮�� ��ɾ� ü��� ��ġ ���� �˻�
    
    [return]
    ��ġ�� ��� true

    [����]
    Check only Parameter invaildate

    [�Լ��� ���� ���]
    checkInput

    [LOGIC]
    ������ �������� �ڸ���.
    ������ ������ �߸��� ��ɾ�
    ���� ���� ���ڰ� D�� I�� �ƴϸ� �߸��� ��ɾ�
    ���� ���� ���ڰ� ���ڰ� �ƴϸ� �߸��� ��ɾ�

    //�Լ��� ���� ���. ������ ��Ȯ���� ���� �̸�.
*/
bool cOperationDeque::checkOperation(stOPERATION& out, string _input)
{
    bool bResult = false;
    string input = _input;
    string spaceFront;  //���� ��
    string spaceBack;   //���� ��
    eOPERATION eOP = eOP_MAX;
    int value = 0;

    size_t spacePos = input.find(" ");
    if (spacePos == string::npos) goto lb_return;

    spaceFront = input.substr(0, spacePos);
    spaceBack = input.substr(spacePos + 1, input.size());

    //spaceFront�� ��ɾ����� Ȯ���ϴ� ����
    bResult = findOperation(eOP, spaceFront);
    if (bResult == false) goto lb_return;

    //spaceBack�� �������� Ȯ���ϴ� ����
    //isNumeber�� ������ �������� ���Ѵ�. -> ����. 
    //stoi�� ���н� �ͼ����� �߻� ��Ų��.
    if (isNumber(spaceBack) == false) goto lb_return;
    value = stoi(spaceBack);
    
    //����� ����
    out.op = eOP;
    out.value = value;

    //��� ���� ����
    bResult = true;

lb_return:
    return bResult;
}

//�Է��� ��ɾ �����ϴ��� ��ɾ� ����Ʈ���� �˻�.
bool cOperationDeque::findOperation(eOPERATION& op, string input)
{
    bool bResult = false;
    
    auto operation = operationList.find(input);
    if (operation == operationList.end()) goto lb_return;
    op = operation->second;
    bResult = true;

lb_return:
    return bResult;
}

//Not Implements
bool cOperationDeque::excuteOperation(stOPERATION& op)
{
    bool bResult = true;

    switch (op.op)
    {
    case eOP_INPUT:
        bResult = push(op.value);
        break;
    
    case eOP_DELETE:
        bResult = pop(op.value);
        break;

    default:
        //����� �۾��߿� ����?
        //aseert(false);
        bResult = false;
        break;
    }

    return bResult;
}


//
bool cOperationDeque::push(int input)
{
    bool bResult = true;
    que.push_back(input);
    sort(que.begin(), que.end(), comp);

    return bResult;
}

//[���� �ʿ�]�Ķ���� �˻� ȿ�� �� Ȯ�� ������ ������
bool cOperationDeque::pop(int value)
{
    bool bResult = true;
    int val = value;
    
    if (que.size() == 0) goto lb_return;

    if (val == 1)
    {
        //�ִ밪 ����.
        que.pop_front();
    }
    else if (val == -1)
    {
        //�ּҰ� ����
        que.pop_back();
    }
    else
    {
        //�߸��� �Ķ����
        bResult = false;
    }

lb_return:
    return bResult;
}

const int cOperationDeque::front()
{
    int iResult = 0;
    if (que.size() == 0) goto lb_return;
    iResult = que.front();

lb_return:
    return iResult;
}

const int cOperationDeque::back()
{
    int iResult = 0;
    if (que.size() == 0) goto lb_return;
    iResult = que.back();

lb_return:
    return iResult;
}


vector<int> solution(vector<string> operations) {
    vector<int> answer;
    cOperationDeque opHandler;
    size_t safeCnt = 0;
    //Ŀ�ǵ� �ʱ�ȭ
    opHandler.initalizeOperationList();

    
    //�Լ�ȭ?
    for (auto& it : operations)
    {
        bool bSuccess = opHandler.inputOperation(it);       //�ٽ� �Լ�
        if (bSuccess == false)
        {
            //���� -> �߸��� �Ķ����
            //assert(false);
            break;
        }
        safeCnt++;
    }

    //Ŀ�ǵ� ���� ����.
    if (operations.size() != safeCnt)
    {
        //asert(false);
        //�߸� �� ��ɾ� ���� ���� ���ɼ� ����.
        int a = 0;
    }

    bool bSuccess = opHandler.getResult(answer);
    {
        //�Լ� ����
    }

    return answer;
}






int main()
{

    //return (0, 0)
    //vector<string> operations = { "I 16", "D 1" };

    //[7, 5]
    vector<string> operations = { "I 7", "I 5", "I -5", "D -1" };

    //(0, 0)
    //vector<string> operations = { "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" };
      
    vector<int> result = solution(operations);


    //��� ���
    printf("������� : \n");
    for (auto& it : result)
    {
        printf("%d \n", it);
    }


    return 0;
}