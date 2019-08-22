#include <cstdio>

using namespace std;

int N;
int MAX_VALUE=0;
int map[22][22]={0,};


void initMapWihtMinus()
{
    for(int row = 0; row<=N+1; row++)
    {
        for(int col = 0; col<=N+1; col++)
        {
            map[row][col]=-1;
        }
    }
}

void searchUpToDown()
{
    for(int col = 1; col<=N; col++)
    {
        int preValue =0;
        int preRow=0;
        for(int row = 1; row<=N; row++)
        {
            if(map[row][col]!=0)
            {
                if(preValue == map[row][col])
                {
                    map[row][col]*=2;
                    map[preRow][col]=0;
                    preValue=0;
                    preRow=0;
                }
                else
                {
                    preValue =map[row][col];
                    preRow=row;
                }
            }
        }
    }
}

void searchDownToUp()
{
    for(int col = 1; col<=N; col++)
    {
        int preValue =0;
        int preRow=0;
        for(int row = N; row>=1; row--)
        {
            if(map[row][col]!=0)
            {
                if(preValue == map[row][col])
                {
                    map[row][col]*=2;
                    map[preRow][col]=0;
                    preValue=0;
                    preRow=0;
                }
                else
                {
                    preValue =map[row][col];
                    preRow=row;
                }
            }
        }
    }
}

void searchLeftToRight()
{
    for(int row = 1; row<=N; row++)
    {
        int preValue =0;
        int preCol=0;
        for(int col = 1; col<=N; col++)
        {
            if(map[row][col]!=0)
            {
                if(preValue == map[row][col])
                {
                    map[row][col]*=2;
                    map[row][preCol]=0;
                    preValue=0;
                    preCol=0;
                }
                else
                {
                    preValue =map[row][col];
                    preCol=col;
                }
            }
        }
    }
}

void searchRightToLeft()
{
    for(int row = 1; row<=N; row++)
    {
        int preValue =0;
        int preCol=0;
        for(int col = N; col>=1; col--)
        {
            if(map[row][col]!=0)
            {
                if(preValue == map[row][col])
                {
                    map[row][col]*=2;
                    map[row][preCol]=0;
                    preValue=0;
                    preCol=0;
                }
                else
                {
                    preValue =map[row][col];
                    preCol=col;
                }
            }
        }
    }
}

void moveUp()
{
    for(int col = 1; col<=N; col++)
    {
        for(int row = 1; row<=N; row++)
        {
            int currentRow=row;
            int currentCol=col;
            while (map[currentRow-1][currentCol]==0)
            {
                map[currentRow-1][col]=map[currentRow][currentCol];
                map[currentRow][currentCol]=0;
                currentRow--;
            }
        }
    }
}

void moveDown()
{
    for(int col = 1; col<=N; col++)
    {
        for(int row = N; row>0; row--)
        {
            int currentRow=row;
            int currentCol=col;
            while (map[currentRow+1][currentCol]==0)
            {
                map[currentRow+1][col]=map[currentRow][currentCol];
                map[currentRow][currentCol]=0;
                currentRow++;
            }
        }
    }
}

void moveLeft()
{
    for(int row = 1; row<=N; row++)
    {
        for(int col = 1; col<=N; col++)
        {
            int currentRow=row;
            int currentCol=col;
            while (map[currentRow][currentCol-1]==0)
            {
                map[row][currentCol-1]=map[currentRow][currentCol];
                map[currentRow][currentCol]=0;
                currentCol--;
            }
        }
    }
}

void moveRight()
{
    for(int row = 1; row<=N; row++)
    {
        for(int col = N; col>=1; col--)
        {
            int currentRow=row;
            int currentCol=col;
            while (map[currentRow][currentCol+1]==0)
            {
                map[row][currentCol+1]=map[currentRow][currentCol];
                map[currentRow][currentCol]=0;
                currentCol++;
            }
        }
    }
}

void saveMap(int _map[22][22])
{
    for(int row = 1; row<=N; row++)
    {
        for(int col = 1; col<=N; col++)
        {
            _map[row][col]=map[row][col];
        }
    }
}

void restoreMap(int _map[22][22])
{
    for(int row = 1; row<=N; row++)
    {
        for(int col = 1; col<=N; col++)
        {
            map[row][col]=_map[row][col];
        }
    }
}

int findMaxValue()
{
    int currentMax=0;
    for(int row = 1; row<=N; row++)
    {
        for(int col = 1; col<=N; col++)
        {
            if(map[row][col]>currentMax)
            {
                currentMax=map[row][col];
            }
        }
    }
    return currentMax;
}

void (*direcFunction[4])()={moveUp,moveRight,moveLeft,moveDown};
void (*searchFuntion[4])()={searchUpToDown,searchRightToLeft,searchLeftToRight,searchDownToUp};

void runGame(int currentLevel)
{
    int backupMap[22][22]={0,};
    //printMap();
    
    if(currentLevel==5)
    {
        int cMax= findMaxValue();
        if(cMax>MAX_VALUE)
        {
            MAX_VALUE=cMax;
            //printMap();
        }
        return;
    }
    
    for(int dir=0; dir<4; dir++)
    {
        saveMap(backupMap);
        searchFuntion[dir]();
        direcFunction[dir]();
        runGame(currentLevel+1);
        restoreMap(backupMap);
    }
}


int main()
{
    scanf("%d ",&N);
    
    initMapWihtMinus();
    
    for(int row = 1; row<=N; row++)
    {
            for(int col = 1; col<=N; col++)
            {
                scanf("%d ",&map[row][col]);
            }
    }
    runGame(0);
    printf("%d",MAX_VALUE);
    
}
