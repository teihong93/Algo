#include <cstdio>

int M,N,D;
int map[16][15]={0,};
int backupMap[15][15]={0,};
const int MAX_ARCHER = 3;
const int SEARCHED = 4;
const int INITPOS = 9999;
int killed =0 ;

inline int abs(int a) { return a<0?-a:a; }

void saveMap()
{
    for(int row = 0  ; row<N ; row++ )
    {
        for(int col =0 ; col < M; col++)
        {
            backupMap[row][col]= map[row][col];
        }
    }
}

void restoreMap()
{
    for(int row = 0  ; row<N ; row++ )
    {
        for(int col =0 ; col < M; col++)
        {
            map[row][col]= backupMap[row][col];
        }
    }
}

void search(int ypos,int xpos)
{
    int targetY=INITPOS;
    int targetX=INITPOS;
    int currentMinDist =INITPOS;
    
    for(int col =0 ; col < M; col++)
    {
        for(int row = N-1  ; row>=0 ; row-- )
        {
            if(map[row][col]==1 || map[row][col] ==SEARCHED)
            {
                int dist = abs(ypos-row)+abs(xpos-col);
                if(dist <= D && dist<currentMinDist)
                {
                    targetY=row;
                    targetX=col;
                    currentMinDist=dist;
                }
            }
        }
    }
    if(targetX!= INITPOS && targetY!=INITPOS)
    {
        map[targetY][targetX]=SEARCHED;
    }
}

void destroy()
{
    for(int row = 0  ; row<N ; row++ )
    {
        for(int col =0 ; col < M; col++)
        {
            if(map[row][col]==SEARCHED)
            {
                map[row][col]= 0;
                killed++;
            }
        }
    }
}

void moveEnemy()
{
    for(int row = N-2  ; row>=0 ; row-- )
    {
        for(int col =0 ; col < M; col++)
        {
            map[row+1][col]=map[row][col];
        }
    }
    for(int col =0 ; col < M; col++)
    {
        map[0][col]=0;
    }
}

int isDone()
{
    for(int row = 0  ; row<N ; row++ )
    {
        for(int col =0 ; col < M; col++)
        {
            if(map[row][col]==1)
            {
                return false;
            }
        }
    }
    return true;
}

void archerCase(int currentLevel,int recursiveStart)
{
    if(currentLevel==MAX_ARCHER)
    {
        int previousKill = killed;
        killed=0;
        
        saveMap();
        while(!isDone())
        {
            for(int archerNumber =0 ; archerNumber<M; archerNumber++)
            {
                if(map[N][archerNumber]==1)
                {
                    search(N, archerNumber);
                }
            }
            destroy();
            moveEnemy();
        }
        restoreMap();
        
        if(previousKill>killed)
        {
            killed=previousKill;
        }
    }
    
    for(int recursiveIndex = recursiveStart; recursiveIndex<M; recursiveIndex++)
    {
        if(map[N][recursiveIndex]==0)
        {
            map[N][recursiveIndex]=1;
            archerCase(currentLevel+1,recursiveIndex);
            map[N][recursiveIndex]=0;
        }
    }
}


int main()
{
    scanf("%d %d %d",&N,&M,&D);
    for(int row =0; row <N; row++)
    {
        for(int col= 0; col<M; col++)
        {
            scanf("%d ",&map[row][col]);
        }
    }
    
    archerCase(0,0);
    printf("%d",killed);
}
