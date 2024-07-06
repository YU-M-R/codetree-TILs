#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
N*M 크기의 도로에 자동차가 움직임

-- 움직이는 규칙 --
1. 현재 방향을 기준으로 왼쪽 방향으로 간적이 한번도 없으면 좌회전해서 왼쪽으로 한칸감
2. if 왼쪽 방향이 인도거나(1) 이미 방문한 도로이면 다시 좌회전 하고 시도
3. 전부 확인했는데 안되면 방향은 그대로 한 채 한 칸 후진을 하고 다시 1번 과정 시도
4. 후진조차 못한다면 작동을 멈추고 그대로 종료.

최종적으로 거쳐갔던 도로의 총 면적을 구하시오.

도로는 0 인도는 1로 하고 지나간곳은 2로 하자

dfs로 움직이는데 그때의 현재 위치와 state를 저장하고 움직여야 할듯
현재 state에 따라
0이면 3방향
1이면 0방향
2이면 1방향
3이면 2방향으로 움직이면 됨

*/

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int map[51][51];
struct Node {
    int row;
    int col;
    int dir;
};

Node car;

int n, m;

void dfs(int row, int col, int dir) {

    // 일단 움직인 자리의 배열의 값을 2로 바꿔줘야됨
    map[row][col] = 2;

    // 여기서 조건을 체크해주는데 첫째로 왼쪽방향을 간적이 있는지 체크해서 간적이 없고, 갈 수 있으면 감. 아니면 그냥 회전만함 근데 이걸 4번만 해서 확인 해야함. (4방향 전부 확인하면 stop)
    int nextDir = dir;
    for (int i = 1; i <= 4; i++) {
        nextDir = nextDir - 1;
        if (nextDir == -1) nextDir = 3;

        int nextRow = row + dr[nextDir];
        int nextCol = col + dc[nextDir];

        if (nextRow >= n || nextCol >= m || nextRow < 0 || nextCol < 0) continue;
        // 다음 위치가 갈 수 있는 도로이면 움직이고 다음단계로 넘어간다.
        if (map[nextRow][nextCol] == 0) {
            dfs(nextRow, nextCol, nextDir);
            return;
        }
    }

    // 만약 for문을 다 도는동안 즉 좌회전에서 체크하는동안 안되면, 원래 방향으로 돌아오게 되고, 이러면 후진을 체크한다.
    // 이때는 바라보는 방향은 유치한채 후진함. 후진은 0이면 하는게 아니고 1만 아니면 할 수 있음
    nextDir = dir - 2;
    if (nextDir == -2) nextDir = 2;
    if (nextDir == -1) nextDir = 3;
    int nextRow = row + dr[nextDir];
    int nextCol = col + dc[nextDir];

    if (map[nextRow][nextCol] != 1) {
        dfs(nextRow, nextCol, dir);
    }

    else if (map[nextRow][nextCol] == 1) return;

}


int main() {
    
    cin >> n >> m;
    int x, y, d;
    cin >> x >> y >> d;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            map[i][j] = a;
        }
    }

    dfs(x, y, d);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 2) cnt++;
        }
    }
    cout << cnt;
    return 0;
}