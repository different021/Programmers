/*
    올해의 베스트 앨범
    장르별로 가장 많이 재생된 2곡을 앨범에 담기로 결정

    1. 속한 노래가 많이 재생된 장르부터
    2. 장르 내에서 많이 재생된 순으로
    3. 재생 횟수가 같을 경우 고유번호가 낮은 것 부터

    vector<string> genres, vector<int> plays
    genres[i] : i는 고유번호
    plays[i]  : 고유번호 i의 재생횟수 저장

    genres, plays는 길이가 같다 ( 1 ~ 10000 )
    genres는 100개 미만
    genres에 곡이 1개일 경우 하나만.
    장르별로 재생횟수가 다르다.(장르총합간 같은 재생횟수 없다.)


    [sample]
    genres:
    ["classic", "pop", "classic", "classic", "pop"]	
    
    plays:
    [500, 600, 150, 800, 2500]	
    
    return :
        [4, 1, 3, 0]
*/

//언어도드맵으로 각 장르별 총 플레이 횟수 저장
//

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


struct stSong {
    int id;         //고유번호
    int played;     //플레이 횟수

    stSong() {
        id = -1;
        played = -1;
    }
    stSong(int _id, int _played) {
        id      = _id;
        played  = _played;
    }
};

struct stRecord {
    int totalPlayed = 0;    //총 플레이 횟수
    stSong songs[2];        //1, 2위만 기록    
};


typedef pair<string, stRecord> myData;

bool UpdatePlayedCount(map<string, stRecord>& totalPlayedMap, string genre, int id, int played);
bool UpdateRank(stRecord* pRecord, stSong* pChallenger);
void swapSong(stSong& song1, stSong& song2);
bool UpdateAlbum(vector<int>& out, map<string, stRecord>& src);

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, stRecord> totalPlayedOfGenres;   //장르별 총 플레이 리스트
    size_t genresSize = genres.size();
    size_t playsSzie = plays.size();

    if (genresSize != playsSzie)
    {
        //잘못된 파라미터. 둘은 같아야만 한다.
        //에러처리
    }
    
    //장르별 플레이획수 & 랭킹 업데이트
    for (size_t id = 0; id < genresSize; id++) {
        string genre  = genres.at(id);
        int    played = plays.at(id);
        stSong song(id, played);

        //장르별 총 횟수 합산
        //장르별 1등, 2등 곡 id와 플레이 횟수 기록
        bool bSuccess = UpdatePlayedCount(totalPlayedOfGenres, genre, id, played);
    }
    
    //앨범생성
    UpdateAlbum(answer, totalPlayedOfGenres);

    return answer;
}

bool UpdatePlayedCount(map<string, stRecord>& totalPlayedMap, string genre, int id, int played) {
    bool bResult = false;
    stRecord* pRecord = nullptr;
    stSong song;

    if (genre.compare("") == 0) goto lb_return;
    if (id < 0) goto lb_return;
    if (played < 0) goto lb_return;

    song.id = id;
    song.played = played;

    //장르의 총 플레이횟수 업데이트
    pRecord = &totalPlayedMap[genre];
    pRecord->totalPlayed += played;

    //해당 장르 랭크 업데이트
    bResult = UpdateRank(pRecord, &song);
    if (bResult = false) goto lb_return;
    
    bResult = true;
lb_return:
    return bResult;
}

bool UpdateRank(stRecord* _pRecord, stSong* _pChallenger) {
    bool bResult = false;
    stRecord* pRecord   = _pRecord;
    stSong* pChallenger = _pChallenger;

    if (pRecord == nullptr)
        goto lb_result;
    if (pChallenger == nullptr)
        goto lb_result;

    //새기록과 2위 기록 비교
    if (pRecord->songs[1].played < pChallenger->played) {
        //새 기록이 더 좋을 경우
        pRecord->songs[1].id = pChallenger->id;
        pRecord->songs[1].played = pChallenger->played;

        //1위 기록과 2위 기록 비교
        if (pRecord->songs[1].played > pRecord->songs[0].played) {
            //2위 기록이 더 좋을 경우 스왑
            swapSong(pRecord->songs[1], pRecord->songs[0]);
        }
    }

    bResult = true;

lb_result:
    return bResult;
}

void swapSong(stSong& song1, stSong& song2) {
    stSong temp(song1.id, song1.played);

    song1.id     = song2.id;
    song1.played = song2.played;

    song2.id     = temp.id;
    song2.played = temp.played;
}

bool comp(const myData& a, const myData& b) {
    return (a.second.totalPlayed < b.second.totalPlayed);;
}

bool UpdateAlbum(vector<int>& out, map<string, stRecord>& src) {
    bool bResult = false;

    vector<myData> vec( src.begin(), src.end() );
    sort(vec.begin(), vec.end(), comp);

    for ( auto it : vec) {
        //write in out 
        int id1 = it.second.songs[0].id;
        int id2 = it.second.songs[1].id;
        
        if(id1 < 0)
            out.push_back(id1);

        if (id2 < 0)
            out.push_back(id2);
    }

    bResult = true;
    return bResult;
}


int main()
{
    vector<string> genres{ "classic", "pop", "classic", "classic", "pop" };
    vector<int> plays{ 500, 600, 150, 800, 2500 };
    vector<int> result = solution(genres, plays);

    return 0;
}