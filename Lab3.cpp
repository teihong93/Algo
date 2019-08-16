#include <cstdio>
#include <deque>
#include <cstring>

using namespace std;

int N,M;

typedef struct _pos
{
    _pos(int _y, int _x,int _time): y(_y),x(_x),time(_time) {}
    int y;
    int x;
    int time;
}pos;

deque<pos> virusQ;
int visitQ[10]={0,};
int minSpreadTime = 99999;
int isPossible = 0;
int targetCount=0;;

int map[52][52]={0,};
int visitMap[52][52]={0,};

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

void initMapWithWall()
{
    for(int row=0 ; row<=N+1 ; row++)
    {
        for(int col=0 ; col<=N+1 ; col++)
        {
            map[row][col]=1;
        }
    }
}

int spreadVirus(deque<int> caseQueue)
{
    deque<pos> bfsQueue;
    int infectCount=0;
    
    for(int index = 0 ; index<caseQueue.size() ; index++)
    {
        int currentIndex= caseQueue[index];
        int currentY = virusQ[ currentIndex ].y;
        int currentX = virusQ[ currentIndex ].x;
        bfsQueue.push_back(pos(currentY,currentX,1));
        visitMap[currentY][currentX] =1;
    }
    
    while(!bfsQueue.empty())
    {
        
        if(infectCount == targetCount) break;
        
        int currentY= bfsQueue.front().y;
        int currentX= bfsQueue.front().x;
        int currnetTime = bfsQueue.front().time;
        bfsQueue.pop_front();
        
        if(currnetTime>=minSpreadTime)
        {
            memset(visitMap,0, sizeof(visitMap));
            return currnetTime;
        }
        
        visitMap[currentY][currentX]=currnetTime;
        
        for(int dir=0; dir<4; dir++)
        {
            int nextY= currentY+dy[dir];
            int nextX= currentX+dx[dir];
            
            if(map[nextY][nextX]==0 && visitMap[nextY][nextX]==0){
                visitMap[nextY][nextX]=currnetTime;
                infectCount++;
                bfsQueue.push_back(pos(nextY,nextX,currnetTime+1));
            }
            else if(map[nextY][nextX]==2 && visitMap[nextY][nextX]==0){
                visitMap[nextY][nextX]=currnetTime;
                bfsQueue.push_back(pos(nextY,nextX,currnetTime+1));
            }
        }
    }
    
    int maxTime=0;
    for(int row=1 ; row<=N ; row++)
    {
        for(int col=1 ; col<=N ; col++)
        {
            if(visitMap[row][col]>maxTime)
            {
                maxTime= visitMap[row][col];
            }
        }
    }
    
    memset(visitMap,0, sizeof(visitMap));
    
    if(infectCount == targetCount)
    {
        return maxTime;
    }
    return -1;
}



/* Do <Q.length C M> and BFS */
void findCases(int currentLevel,int startindex)
{
    
    if(currentLevel == M)
    {
        
        //find CurrentCase and Push to BFS Target
        deque<int> caseQueue;
        for(int index =0 ; index<virusQ.size(); index++)
        {
            if(visitQ[index] == 1)
            {
                caseQueue.push_back(index);
            }
        }
        
        int currentSpreadTime = spreadVirus(caseQueue);
        
        if(currentSpreadTime!= -1 &&
          (currentSpreadTime < minSpreadTime)){
            minSpreadTime = currentSpreadTime;
            isPossible =1;
        }

        return;
    }
    
 
    for(int recursive = startindex ; recursive< virusQ.size(); recursive++)
    {
        if(visitQ[recursive]==0)
        {
            visitQ[recursive]=1;
            findCases(currentLevel+1,recursive);
            visitQ[recursive]=0;
        }
    }
}

int main()
{
    scanf("%d %d", &N,&M);
    initMapWithWall();
    
    for(int row=1 ; row<=N ; row++)
    {
        for(int col=1 ; col<=N ; col++)
        {
            scanf("%d ", &map[row][col]);
            if(map[row][col]==2)
            {
                virusQ.push_back(pos(row,col,1));
            }
            else if( map[row][col]==0 )
            {
                targetCount++;
            }
        }
    }
    
    if(targetCount!=0){
        findCases(0,0);
    }else{
        isPossible =1;
        minSpreadTime =0;
    }
    isPossible?printf("%d ", minSpreadTime):printf("-1");
}
