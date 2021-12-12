#include <string>
#include <vector>
#include <functional>

#define MAX_PHONEBOOK_SIZE 1000000

using namespace std;

//���� �˸�

struct stHASH
{
    size_t index;
    size_t lengthOfPrefix;    //�ؽ��� ���鶧 ����� �����Ƚ� ����
    size_t hashValue;
};

typedef vector<stHASH> HASH_TABLE;

bool MakeHash(size_t& out, string str, size_t length = 0);
bool CheckPrefix(vector<string> phone_book, stHASH& _pPrefix, stHASH& _pNumber);
bool MakeHashTable(HASH_TABLE out[], std::vector<string> src);

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
    HASH_TABLE vPhoneBookByLength[20];

    for (int i = 0; i < 20; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        vPhoneBookByLength[i].reserve(size);
    }

    //�����̷� ������.
    bool bResult = MakeHashTable(vPhoneBookByLength, phone_book);


    //3. �ڽź��� �� ���̿� ���� �˻�. 
    for (int i = 0; i < 20; i++)
    {
        if (answer == false) break;

        HASH_TABLE::iterator it;
        if (vPhoneBookByLength[i].size() == 0)
            continue;   //������ �˻��� �ʿ䰡 ����.

        for (it = vPhoneBookByLength[i].begin(); it != vPhoneBookByLength[i].end(); it++) {
            if (answer == false) break;

            stHASH pPrefix = *it;
            const string& prefix = phone_book.at(pPrefix.index);

            MakeHash(pPrefix.hashValue, prefix);
            pPrefix.lengthOfPrefix = prefix.size();

            //�ڽ��� ���� ��� ���� ���ʷ� �˻�
            for (int j = i + 1; j < 20; j++) {
                if (answer == false) break;
                HASH_TABLE::iterator itLongString;
                for (itLongString = vPhoneBookByLength[j].begin(); itLongString != vPhoneBookByLength[j].end(); itLongString++) {
                    stHASH pLongStr = (*itLongString);
                    
                    bool bIsPrefix = CheckPrefix(phone_book, pPrefix, pLongStr);

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

bool MakeHash(size_t& out, string str, size_t length) {
    bool bResult = false;
    size_t lengthOfStr = str.size();
    size_t lengthOfprefix = length;
    size_t sum = 0;
    string subString;

    //���ڿ� ���̰� 0�̸� �����ʿ����.
    if (lengthOfStr == 0)
        goto lb_return;

    if (lengthOfprefix == 0)
        lengthOfprefix = lengthOfStr;

    //���ڿ� ���̺��� Ŭ �� ����.
    if (lengthOfStr < lengthOfprefix)
        goto lb_return;

    std::hash<string> hash_string;
    subString = str.substr(0, lengthOfprefix);   //�����Ƚ���ŭ �ڸ���

    sum = hash_string(subString);

  
    bResult = true;
    out = sum;

lb_return:
    return bResult;
}

bool CheckPrefix(vector<string> phone_book, stHASH& _pPrefix, stHASH& _pNumber) {
    bool bResult = false;
    stHASH pPrefix = _pPrefix;
    stHASH pNumber = _pNumber;
    string prefix;
    string number;

    size_t sizeOfPhoneBook = phone_book.size();
    int iIndexOfPrefix = pPrefix.index;
    int iIndexOfNumber = pNumber.index;

    prefix = phone_book.at(iIndexOfPrefix);
    number = phone_book.at(iIndexOfNumber);

    //�ε��� ������ �˻� -prefix
    if (sizeOfPhoneBook < iIndexOfPrefix)
        goto lb_return;

    //�ε��� ��ȿ�� �˻� - number
    if (sizeOfPhoneBook < iIndexOfNumber)
        goto lb_return;

    //���ξ� ���̰� 0�̸� �˻��� �ʿ䰡 ����.
    if (prefix.size() == 0)
        goto lb_return;

    //���ξ� ���̰� �� �� �� ����.
    if (number.size() < prefix.size())
        goto lb_return;


    //���ξ� �ؽ����� ��ȿ���� �˻�
    if (pPrefix.lengthOfPrefix != pPrefix.lengthOfPrefix) {
        pPrefix.lengthOfPrefix = prefix.size();
        MakeHash(pPrefix.hashValue, prefix, pPrefix.lengthOfPrefix);
    }

    //����ȭ��ȣ�� �ؽ����� ��ȿ���� �˻�. ��ȿ���� ������ �����
    if (pNumber.lengthOfPrefix != pPrefix.lengthOfPrefix) {
        pNumber.lengthOfPrefix = prefix.size();
        MakeHash(pNumber.hashValue, number, pNumber.lengthOfPrefix);
    }
    
    if (pNumber.hashValue == pPrefix.hashValue) {
        //�ΰ��� ���ٸ� �� �˻�
        
        int comp = number.compare(0, pPrefix.lengthOfPrefix, prefix);
        if (comp == 0) {
            bResult = true;
        }
        
        /*
        pPrefix = (char*)prefix.c_str();
        pNumber = (char*)number.c_str();

        for (int i = 0; i < lengthOfPrefix; i++) {
            if (pPrefix[i] != pNumber[i]) {
                bResult = false;
                break;
            }
        }*/

    }

lb_return:

    return bResult;

}

bool MakeHashTable(HASH_TABLE phoneBook[], vector<string> src) {

    bool bResult = false;
    int index = 0;
    vector<string>::iterator it;
    
    //Check parameter
    if (phoneBook == nullptr)
        goto lb_result;
    
    if (src.size() == 0) 
        goto lb_result;

    //sort by phoneNumber size;
    
    for (it = src.begin(); it != src.end(); it++) {
        string* phoneNum = &(*(it + 0));
        size_t phoneNumLength = (*it).size();
        
        stHASH pHash;
        //pHash->data = phoneNum;
        pHash.hashValue = 0;
        pHash.lengthOfPrefix = 0;
        pHash.index = index;

        index++;
        //MakeHash(hashValue, phoneNum, static_cast<int>(phoneNumLength) );
        phoneBook[phoneNumLength - 1].push_back(pHash);
    }

    bResult = true;

lb_result:
    return bResult;
}
