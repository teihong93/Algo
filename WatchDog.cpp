#include <cstdio>
#include <deque>

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4
#define VIEW 7

using namespace std;

typedef struct _cctv
{
    _cctv(int _y,int _x,int _type): y(_y),x(_x),type(_type){};
    int y;
    int x;
    int type;
}cctv;

deque<cctv> cctvQueue;
int map[10][10]={0,};
int dx[5]={0,1,0,-1,0};
int dy[5]={0,0,1,0,-1};
int directionAry[4]={RIGHT,DOWN,LEFT,UP};

int N,M;
int minCount=999999;

void initMap()
{
    for(int row=0 ; row<10; row++)
    {
        for(int col =0 ; col<10; col++)
        {
            map[row][col]=-1;
        }
    }
}

void saveMap(int argMap[10][10])
{
    for(int row=0 ; row<=N+1; row++)
    {
        for(int col =0 ; col<=M+1; col++)
        {
            argMap[row][col]=map[row][col];
        }
    }
}

void restoreMap(int argMap[10][10])
{
    for(int row=0 ; row<=N+1; row++)
    {
        for(int col =0 ; col<=M+1; col++)
        {
            map[row][col]=argMap[row][col];
        }
    }
}

void watchSingleDirection(int ypos,int xpos, int direction)
{
    ypos+= dy[direction];
    xpos+= dx[direction];
    
    while (map[ypos][xpos]!=-1) {
        if( (map[ypos][xpos]>=1 && map[ypos][xpos]<=5)|| map[ypos][xpos]== 7 )
        {
            ypos+= dy[direction];
            xpos+= dx[direction];
            continue;
        }
        else if(map[ypos][xpos]==6)
        {
            break;
        }
        map[ypos][xpos]=VIEW;
        ypos+= dy[direction];
        xpos+= dx[direction];
    }
}

int countZero()
{
    int count=0;
    for(int row=1; row<=N; row++)
    {
        for(int col=1; col<=M; col++)
        {
            if(map[row][col]==0)
            {
                count++;
            }
        }
    }
    return count;
}

void watchEveryCase(int currentLevel)//startIsOne
{
    int backupMap[10][10]={0,};
    
    if(currentLevel>cctvQueue.size())
    {
        int currnetCount = countZero();
        if(currnetCount<minCount)
        {
            minCount=currnetCount;
        }
        return;
    }
    
    int currentY = cctvQueue[currentLevel-1].y;
    int currentX = cctvQueue[currentLevel-1].x;
    int currentType = cctvQueue[currentLevel-1].type;
    
    switch (currentType) {
        case 1:
            for(int dir=0 ; dir<4; dir++)
            {
                saveMap(backupMap);
                watchSingleDirection(currentY,currentX,directionAry[dir]);
                watchEveryCase(currentLevel+1);
                restoreMap(backupMap);
            }
            break;
        case 2:
            for(int dir=0 ; dir<2; dir++)
            {
                saveMap(backupMap);
                watchSingleDirection(currentY,currentX,directionAry[(dir)%4]);
                watchSingleDirection(currentY,currentX,directionAry[(dir+2)%4]);
                watchEveryCase(currentLevel+1);
                restoreMap(backupMap);
            }
            break;
        case 3:
            for(int dir=0 ; dir<4; dir++)
            {
                saveMap(backupMap);
                watchSingleDirection(currentY,currentX,directionAry[(dir+3)%4]);
                watchSingleDirection(currentY,currentX,directionAry[(dir)%4]);
                watchEveryCase(currentLevel+1);
                restoreMap(backupMap);
            }
            break;
        case 4:
            for(int dir=0 ; dir<4; dir++)
            {
                saveMap(backupMap);
                watchSingleDirection(currentY,currentX,directionAry[(dir+3)%4]);
                watchSingleDirection(currentY,currentX,directionAry[(dir+2)%4]);
                watchSingleDirection(currentY,currentX,directionAry[(dir)%4]);
                watchEveryCase(currentLevel+1);
                restoreMap(backupMap);
            }
            break;
        case 5:
            saveMap(backupMap);
            watchSingleDirection(currentY,currentX,UP);
            watchSingleDirection(currentY,currentX,LEFT);
            watchSingleDirection(currentY,currentX,RIGHT);
            watchSingleDirection(currentY,currentX,DOWN);
            watchEveryCase(currentLevel+1);
            restoreMap(backupMap);
            break;
    }
    
}

int main()
{
    initMap();
    scanf("%d %d",&N,&M);
    
    for(int row=1; row<=N; row++)
    {
        for(int col=1; col<=M; col++)
        {
            scanf("%d",&map[row][col]);
            if(map[row][col]>=1 && map[row][col]<=5)
            {
                cctvQueue.push_back(cctv(row,col,map[row][col]));
            }
        }
    }
    
    watchEveryCase(1);
    printf("%d",minCount);
    
}
