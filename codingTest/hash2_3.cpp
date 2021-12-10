//��Ȳ
//phone_book�� ���̴� 1 �̻� 1,000,000 ����
//�� ��ȣ�� ���̴� 1 ~ 20
//�ߺ�����

//���1 
//1. ������ ��ȭ��ȣ���� ���̿� ���� �з�
//2. �ߺ��� �����Ƿ� ���� ���̸� �˻��� �ʿ䰡 ����.
//3. �ڽź��� �� ���̿� ���ؼ� ��� �˻�
//4. �ϳ��� �ɸ� ���, return false;


#include <string>
#include <vector>
#include <functional>

#define MAX_PHONEBOOK_SIZE 1000000

using namespace std;

struct stHASH
{
    size_t index;
    size_t hashKey;    //�ؽ��� ���鶧 ����� �����Ƚ� ����
    size_t hashValue;
};

typedef vector<stHASH> HASH_TABLE;

bool MakeHashValue(vector<string>& phone_book, stHASH* pHash, size_t hashKey = 0);
bool CompareHash(vector<string>& phone_book, stHASH* pPrefix, stHASH* pStr);
bool CheckPrefix(vector<string>& phone_book, stHASH& _pPrefix, stHASH& _pNumber);
bool MakeHashTable(HASH_TABLE out[], std::vector<string> src);

bool solution(vector<string> phone_book) {
    bool answer = true;

    HASH_TABLE hashTable[20];

    for (int i = 0; i < 20; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        hashTable[i].reserve(size);
    }

    //�����̷� ������.
    bool bResult = MakeHashTable(hashTable, phone_book);


    //3. �ڽź��� �� ���̿� ���� �˻�. 
    for (int i = 0; i < 20; i++)
    {
        if (answer == false) break;

        HASH_TABLE::iterator it;
        if (hashTable[i].size() == 0)
            continue;   //������ �˻��� �ʿ䰡 ����.

        for (it = hashTable[i].begin(); it != hashTable[i].end(); it++) {
            if (answer == false) break;

            stHASH pPrefix = *it;
            const string& prefix = phone_book.at(pPrefix.index);

            MakeHashValue(phone_book, &pPrefix);
            //MakeHash(pPrefix.hashValue, prefix);
            //pPrefix.hashKey = prefix.size();

            //�ڽ��� ���� ��� ���� ���ʷ� �˻�
            for (int j = i + 1; j < 20; j++) {
                if (answer == false) break;
                HASH_TABLE::iterator itLongString;
                for (itLongString = hashTable[j].begin(); itLongString != hashTable[j].end(); itLongString++) {
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
    size_t hashValue = 0;
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

    hashValue = hash_string(subString);


    bResult = true;
    out = hashValue;

lb_return:
    return bResult;
}

bool MakeHashValue(vector<string>& phone_book, stHASH* pHash, size_t _hashKey) {
    bool bResult = false;
    vector<string> book = phone_book;
    size_t hashKey = _hashKey;
    stHASH* pTarget = pHash;
    string substring;
    string* pStr;

    pStr = &book.at(pTarget->index);
    if (hashKey == 0)
        hashKey = pStr->size();

    std::hash<string> hash_string;
    substring = pStr->substr(0, hashKey);   //���ο� ���� Ű������ �ڸ���

    pTarget->hashValue = hash_string(substring);
    pTarget->hashKey = hashKey;

lb_return:
    return bResult;
}

bool CompareHash(vector<string>& phone_book, stHASH* _pPrefix, stHASH* _pStr) {
    bool bResult = false;
    vector<string> book = phone_book;
    size_t bookSize = 0;
    stHASH* pPrefix = _pPrefix;
    stHASH* pStr = _pStr;
    string* prefix = nullptr;
    string* str = nullptr;
    string subString;
    int comp = -1;

    if (pPrefix == nullptr) goto lb_return;
    if (pStr == nullptr) goto lb_return;

    bookSize = book.size();
    if (bookSize == 0) goto lb_return;

    if (pPrefix->index > bookSize) goto lb_return;
    prefix = &book.at(pPrefix->index);

    if (pStr->index > bookSize) goto lb_return;
    str = &book.at(pStr->index);

    if (pPrefix->hashKey != prefix->size()) {
        MakeHashValue(book, pPrefix);
    }

    if (pStr->hashKey != pPrefix->hashKey) {
        MakeHashValue(book, pStr, pPrefix->hashKey);
    }

    comp = str->compare(0, pPrefix->hashKey, *prefix);
    if (comp == 0) {
        bResult = true;
    }


lb_return:
    return bResult;
}

bool CheckPrefix(vector<string>& phone_book, stHASH& _pPrefix, stHASH& _pNumber) {
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


    if (pPrefix.hashKey != pPrefix.hashKey) {
        MakeHashValue(phone_book, &_pPrefix);
        //pPrefix.hashKey = prefix.size();
        //MakeHash(pPrefix.hashValue, prefix, pPrefix.hashKey);
    }

    if (pNumber.hashKey != pPrefix.hashKey) {
        MakeHashValue(phone_book, &pNumber, pPrefix.hashKey);
        //pNumber.hashKey = prefix.size();
        //MakeHash(pNumber.hashValue, number, pNumber.hashKey);
    }

    if (pNumber.hashValue == pPrefix.hashValue) {
        //�ΰ��� ���ٸ� �� �˻�

        int comp = number.compare(0, pPrefix.hashKey, prefix);
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
        pHash.hashKey = 0;
        pHash.index = index;

        index++;
        phoneBook[phoneNumLength - 1].push_back(pHash);
    }

    bResult = true;

lb_result:
    return bResult;
}


int main()
{
    //vector<string> phone_book{ "119", "97674223", "1195524421" };
    vector<string> phone_book{ "123", "456", "789" };
    //vector<string> phone_book{ "12", "123", "1235", "567", "88" };
    //vector<string> phone_book{ "12", "112" };
    bool bResult = solution(phone_book);

    if (bResult == true)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}