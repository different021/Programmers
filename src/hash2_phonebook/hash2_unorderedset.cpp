#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#define MAX_DATA_SIZE   1000000
#define MAX_STRING_SIZE 20

using namespace std;

bool InsertInSet(unordered_set<string>& phone_set, string& str, size_t maxStringSize);
bool QueryToSet(unordered_set<string>& phone_set, string& str);
bool CompareByStringLength(string str1, string str2);

bool solution(vector<string> phone_book) {
    bool answer = true;
    vector<string>& book = phone_book;      
    unordered_set<string> phoneSet;     

    //���ڿ��� ����� ������ ������ ����
    sort(book.begin(), book.end(), CompareByStringLength);

    vector<string>::iterator it;
    for (it = book.begin(); it != book.end(); it++) {
        string& str = (*it);
        bool bExist = InsertInSet(phoneSet, str, MAX_STRING_SIZE);
        if (bExist == true) {
            //���ξ ����.
            answer = false;
            break;
        }
    }

    return answer;
}


//���ڿ��� ��� ���ξ �����Ͽ� set�� �ִ´�.
/*
* return : 
*   �ڱ� �ڽ��� �����Ͽ� �����ϸ� false (���ξ�� �����Ѵ�.)
*   ������ �ڽ��� ���������� ���ξ� ��, set�� ���� ���� �߰��Ѵ�.
*/
bool InsertInSet(unordered_set<string>& phone_set, string& str, size_t maxStringSize) {
    //1. ������ ��� prefix�� ������.
    //2. ���簡���� prefix�� �������� �ʴ´ٸ� �ִ´�.
    //�ڱ� �ڽ��� ���� �ʿ䰡 ����.
    bool bResult = false;
    
    string& newString = str;
    size_t strSize = newString.size();

    //�ִ� ���̰� �ƴϸ� �ڱ��ڽ��� �����ϴ��� ����
    if (str.size() != maxStringSize)
    {
        bool bExsit = QueryToSet(phone_set, newString);
        if (bExsit == true) {
            bResult = true; //�ֳ�? �׸� ã�Ƶ� �ȴ�.
            goto lb_result;
        }
    }

    //�ƴ� ��� ���꽺Ʈ���� ����� ���� Ŀ��
    for (int i = 1; i < strSize; i++) {
        string subString = newString.substr(0, i);
        bool bIsPrefixExsit = QueryToSet(phone_set, subString);
        
        if (bIsPrefixExsit == false)
            phone_set.insert(subString); //���� ���ξ�� set�� �߰�
    }

lb_result:
    return bResult;
}

//return : �Ķ������ ���ڿ���
// �����ϸ� true
// ������ false
bool QueryToSet(unordered_set<string>& phone_set, string& str) {
    bool bResult = true;
    unordered_set<string>& phoneSet = phone_set;
    string& qryStr = str;

    unordered_set<string>::iterator itr = phoneSet.find(qryStr);
    if (itr != phoneSet.end()) {
        //ã��
    }
    else {
        //��ã��
        bResult = false;
    }
    
    return bResult;
}

bool CompareByStringLength(string str1, string str2) {
    //���ڿ��� ��� ������ ����.
    return str1.size() > str2.size();
}

int main()
{
    vector<string> phone_book{ "119", "97674223", "1195524421" };
    //vector<string> phone_book{ "123", "456", "789" };
    //vector<string> phone_book{ "12", "123", "1235", "567", "88" };
    //vector<string> phone_book{ "12", "112" };
    bool bResult = solution(phone_book);

    if (bResult == true)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}