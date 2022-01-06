/*
    
    �ִ� ���� 2��, ���� ���� limit(param2) ��Ʈ�� �̿���
    �پ��� �������� �����(param1)�� ���� �Ҷ�, �ʿ��� ��Ʈ�� �ּ� ����

    [param]
    ���� ���� int limit
    ����� ������ vector<int> = { }

    [return]
    �ʿ� �ּ� ��Ʈ ����

    [���ѻ���]
    people.size     : 1 ~ 50000
    people.weight   : 40 ~ 240
    boat.limit      : 40 ~ 240
    ��Ʈ�� ���� ������ ������� ������ ���� �׻� ũ��. -> ���� ���ϴ� ���� ����.
*/

/*
    [����]
    people	            limit	return
    [70, 50, 80, 50]	100	    3
    [70, 80, 50]	    100	    3
*/

    /*
        [solution]
        1. ���Ը� ���� ���� ����
        2. (limit - 40)�� �����Դ� 1�δ� �Ѱ��� ��Ʈ �ʿ� (������ �Ѱ�, ����)
        3. �θ� ž�� ������ �ο� �� ���� ���ſ� �ο��� ���� ������ �ο��� ��Ī�Ͽ� ž�� �������� �˻�.
            ->2�� ž�� ����  : ž�� ������ �θ��� ����
            ->2�� ž�� �Ұ���: �� ����� ����
        4. 3�� �ݺ�

    */

    #include <string>
    #include <vector>
    #include <algorithm>
    #include <deque>

    using namespace std;

    #define PEOPLE_WEIGHT_MIN 40
    #define PEOPLE_WEIGHT_MAX 240

    #define BOAT_LIMIT_MIN 40
    #define BOAT_LIMIT_MAX 240

    int GetSingleBoatPeople(deque<int>& out, vector<int>& people, int threshold);

    int solution(vector<int> people, int limit) {
        int answer = 0;
        deque<int> left;
        int boatLimit = limit;
        int weight_Threshold = boatLimit - PEOPLE_WEIGHT_MIN;   //�� ���� �ʰ��ϴ� ������� ������ ��Ʈ�� �Ѱ� ��� �ؾ� �Ѵ�.
        int boatInSingle = 0;
        int boatInDoble = 0;
        int boatInTemp = 0;

        //1. ���� ���� ����
        sort(people.begin(), people.end());
    
        //2. ȥ�� Ÿ���ϴ� ����� �� ���� Ż ���� �ִ� ����� �з�
        boatInSingle = GetSingleBoatPeople(left, people, weight_Threshold);
        

        //3. ���ſ� ������� 
        //for (deque<int>::iterator it = left.begin(); it != left.end();)
        while(left.empty() == false)
        {
            //���� ����� 2���� �ȵǸ� 1���� �¿� �� �ۿ�
            if (left.size() < 2)
            {
                boatInTemp++;
                break;
            }

            int heavy = left.front();
            int light = left.back();
            
            if ( heavy + light <= limit )
            {
                //�θ��� ���� Ż �� �ִ� ���
                boatInDoble++;
                left.pop_back();
                left.pop_front();
            }
            else
            {
                //�Ѹ� �ۿ� ���¿�� ���
                left.pop_front();
                boatInTemp++;
            }
        }

        answer = boatInDoble + boatInSingle + boatInTemp;

        return answer;
    }


int GetSingleBoatPeople(deque<int>& out, vector<int>& people, int threshold)
{
    int countBoatInSingle = 0;

    for (auto& it : people)
    {
        int weight = it;
        if (weight > threshold) break;

        out.push_front(it);  //���ſ� ������� �˻��� �Ŷ� ������ �ִ´�.
    }

    //1�δ� 1���� ��Ʈ�� �ʿ��� ����� (��ġ������ Ȯ������ �����)
    countBoatInSingle = people.size() - out.size();

    return countBoatInSingle;

}



int main()
{
    //return	3
    /*vector<int> people = { 70, 50, 80, 50 }; 
    int limit = 100;*/

    vector<int> people = { 70, 50, 80 };
    int limit = 100;


    int result = solution(people, limit);

    printf("�ʿ� ��Ʈ �� : %d\n", result);

    return 0;
}