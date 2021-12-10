//결과
//성능4 실패

#include <string>
#include <vector>
#include <functional>

#define MAX_PHONEBOOK_SIZE 1000000

using namespace std;


bool MakeHash(int& out, string str, int length = 0);
bool CheckPrefix(int hashValue, string prefix, string longNumber);
bool MakePhoneBookByLength(std::vector<string> out[], std::vector<string> src);

bool solution(vector<string> phone_book) {
    bool answer = true;

    vector<string> vHashTable[20];

    for (int i = 0; i < 20; i++) {
        int size = 10 ^ i;
        if (size > MAX_PHONEBOOK_SIZE) size = MAX_PHONEBOOK_SIZE;
        vHashTable[i].reserve(size);
    }

    //각길이로 보낸다.
    bool bResult = MakePhoneBookByLength(vHashTable, phone_book);


    //3. 자신보다 긴 길이에 대해 검사. 
    for (int i = 0; i < 20; i++)
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

            //자신의 다음 대상 부터 차례로 검사
            for (int j = i + 1; j < 20; j++) {
                if (answer == false) break;
                vector<string>::iterator itLongString;
                for (itLongString = vHashTable[j].begin(); itLongString != vHashTable[j].end(); itLongString++) {
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
    string subString;
    //char* pStr = nullptr;


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

    /* pStr = (char*)str.c_str();
     for (int i = 0; i < lengthOfprefix; i++) {

         sum += pStr[i];
     }
    */

    bResult = true;
    out = sum;

lb_return:
    return bResult;
}

bool CheckPrefix(int hashValue, string prefix, string number) {
    bool bResult = false;
    int numberHash = 0;
    int lengthOfPrefix = prefix.size();
    int lengthOfNumber = number.size();
    //char* pPrefix = nullptr;
    //char* pNumber = nullptr;

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