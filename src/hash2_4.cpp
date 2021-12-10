
#include <string>
#include <vector>
#include <functional>
#include <memory.h>

#define MAX_PHONEBOOK_SIZE 1000000
#define MAX_PHONE_LENGTH 20
using namespace std;

struct stHash {
    size_t  hashKey = 0;
    size_t  hashValue = 0;
};

bool MakeHash(int& out, string str, int length = 0);
bool CheckPrefix(size_t hashValue, string prefix, string longNumber);
bool CheckPrefix(stHash* pArray, size_t size, size_t index, size_t hashValue, string prefix, string longNumber);
bool MakePhoneBookByLength(size_t& outMaxSize, std::vector<string> out[], std::vector<string> src);

bool solution(vector<string> phone_book) {
    bool answer = true;

    vector<string> vHashTable[MAX_PHONE_LENGTH];
    size_t maxSize = 0;
    stHash* pHashArray = nullptr;

    for (int i = 0; i < MAX_PHONE_LENGTH; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        vHashTable[i].reserve(size);
    }

    //각길이로 보낸다.
    bool bResult = MakePhoneBookByLength(maxSize, vHashTable, phone_book);
    
    if (maxSize != 0) {
        pHashArray = new stHash[maxSize];
    }

    //3. 자신보다 긴 길이에 대해 검사. 
    for (int i = 0; i < MAX_PHONE_LENGTH; i++)
    {
        if (answer == false) break;

        vector<string>::iterator it;
        if (vHashTable[i].size() == 0)
            continue;   //없으면 검사할 필요가 없다.

        for (it = vHashTable[i].begin(); it != vHashTable[i].end(); it++) {
            if (answer == false) break;

            string prefix = *it;
            int hashValue = 0;
            MakeHash(hashValue, prefix);
            
            
            size_t  size = 0;
            //자신의 다음 대상 부터 차례로 검사
            for (int j = i + 1; j < MAX_PHONE_LENGTH; j++) {
                
                if (answer == false) break;

                vector<string>::iterator itLongString;
                int index = 0;
                for (itLongString = vHashTable[j].begin(); itLongString != vHashTable[j].end(); itLongString++) {
                    
                    size = vHashTable[j].size();
                    string longStr = *itLongString;
                    bool bIsPrefix = false;
                    /*if (size < 10) {
                        bIsPrefix = CheckPrefix(hashValue, prefix, longStr);
                    }
                    else */
                    //{
                    
                    if (pHashArray == nullptr) {
                        //메모리 할당 실패
                        bIsPrefix = CheckPrefix(hashValue, prefix, longStr);
                    }
                    else
                        bIsPrefix = CheckPrefix(pHashArray, size, index, hashValue, prefix, longStr);
                    //}

                    index++;

                    if (bIsPrefix == true)
                    {
                        answer = false;
                        break;
                    }
                }


                //해시 저정소 클리어
                memset(pHashArray, 0, sizeof(stHash) * maxSize);
            }

        }
    }

    if (pHashArray != nullptr)
        delete[] pHashArray;

    return answer;
}

bool MakeHash(int& out, string str, int length) {
    bool bResult = false;
    int lengthOfStr = str.size();
    int sum = 0;
    int lengthOfprefix = length;
    string subString;

    //문자열 길이가 0이면 만들필요없다.
    if (lengthOfStr == 0)
        goto lb_return;

    if (lengthOfprefix == 0)
        lengthOfprefix = lengthOfStr;

    //문자열 길이보다 클 수 없다.
    if (lengthOfStr < lengthOfprefix)
        goto lb_return;

    std::hash<string> hash_string;
    subString = str.substr(0, lengthOfprefix);   //프리픽스만큼 자르기

    sum = hash_string(subString);

    bResult = true;
    out = sum;

lb_return:
    return bResult;
}

bool CheckPrefix(size_t hashValue, string prefix, string number) {
    bool bResult = false;
    int numberHash = 0;
    int lengthOfPrefix = prefix.size();
    int lengthOfNumber = number.size();

    //접두어 길이가 0이면 검사할 필요가 없다.
    if (lengthOfPrefix == 0)
        goto lb_return;

    //접두어 길이가 더 길 수 없다.
    if (lengthOfNumber < lengthOfPrefix)
        goto lb_return;

    //해쉬 생성 실패
    MakeHash(numberHash, number, lengthOfPrefix);

    if (numberHash == hashValue) {
        //두값이 같다면 상세 검사
        int comp = number.compare(0, prefix.size(), prefix);
        if (comp == 0) {
            bResult = true;
        }
    }

lb_return:
    return bResult;
}

bool CheckPrefix(stHash* pArray, size_t size, size_t index, size_t hashValue, string prefix, string longNumber)
{
    bool bResult = false;
    int numberHash = 0;
    int lengthOfPrefix = prefix.size();
    int lengthOfNumber = longNumber.size();

    if (pArray == nullptr)
        goto lb_return;

    if (size <= index)
        goto lb_return;

    //접두어 길이가 0이면 검사할 필요가 없다.
    if (lengthOfPrefix == 0)
        goto lb_return;

    //접두어 길이가 더 길 수 없다.
    if (lengthOfNumber < lengthOfPrefix)
        goto lb_return;

    if (pArray[index].hashValue == 0) {
        MakeHash(numberHash, longNumber, lengthOfPrefix);
        pArray[index].hashValue = numberHash;
        pArray[index].hashKey = lengthOfPrefix;
    }
    else {
        numberHash = pArray[index].hashValue;
    }

    if (numberHash == hashValue) {
        //두값이 같다면 상세 검사
        int comp = longNumber.compare(0, prefix.size(), prefix);
        if (comp == 0) {
            bResult = true;
        }
    }

lb_return:
    return bResult;
}

bool MakePhoneBookByLength(size_t& outMaxSize, vector<string> phoneBook[], vector<string> src) {

    bool bResult = false;
    size_t maxSize = 0;
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

    for (int i = 0; i < MAX_PHONE_LENGTH; i++) {
        size_t cur = phoneBook[i].size();
        maxSize = cur > maxSize ? cur : maxSize;
    }

    outMaxSize = maxSize;
    bResult = true;

lb_result:
    return bResult;
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