/*
    ������ ����Ʈ �ٹ�
    �帣���� ���� ���� ����� 2���� �ٹ��� ���� ����

    1. ���� �뷡�� ���� ����� �帣����
    2. �帣 ������ ���� ����� ������
    3. ��� Ƚ���� ���� ��� ������ȣ�� ���� �� ����

    vector<string> genres, vector<int> plays
    genres[i] : i�� ������ȣ
    plays[i]  : ������ȣ i�� ���Ƚ�� ����

    genres, plays�� ���̰� ���� ( 1 ~ 10000 )
    genres�� 100�� �̸�
    genres�� ���� 1���� ��� �ϳ���.
    �帣���� ���Ƚ���� �ٸ���.(�帣���հ� ���� ���Ƚ�� ����.)


    [sample]
    genres:
    ["classic", "pop", "classic", "classic", "pop"]	
    
    plays:
    [500, 600, 150, 800, 2500]	
    
    return :
        [4, 1, 3, 0]
*/

//��������� �� �帣�� �� �÷��� Ƚ�� ����
//

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


struct stSong {
    int id;         //������ȣ
    int played;     //�÷��� Ƚ��

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
    int totalPlayed = 0;    //�� �÷��� Ƚ��
    stSong songs[2];        //1, 2���� ���    
};


typedef pair<string, stRecord> myData;

bool UpdatePlayedCount(map<string, stRecord>& totalPlayedMap, string genre, int id, int played);
bool UpdateRank(stRecord* pRecord, stSong* pChallenger);
void swapSong(stSong& song1, stSong& song2);
bool UpdateAlbum(vector<int>& out, map<string, stRecord>& src);

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, stRecord> totalPlayedOfGenres;   //�帣�� �� �÷��� ����Ʈ
    size_t genresSize = genres.size();
    size_t playsSzie = plays.size();

    if (genresSize != playsSzie)
    {
        //�߸��� �Ķ����. ���� ���ƾ߸� �Ѵ�.
        //����ó��
    }
    
    //�帣�� �÷���ȹ�� & ��ŷ ������Ʈ
    for (size_t id = 0; id < genresSize; id++) {
        string genre  = genres.at(id);
        int    played = plays.at(id);
        stSong song(id, played);

        //�帣�� �� Ƚ�� �ջ�
        //�帣�� 1��, 2�� �� id�� �÷��� Ƚ�� ���
        bool bSuccess = UpdatePlayedCount(totalPlayedOfGenres, genre, id, played);
    }
    
    //�ٹ�����
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

    //�帣�� �� �÷���Ƚ�� ������Ʈ
    pRecord = &totalPlayedMap[genre];
    pRecord->totalPlayed += played;

    //�ش� �帣 ��ũ ������Ʈ
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

    //����ϰ� 2�� ��� ��
    if (pRecord->songs[1].played < pChallenger->played) {
        //�� ����� �� ���� ���
        pRecord->songs[1].id = pChallenger->id;
        pRecord->songs[1].played = pChallenger->played;

        //1�� ��ϰ� 2�� ��� ��
        if (pRecord->songs[1].played > pRecord->songs[0].played) {
            //2�� ����� �� ���� ��� ����
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