#include <string>
#include <vector>
#include <functional>

#define MAX_PHONEBOOK_SIZE 1000000

using namespace std;

//성능 똥망

struct stHASH
{
    size_t index;
    size_t lengthOfPrefix;    //해쉬를 만들때 사용한 프리픽스 길이
    size_t hashValue;
};

typedef vector<stHASH> HASH_TABLE;

bool MakeHash(size_t& out, string str, size_t length = 0);
bool CheckPrefix(vector<string> phone_book, stHASH& _pPrefix, stHASH& _pNumber);
bool MakeHashTable(HASH_TABLE out[], std::vector<string> src);

bool solution(vector<string> phone_book) {
    bool answer = true;
    
    //전제 조건
    //phone_book의 길이는 1 이상 1,000,000 이하
    //각 번호의 길이는 1 ~ 20
    //중복없다

    //방법1 
    //1. 벡터의 전화번호들을 길이에 따라 분류
    //2. 중복이 없으므로 동일 길이를 검사할 필요가 없다.
    //3. 자신보다 긴 길이에 대해서 모두 검사
    //4. 하나라도 걸릴 경우, return false;


    //1. 벡터의 번호들을 길이에 따라 분류
    //20개 배열 준비 -> 문제 각 배열벌로 필연적으로 길이가 다를수 밖에 없다
    HASH_TABLE vPhoneBookByLength[20];

    for (int i = 0; i < 20; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        vPhoneBookByLength[i].reserve(size);
    }

    //각길이로 보낸다.
    bool bResult = MakeHashTable(vPhoneBookByLength, phone_book);


    //3. 자신보다 긴 길이에 대해 검사. 
    for (int i = 0; i < 20; i++)
    {
        if (answer == false) break;

        HASH_TABLE::iterator it;
        if (vPhoneBookByLength[i].size() == 0)
            continue;   //없으면 검사할 필요가 없다.

        for (it = vPhoneBookByLength[i].begin(); it != vPhoneBookByLength[i].end(); it++) {
            if (answer == false) break;

            stHASH pPrefix = *it;
            const string& prefix = phone_book.at(pPrefix.index);

            MakeHash(pPrefix.hashValue, prefix);
            pPrefix.lengthOfPrefix = prefix.size();

            //자신의 다음 대상 부터 차례로 검사
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

    //인덱스 유혀성 검사 -prefix
    if (sizeOfPhoneBook < iIndexOfPrefix)
        goto lb_return;

    //인덱스 유효성 검사 - number
    if (sizeOfPhoneBook < iIndexOfNumber)
        goto lb_return;

    //접두어 길이가 0이면 검사할 필요가 없다.
    if (prefix.size() == 0)
        goto lb_return;

    //접두어 길이가 더 길 수 없다.
    if (number.size() < prefix.size())
        goto lb_return;


    //접두어 해쉬값이 유효한지 검사
    if (pPrefix.lengthOfPrefix != pPrefix.lengthOfPrefix) {
        pPrefix.lengthOfPrefix = prefix.size();
        MakeHash(pPrefix.hashValue, prefix, pPrefix.lengthOfPrefix);
    }

    //긴전화번호의 해쉬값이 유효한지 검사. 유효하지 않으면 재생성
    if (pNumber.lengthOfPrefix != pPrefix.lengthOfPrefix) {
        pNumber.lengthOfPrefix = prefix.size();
        MakeHash(pNumber.hashValue, number, pNumber.lengthOfPrefix);
    }
    
    if (pNumber.hashValue == pPrefix.hashValue) {
        //두값이 같다면 상세 검사
        
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
