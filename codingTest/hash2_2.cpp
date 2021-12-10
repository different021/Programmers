#include <string>
#include <vector>
#include <functional>


//��Ȳ
//phone_book�� ���̴� 1 �̻� 1,000,000 ����
//�� ��ȣ�� ���̴� 1 ~ 20
//�ߺ�����

//���1 
//1. ������ ��ȭ��ȣ���� ���̿� ���� �з�
//2. �ߺ��� �����Ƿ� ���� ���̸� �˻��� �ʿ䰡 ����.
//3. �ڽź��� �� ���̿� ���ؼ� ��� �˻�
//4. �ϳ��� �ɸ� ���, return false;

#define MAX_PHONEBOOK_SIZE 1000000
#define MAX_PHONE_SIZE 20

using namespace std;

struct stHASH {
    size_t index;
    size_t hashValue;
    size_t hashKey;
    string* pData;
};

typedef vector<stHASH*> HashTable_t;

bool solution(vector<string> phone_book);

//�ؽ����̺� ����
bool MakeHashTable(HashTable_t out[MAX_PHONE_SIZE], stHASH*& pHashArray, vector<string>& phone_book);
bool FreeHashTable(stHASH*& phashArray, HashTable_t phone_book[MAX_PHONE_SIZE]);

//�ؽð� ���� by Length
bool MakeHashValue(stHASH* pHash, size_t lengthOfStr = 0);

//���ξ �ִ��� ã�´�. (������ �� ���� ����ִ°� �� ���� ��) 
bool CompareHash(stHASH* pPrefix, stHASH* pStr);
bool FindPrefix(HashTable_t hashTable[MAX_PHONE_SIZE]);

//���ξ 
//  -�����ϸ� false
//  -������   true;
bool solution(vector<string> phone_book) {
    bool answer = true;
    bool bIsFind = false;
    HashTable_t table[20];
    stHASH* pHashArray = nullptr;
    MakeHashTable(table, pHashArray, phone_book);

    //ã���� true
    bIsFind = FindPrefix(table);
    if (bIsFind == true)
        answer = false;

    FreeHashTable(pHashArray, table);

    return answer;
}

/*
* input : vector<string> 
    �ִ� ������   : 1,000,000
    ���ڿ� ������ : 1 ~ 20 
 
* output : 
    1. pOutArray�� �޸� �Ҵ�
    2. out�� ���ڿ� ������ ���� ������ vector
 
*/
bool MakeHashTable(HashTable_t out[MAX_PHONE_SIZE], stHASH*& pOutArray, vector<string>& phone_book) {
    bool bResult = false;
    HashTable_t* pTable = out;
    vector<string>&  origin = phone_book;
    vector<string>::iterator it;
    size_t countOfData = origin.size();
    size_t index = 0;
    stHASH* pArray = nullptr;

    for (int i = 0; i < MAX_PHONE_SIZE; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        pTable[i].reserve(size);
    }

    size_t mallocSize = sizeof(stHASH) * countOfData;
    
    pArray = (stHASH*)malloc(mallocSize);
    if (pArray == nullptr) {
        //�޸� �Ҵ� ����
        goto lb_return;
    }
    else
    {
        //�޸� �Ҵ� ����
        //memset(pArray, 0, mallocSize);
    }

    index = 0;
    for (it = origin.begin(); it != origin.end(); it++)
    {
        if (index >= origin.size()) {
            //out of index
            int a = 3;
            break;
        }
        pArray[index].hashKey = 0;
        pArray[index].hashValue = 0;
        pArray[index].index = index;
        pArray[index].pData = &(*it);
        

        //������� �й�
        size_t lengthOfStr = pArray[index].pData->size();
        pTable[lengthOfStr].push_back(&pArray[index]);

        //MakeHashValue(&pArray[index]); -> �˻�� ����

        index++;
    }

    if (index != origin.size())
    {
        //�ʱ�ȭ ����
        //�޸� ����
        FreeHashTable(pArray, out);
        goto lb_return;
    }

    pOutArray = pArray;
    bResult = true;

lb_return:
    return bResult;
}

