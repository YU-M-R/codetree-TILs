#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

/*
n*m크기의 이차원 영역에 방화벽을 설치해서 불을 막아야됨.
1.불은 상하좌우의 인접한 공간으로 퍼짐
2.방화벽을 뚫을 수 없음
3.기존의 방화벽 + 추가로 3개의 방화벽 설치 가능
4.3개의 방화벽을 설치한 뒤 불이 퍼지지 "않는" 영역이 최대일때의 크기를 출력하라
5.불이 있는 자리에 방화벽 불가

불이 있으면 2 방화벽이 있으면 1 빈칸이면 0
n,m이 8까지라서 그냥 다 찾아도 될듯???

풀이
1.일단 방화벽을 설치할 수 있는 자리를 다 찾아놓은 다음에 (백트래킹으로???)
2.찾은 상황마다 bfs로 불이 얼마나 퍼지는지 체크
3.체크하면서 불이 퍼지지 "않는" 영역의 최대 크기를 구하면 될듯
*/



struct Node {
    int row;
    int col;
};

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0, 1, 0, -1 };
int n, m;
int arr[9][9];
int initArr[9][9];
int cnt;
int maxArea = -1;
bool visited[9][9];
queue <Node> q;
vector <Node> possible;
vector <int> selected;

void removeFirewalls() {
    for (int i = 0; i < 3; i++) {
        int row = possible[selected[i]].row;
        int col = possible[selected[i]].col;

        arr[row][col] = 0;
    }
}

void installFirewalls() {
    for (int i = 0; i < 3; i++) {
        int row = possible[selected[i]].row;
        int col = possible[selected[i]].col;

        arr[row][col] = 1;
    }
}
void bfs(int row, int col) {
    q.push({ row,col });
    visited[row][col] = 1;

    while (!q.empty()) {
        Node now = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nextRow = now.row + dr[i];
            int nextCol = now.col + dc[i];

            if (visited[nextRow][nextCol] == true) continue;
            if (nextRow >= n || nextCol >= m || nextRow < 0 || nextCol < 0) continue;
            if (arr[nextRow][nextCol] == 0) {
                visited[nextRow][nextCol] = true;
                arr[nextRow][nextCol] = 2;
                q.push({ nextRow,nextCol });
            }
        }
    }
}

void findArea() {

    // 매번 visited 초기화 해줌
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    // 매번 arr 초기화 해줌
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = initArr[i][j];
        }
    }
    
    cnt = 0;
   
    // 방화벽 설치해줌
    installFirewalls();

    // 방화벽 설치가 끝났으면 각각의 불(값이 2인 영역)들마다 bfs 돌아서 불퍼지게함
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j] == false && arr[i][j] == 2) bfs(i, j);
        }
    }

    // 다 처리했다면 아직까지도 0인 공간을 찾고, 그 최대값을 찾자
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 0) cnt++;
        }
    }

    maxArea = max(maxArea, cnt);
    removeFirewalls();
}

void searchPossible(int idx, int cnt) {
    // 백트래킹으로 possible 벡터의 맨앞부터 경우의 수를 다 찾아서
    // 3개의 방화벽을 설치했을 때마다 영역을 구하면 될듯

    if (cnt == 3) {
        findArea();
        return;
    }

    // 가능한 idx를 넘어가면 return
    if (idx == possible.size()) return;
    selected.push_back(idx);
    searchPossible(idx + 1, cnt + 1);
    selected.pop_back();
    searchPossible(idx + 1, cnt);
}


int main(void) {
    
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            initArr[i][j] = arr[i][j];
            if (arr[i][j] == 0) {
                // 방화벽 설치가 가능한 영역을 벡터로 저장
                possible.push_back({ i,j });
            }
        }
    }
    

    searchPossible(0, 0);

    cout << maxArea;
    return 0;
}