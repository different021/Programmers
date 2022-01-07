/*
    섬을 다리로 연결한다.
    섬을 모두 연결하는 최소 비용을 구하라.

    ABC 3개의 섬이 있다고 할때,
    %% A-B가 연결 되고, B-C가 연결 되면, A-C 연결 인정. %%


    [제한 사항]
    -섬의 갯수(n)  : 1 ~ 100
    -cost.size    : ( (n - 1) * n ) / 2 이하 (n = 100 일때, (100 - 1) * 100 / 2 = 99 * 100 / 2 = 49500 )
    
    -임의의 i에 대하여
    cost[i][0], const[i][1] 은 연결되는 두섬의 번호. cost[i][3] 은 건설 비용

    -모든 섬에 다리가 연결가능 한 것은 아니다. A-B, B-C등을 통한 A-C간접 연결 해야 한다.
    -연결이 불가능한 섬은 없다.

    [예시]
    n	costs	                                    return
    4	[[0,1,1],[0,2,2],[1,2,5],[1,3,1],[2,3,8]]	4


    []  : 섬 인덱스
    ()  : 코스트
    -, |: 연결

    [0]-(1)-[1]
     |     / |
    (2) (5) (1)
     | /     |
    [2]-(8)-[3]




    [0,1,1]
    [0,2,2]
    [1,2,5]
    [1,3,1]
    [2,3,8]


    [링크] - 그림 있음
    https://programmers.co.kr/learn/courses/30/lessons/42861
*/


/*
    가장 까다로운 점은
    {0, 1}
    {2, 0}
    같은 경우.
    둘다 0번에 연결 되어 있지만. cost[i][0]을 통해 확신 할 수 없다. 
    
    한 섬에 여러개의 다리를 만들 수 있다. 
*/

/*
    배열을 전부 돌면서 
    [i][0] < [i][1] 이 보증되도록 바꾼다.
    
    


*/

#include <string>
#include <vector>

using namespace std;

#define MAX_ISLAND_NUMBER 100

struct  cBridge
{
    int index[2];   //연결된 두 섬의 인덱스
    int cost;

    
};

struct cIsland
{
    int index;
    vector<cBridge> link;
    int group;
};

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int numOfIsland = n;
    

    return answer;
}