bool FreeHashTable(stHASH*& pHashArray, HashTable_t phone_book[MAX_PHONE_SIZE])
{
    if (pHashArray == nullptr) {
        goto lb_return;
    }

    free(pHashArray);

lb_return:
    return true;
}


bool MakeHashValue(stHASH* pHash, size_t lengthOfStr) {
    bool bResult = false;
    stHASH* pTarget = pHash;
    size_t strLength = 0;
    size_t newLength = lengthOfStr;
    string subString;

    //�߸��� �Ķ����1
    if (pTarget == nullptr)
        goto lb_return;

    strLength = pHash->pData->size();

    //�߸��� �Ķ����2
    if (strLength < newLength)
        goto lb_return;

    //0�� ��� ��ü ���̷� 
    if (newLength == 0)
        newLength = pTarget->pData->size();

    std::hash<string> hash_string;
    subString = pTarget->pData->substr(0, newLength);   //���ο� ���� Ű������ �ڸ���

    pTarget->hashKey = newLength;
    pTarget->hashValue = hash_string(subString);
    bResult = true;

lb_return:
    return bResult;
}

//�ΰ��� �ؽ� ��
//return: 
// prefix�� �����ϸ� true
//when _pStr has prefix
bool CompareHash(stHASH* _pPrefix, stHASH* _pStr) {
    bool bResult = false;
    stHASH* pPrefix = _pPrefix;
    stHASH* pStr = _pStr;
    
    if (pPrefix == nullptr)
        goto lb_return;

    if (pStr == nullptr)
        goto lb_return;

    if (pPrefix->hashKey != pPrefix->pData->size()) {
        //�ؽð� �ٽ� ȹ��
        MakeHashValue(pPrefix);
    }

    if (pStr->hashKey != pPrefix->hashKey) {
        //�ؽð� Ű���� ���� �ٽ� ����
        MakeHashValue(pStr, pPrefix->hashKey);
    }

    if (pStr->hashValue == pPrefix->hashValue) {
        //�ؽ����� ������ ������ �˻�
        
        int comp = pStr->pData->compare(0, pPrefix->hashKey, *pPrefix->pData);
        if (comp == 0) {
            bResult = true;
        }
        int a = 0;
    }

lb_return:
    return bResult;
}

//prefix�� 
//  -ã���� : true;
//  -������ : false;
bool FindPrefix(HashTable_t hashTable[MAX_PHONE_SIZE]) {
    bool bResult = false;
    HashTable_t* pTable = hashTable;

    for (int i = 0; i < MAX_PHONE_SIZE - 1; i++) {
        if (bResult == true) break;
        HashTable_t::iterator itPrefix;
        
        if (pTable[i].size() == 0)
            continue;   //������ �˻��� �ʿ䰡 ����.

        for (itPrefix = pTable[i].begin(); itPrefix != pTable[i].end(); itPrefix++) {
            if (bResult == true) break;
            stHASH* pPrefix = (*itPrefix);

            for (int j = i + 1; j < MAX_PHONE_SIZE; j++) {
                if (bResult == true) break;
                HashTable_t::iterator itStr;
                for (itStr = pTable[j].begin(); itStr != pTable[j].end(); itStr++) {
                    stHASH* pStr = *itStr;
                    bResult = CompareHash(pPrefix, pStr);
                    if (bResult == true) {
                        break;
                    }
                }
            }
        }
    }

    return bResult;
}

int main()
{
    //vector<string> phone_book{ "119", "97674223", "1195524421" };
    vector<string> phone_book{"123", "456", "789"};
    //vector<string> phone_book{ "12", "123", "1235", "567", "88" };
    //vector<string> phone_book{ "12", "112" };
    bool bResult = solution(phone_book);

    if (bResult == true)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}