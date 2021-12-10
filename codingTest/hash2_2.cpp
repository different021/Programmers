#include <string>
#include <vector>
#include <functional>


//상황
//phone_book의 길이는 1 이상 1,000,000 이하
//각 번호의 길이는 1 ~ 20
//중복없다

//방법1 
//1. 벡터의 전화번호들을 길이에 따라 분류
//2. 중복이 없으므로 동일 길이를 검사할 필요가 없다.
//3. 자신보다 긴 길이에 대해서 모두 검사
//4. 하나라도 걸릴 경우, return false;

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

//해시테이블 생성
bool MakeHashTable(HashTable_t out[MAX_PHONE_SIZE], stHASH*& pHashArray, vector<string>& phone_book);
bool FreeHashTable(stHASH*& phashArray, HashTable_t phone_book[MAX_PHONE_SIZE]);

//해시값 생성 by Length
bool MakeHashValue(stHASH* pHash, size_t lengthOfStr = 0);

//접두어가 있는지 찾는다. (있으면 그 둘을 뱉어주는게 더 좋을 듯) 
bool CompareHash(stHASH* pPrefix, stHASH* pStr);
bool FindPrefix(HashTable_t hashTable[MAX_PHONE_SIZE]);

//접두어가 
//  -존재하면 false
//  -없으면   true;
bool solution(vector<string> phone_book) {
    bool answer = true;
    bool bIsFind = false;
    HashTable_t table[20];
    stHASH* pHashArray = nullptr;
    MakeHashTable(table, pHashArray, phone_book);

    //찾으면 true
    bIsFind = FindPrefix(table);
    if (bIsFind == true)
        answer = false;

    FreeHashTable(pHashArray, table);

    return answer;
}

/*
* input : vector<string> 
    최대 사이즈   : 1,000,000
    문자열 사이즈 : 1 ~ 20 
 
* output : 
    1. pOutArray에 메모리 할당
    2. out에 문자열 사이즈 별로 정리된 vector
 
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
        //메모리 할당 실패
        goto lb_return;
    }
    else
    {
        //메모리 할당 성공
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
        

        //사이즈별로 분배
        size_t lengthOfStr = pArray[index].pData->size();
        pTable[lengthOfStr].push_back(&pArray[index]);

        //MakeHashValue(&pArray[index]); -> 검사시 생성

        index++;
    }

    if (index != origin.size())
    {
        //초기화 실패
        //메모리 해제
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

    //잘못된 파라미터1
    if (pTarget == nullptr)
        goto lb_return;

    strLength = pHash->pData->size();

    //잘못된 파라미터2
    if (strLength < newLength)
        goto lb_return;

    //0일 경우 전체 길이로 
    if (newLength == 0)
        newLength = pTarget->pData->size();

    std::hash<string> hash_string;
    subString = pTarget->pData->substr(0, newLength);   //새로운 기준 키값으로 자르기

    pTarget->hashKey = newLength;
    pTarget->hashValue = hash_string(subString);
    bResult = true;

lb_return:
    return bResult;
}

//두개의 해쉬 비교
//return: 
// prefix가 존재하면 true
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
        //해시값 다시 획득
        MakeHashValue(pPrefix);
    }

    if (pStr->hashKey != pPrefix->hashKey) {
        //해시값 키값에 맞춰 다시 생성
        MakeHashValue(pStr, pPrefix->hashKey);
    }

    if (pStr->hashValue == pPrefix->hashValue) {
        //해쉬값이 같으면 정교한 검사
        
        int comp = pStr->pData->compare(0, pPrefix->hashKey, *pPrefix->pData);
        if (comp == 0) {
            bResult = true;
        }
        int a = 0;
    }

lb_return:
    return bResult;
}

//prefix가 
//  -찾으면 : true;
//  -없으면 : false;
bool FindPrefix(HashTable_t hashTable[MAX_PHONE_SIZE]) {
    bool bResult = false;
    HashTable_t* pTable = hashTable;

    for (int i = 0; i < MAX_PHONE_SIZE - 1; i++) {
        if (bResult == true) break;
        HashTable_t::iterator itPrefix;
        
        if (pTable[i].size() == 0)
            continue;   //없으면 검사할 필요가 없다.

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