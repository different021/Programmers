/*
    �׵θ��� ����, ���ΰ� ��������� ĥ���� ���ڸ�� ī��
    ����� �ܺθ� ������ 1�ٷ� ���ΰ� �ִ� �����̴�.

    ����, ����� ������ ���ڰ� �־�����, ī���� ���μ��� ũ�⸦ �����Ͻÿ�

    [param]
    brown  : int
    yellow : int

    [���ѻ���]
    brown : 8 ~ 5000
    yellow: 1 ~ 2000000
    ���� >= ����

    ��1) 
    [B][B][B][B][B][B]
    [B][Y][Y][Y][Y][B]
    [B][B][B][B][B][B]

    [�Ķ����]
    brown  : 14
    yellow : 4

    [return]
    ���� : 6
    ���� : 3

    ��2)
    [B][B][B][B]
    [B][Y][Y][B]
    [B][Y][Y][B]
    [B][B][B][B]

    [�Ķ����]
    brown  : 12
    yellow : 4

    [return]
    ���� : 4
    ���� : 4
*/

/*
    ���δ� �����.
    �ܺδ� ����

    ������ (yWidth + 2) * 2 + yHeight * 2 = (yWidth + 2 + yHiehgt) * 2
    ������� ũ�⿡ ���� ���Ѵ�.
    ������� ���̿� ���� ���ΰ� ��������.

    (����)            (1���� ���ʴ�� ����)
    yT = yWidth * yHeight
    yW = yTotal / yHeight
    

    [����] 
    bTotal = (yWidth + 2 + yHeight) * 2
    bTotal = (yTotal/yHeight + 2 + yHeight) * 2

    [solution]
    1. ����� ���̸� 1���� ���ʷ� ���
    2. ������� ���̷� ���������� ������ continue
    3. ������ ������� ������ �����ϸ� break;
    ���̸� �ϳ��� �������� �ݺ�

*/

#include <string>
#include <vector>

using namespace std;

#define BROWN_MAX   5000
#define YELLOW_MAX  2000000

/**
* @details brown�� yellow�� ���ٷ� ���ΰ� �ִ�. �߾��� ����, ����� ���� ���簢���� ����, ���� ũ�⸦ ���Ѵ�.
* @param[in] brown ���� �簢���� ����(������� �ܰ��� 1�ٷ� �ѷ� �ΰ� �ִ� ���)
* @param[in] yellow ����� �簢�� ����
* @retrun vector<int>
*/
vector<int> solution(int _brown, int _yellow) {
    vector<int> answer;
    int yellow = _yellow;
    int brown = _brown;
    int tatal = brown + yellow;
    int yHeight = 0;

    while (true)
    {
        yHeight++;

        //���ѷ��� ����
        if (yHeight > YELLOW_MAX)
        {
            //����ó��
            //���� ã�� ����.
            break;
        }

        //2. ���̷� ������ �������� ������ skip
        if ((yellow % yHeight) != 0) continue;

        //������ �������� �ʺ� ���
        int yWidth = static_cast<int>(yellow / yHeight);

        int brownTotal = (yWidth + 2 + yHeight) * 2;
        if (brownTotal == brown)
        {
            //ã��
            int width = yWidth + 2;
            int height = yHeight + 2;
            answer.push_back( width );
            answer.push_back( height );
            
            break;
        }
    }

    return answer;
}

int main()
{

    //[4, 3]
    int brown = 10;
    int yellow = 2;
    //8	    1[3, 3]
    //24	24[8, 6]

    vector<int> result = solution(10, 2);

    for (auto& it : result)
    {
        printf("%d \n", it);
    }

    return 0;
}