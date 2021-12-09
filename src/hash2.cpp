#include <string>
#include <vector>
#define MAX_PHONEBOOK_SIZE 1000000

using namespace std;

bool MakeHash(int& out, string str, int length = 0);
bool MakePrefixHash(int& out, string number, int prefixSize = 0);
bool CheckPrefix(int hashValue, string prefix, string longNumber);
bool MakePhoneBookByLength(std::vector<string> out[], std::vector<string> src);

bool solution(vector<string> phone_book) {
    bool answer = true;

    //���� ����
    //phone_book�� ���̴� 1 �̻� 1,000,000 ����
    //�� ��ȣ�� ���̴� 1 ~ 20
    //�ߺ�����

    //���1 
    //1. ������ ��ȭ��ȣ���� ���̿� ���� �з�
    //2. �ߺ��� �����Ƿ� ���� ���̸� �˻��� �ʿ䰡 ����.
    //3. �ڽź��� �� ���̿� ���ؼ� ��� �˻�
    //4. �ϳ��� �ɸ� ���, return false;


    //1. ������ ��ȣ���� ���̿� ���� �з�
    //20�� �迭 �غ� -> ���� �� �迭���� �ʿ������� ���̰� �ٸ��� �ۿ� ����
    vector<string> vPhoneBookByLength[20];

    for (int i = 0; i < 20; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        vPhoneBookByLength[i].reserve(size);
    }

    //�����̷� ������.
    bool bResult = MakePhoneBookByLength(vPhoneBookByLength, phone_book);


    //3. �ڽź��� �� ���̿� ���� �˻�. 
    for (int i = 0; i < 20; i++)
    {
        if (answer == false) break;

        vector<string>::iterator it;
        if (vPhoneBookByLength[i].size() == 0)
            continue;   //������ �˻��� �ʿ䰡 ����.

        for (it = vPhoneBookByLength[i].begin(); it != vPhoneBookByLength[i].end(); it++) {
            if (answer == false) break;

            string prefix = *it;
            int hashValue = 0;
            MakeHash(hashValue, prefix);

            //�ڽ��� ���� ��� ���� ���ʷ� �˻�
            for (int j = i + 1; j < 20; j++) {
                if (answer == false) break;
                vector<string>::iterator itLongString;
                for (itLongString = vPhoneBookByLength[j].begin(); itLongString != vPhoneBookByLength[j].end(); itLongString++) {
                    string longStr = *itLongString;
                    bool bIsPrefix = CheckPrefix(hashValue, prefix, longStr);

                    if (bIsPrefix == true)
                    {
                        answer = false;
                        break;
                    }
                        
                }
                
            }

        }
        
    }

    int a = 0;
    return answer;
}

bool MakeHash(int& out, string str, int length) {
    bool bResult = false;
    int lengthOfStr = str.size();
    int sum = 0;
    int lengthOfprefix = length;
    char* pStr = nullptr;

    //���ڿ� ���̰� 0�̸� �����ʿ����.
    if (lengthOfStr == 0)
        goto lb_return;

    if (lengthOfprefix == 0)
        lengthOfprefix = lengthOfStr;

    //���ڿ� ���̺��� Ŭ �� ����.
    if (lengthOfStr < lengthOfprefix)
        goto lb_return;

    pStr = (char*)str.c_str();
    for (int i = 0; i < lengthOfprefix; i++) {

        sum += pStr[i];
    }
   
    bResult = true;
    out = sum;

lb_return:
    return bResult;
}

bool MakePrefixHash(int& out, string number, int prefix_Size) {
    bool bResult = false;
    int length = number.size();
    int prefixSize = prefix_Size;
    int checkSize = 0;
    int sum = 0;
    char* pStr = nullptr;

    //check parameter
    if (length == 0)
        goto lb_return;

    //���ξ ���ڿ� ��ü ���̺��� Ŭ �� ����.
    if (length < prefixSize)
        goto lb_return;
    
    
    if (prefixSize == 0) {
        //����Ʈ�� ���ڿ� ��ü�� �̿��� �ؽ����� �����Ѵ�.
        checkSize = length;
    }
    else {
        //Ư������ �����ϸ� �� ���� ��ŭ �ؽ��� ����
        checkSize = prefixSize;
    }
     
    bResult = MakeHash(sum, number, prefixSize);
    
    if (bResult == true)
    {
        out = sum;
    }
    

lb_return:
    return bResult;
}

bool CheckPrefix(int hashValue, string prefix, string number) {
    bool bResult = false;
    int numberHash = 0;
    int lengthOfPrefix = prefix.size();
    int lengthOfNumber = number.size();
    char* pPrefix = nullptr;
    char* pNumber = nullptr;

    //���ξ� ���̰� 0�̸� �˻��� �ʿ䰡 ����.
    if (lengthOfPrefix == 0)
        goto lb_return;

    //���ξ� ���̰� �� �� �� ����.
    if (lengthOfNumber < lengthOfPrefix)
        goto lb_return;
    
    //�ؽ� ���� ����
    MakeHash(numberHash, number, lengthOfPrefix);
    
    if (numberHash == hashValue) {
        //�ΰ��� ���ٸ� �� �˻�
        pPrefix = (char*)prefix.c_str();
        pNumber = (char*)number.c_str();
        
        bResult = true;
        for (int i = 0; i < lengthOfPrefix; i++) {
            if (pPrefix[i] != pNumber[i]) {
                bResult = false;
                break;
            }
        }

    }

lb_return:

    return bResult;

}

bool MakePhoneBookByLength(vector<string> phoneBook[], vector<string> src) {

    bool bResult = false;
    vector<string>::iterator it;
    
    //Check parameter
    if (phoneBook == nullptr)
        goto lb_result;
    
    if (src.size() == 0) 
        goto lb_result;

    //sort by phoneNumber size;
    for (it = src.begin(); it != src.end(); it++) {
        string phoneNum = (*it);
        size_t phoneNumLength = (*it).size();
        phoneBook[phoneNumLength - 1].push_back(phoneNum);
    }

    bResult = true;

lb_result:
    return bResult;
}

int main()
{
    //vector<string> phone_book{ "119", "97674223", "1195524421" };
    //vector<string> phone_book{"123", "456", "789"};
    //vector<string> phone_book{ "12", "123", "1235", "567", "88" };
    vector<string> phone_book{ "12", "112" };
    bool bResult = solution(phone_book);

    if (bResult == true)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}