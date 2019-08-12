#include <cstdio>

using namespace std;

int linkAry[21][21]={0,};
int visit[21][21]={0,};
int team[21]={0,};

int N=0;
int minimumSum=999999;

const int abs(int n) { return n<0?-n:n; }

void divideIntoTwoGroup(int maxLevel, int currentLevel,int parent)
{
    if(maxLevel==currentLevel)//then, calulate current Sum
    {
        int yPosLoop=0;
        int xPosLoop=0;
        int currentSumStart=0;
        int currentSumLink=0;

        for(yPosLoop=1; yPosLoop<=N; yPosLoop++)
        {
            for(int xPosLoop=1 ; xPosLoop<=N ;xPosLoop++)
            {
                if((team[yPosLoop]==1) && (team[xPosLoop]==1))
                {
                    currentSumStart+=linkAry[yPosLoop][xPosLoop];
                }
                else if((team[yPosLoop]==0) && (team[xPosLoop]==0))
                {
                    currentSumLink+=linkAry[yPosLoop][xPosLoop];
                }
            }
        }

        int currentDirrerence = abs( (currentSumStart-currentSumLink) );

        if(currentDirrerence<minimumSum)
        {
            minimumSum=currentDirrerence;
        }
        
    }

    if(currentLevel < maxLevel)
    {   
        int recursiveLoop=0;
        for(recursiveLoop=parent+1;recursiveLoop<=N;recursiveLoop++)
        {
            if(team[recursiveLoop]==0)
            {
                team[recursiveLoop]=1;
                divideIntoTwoGroup(maxLevel,currentLevel+1,recursiveLoop);
                team[recursiveLoop]=0;
            }
        }
    }
}

int main()
{
    scanf("%d",&N);
    
    int yPosLoop=0;
    int xPosLoop=0;

    for(yPosLoop=1; yPosLoop<=N; yPosLoop++)
    {
        for(xPosLoop=1; xPosLoop<=N; xPosLoop++)
        {
            scanf("%d ",&linkAry[yPosLoop][xPosLoop]);
        }
    }

    divideIntoTwoGroup(N/2,0,0);
    printf("%d",minimumSum);

}