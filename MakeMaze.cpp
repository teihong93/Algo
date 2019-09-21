#include <cstdio>
#include <deque>

using namespace std;

int N;
int minChange=999999;
int maze[52][52]={0,};
int visit[52][52]={0,};
char inputBuffer[50];

int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

typedef struct _node{
    _node(int _y, int _x,int _broken):y(_y),x(_x),broken(_broken){}
    int y;
    int x;
    int broken=0;
}node;

void initMapWithMinus(){
    for(int row = 0; row<=N+1; row++){
        for(int col =0 ; col<=N+1; col++){
            maze[row][col]=-1;
        }
    }
}

void initVisit(){
    for(int row = 1; row<=N; row++){
        for(int col =1 ; col<=N; col++){
            visit[row][col]=minChange;
        }
    }
}

void bfs(int startY,int startX){
    deque<node> q;
    visit[startY][startX]=1;
    q.push_back(node(startY,startX,0));
    
    while(!q.empty()){
        int currentY = q.front().y;
        int currentX = q.front().x;
        int currentBroken = q.front().broken;
        q.pop_front();
        for(int dir=0; dir<4; dir++){
            int nextY= currentY+dy[dir];
            int nextX= currentX+dx[dir];
            
            if(maze[nextY][nextX]!=-1){
                if(maze[nextY][nextX]==0 && visit[nextY][nextX]>currentBroken+1) {
                    q.push_back(node(nextY,nextX,currentBroken+1));
                    visit[nextY][nextX]=currentBroken+1;
                }else if(maze[nextY][nextX]==1 && visit[nextY][nextX]>currentBroken){
                    q.push_back(node(nextY,nextX,currentBroken));
                    visit[nextY][nextX]=currentBroken;
                }
            }
        }
    }
}


int main(){
    scanf("%d",&N);
    initMapWithMinus();
    initVisit();
    for(int row=1 ;row<=N; row++){
        scanf("%s",inputBuffer);
        for(int col=1 ;col<=N ;col++ ){
            maze[row][col] = inputBuffer[col-1]-'0';
        }
    }
    bfs(1,1);
    printf("%d",visit[N][N]);

}

/*
 굉장히 쉬울것같아서 몸풀기용으로 시작한 문제인데 생각보다 고생을 했습니다.
 DFS로 풀어야 한다고 생각했는데, DFS로 풀다 생각해보니 경우의수가 너무나 많아 BFS를 사용해야 하는 문제라고
 판단되어 BFS로 다시 풀기 시작했습니다.
 
 그런데 일반적인 BFS와 다르게 방문처리가 까다롭다고 느껴졌습니다. 이미 방문했던 셀이더라도 더 나은 경우의 수가 있다면
 덮어쓰기 위해, 처음부터 방문 배열을 최악의 케이스로 초기화하고, 더 나은 경우가 있을때만 BFS하도록 했습니다.
 */

