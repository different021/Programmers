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

    //문자열이 긴것이 앞으로 가도록 정렬
    sort(book.begin(), book.end(), CompareByStringLength);

    vector<string>::iterator it;
    for (it = book.begin(); it != book.end(); it++) {
        string& str = (*it);
        bool bExist = InsertInSet(phoneSet, str, MAX_STRING_SIZE);
        if (bExist == true) {
            //접두어가 존재.
            answer = false;
            break;
        }
    }

    return answer;
}


//문자열의 모든 접두어를 생성하여 set에 넣는다.
/*
* return : 
*   자기 자신을 쿼리하여 존재하면 false (접두어로 존재한다.)
*   없으면 자신이 생성가능한 접두어 중, set에 없는 것을 추가한다.
*/
bool InsertInSet(unordered_set<string>& phone_set, string& str, size_t maxStringSize) {
    //1. 가능한 모든 prefix를 만들어낸다.
    //2. 존재가능한 prefix가 존재하지 않는다면 넣는다.
    //자기 자신은 넣을 필요가 없다.
    bool bResult = false;
    
    string& newString = str;
    size_t strSize = newString.size();

    //최대 길이가 아니면 자기자신이 존재하는지 쿼리
    if (str.size() != maxStringSize)
    {
        bool bExsit = QueryToSet(phone_set, newString);
        if (bExsit == true) {
            bResult = true; //있넹? 그만 찾아도 된다.
            goto lb_result;
        }
    }

    //아닐 경우 서브스트링을 만들어 몽땅 커리
    for (int i = 1; i < strSize; i++) {
        string subString = newString.substr(0, i);
        bool bIsPrefixExsit = QueryToSet(phone_set, subString);
        
        if (bIsPrefixExsit == false)
            phone_set.insert(subString); //없던 접두어는 set에 추가
    }

lb_result:
    return bResult;
}

//return : 파라미터의 문자열이
// 존재하면 true
// 없으면 false
bool QueryToSet(unordered_set<string>& phone_set, string& str) {
    bool bResult = true;
    unordered_set<string>& phoneSet = phone_set;
    string& qryStr = str;

    unordered_set<string>::iterator itr = phoneSet.find(qryStr);
    if (itr != phoneSet.end()) {
        //찾음
    }
    else {
        //못찾음
        bResult = false;
    }
    
    return bResult;
}

bool CompareByStringLength(string str1, string str2) {
    //문자열이 길면 앞으로 간다.
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