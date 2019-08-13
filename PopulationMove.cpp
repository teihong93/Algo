#include <cstdio>
#include <deque>

using namespace std;

int N;
int L;
int R;

int A[52][52]={0,};
int visit[52][52]={0,};
int dx[4]= {1,-1,0,0};
int dy[4]= {0,0,-1,1};
int UnionExist=false;
int cnt=0;

typedef struct _pos
{
    _pos(int y,int x) : ypos(y),xpos(x) {}
    int xpos;
    int ypos;
}pos;

deque<pos>Q;
deque<int> countAry[2704];//UnionNumber에 해당하는 index에 동맹국 수와 각각의 값 저장


inline int abs(int num ) {return num<0?-num:num;}

void initMapWithMinus()
{
    for(int colum =0 ; colum<=N+1 ; colum++ )
    {
        for(int row =0 ; row <=N+1 ; row++ )
        {
            A[colum][row] = -1;
        }
    }
}

void initVisit()
{
     for(int colum =0 ; colum<=N+1 ; colum++ )
    {
        for(int row =0 ; row <=N+1 ; row++ )
        {
            visit[colum][row] = 0;
        }
    }
    
}

void findUnion(int startY, int startX, int unionNumber)
{
    visit[startY][startX]=unionNumber;
    countAry[unionNumber].push_back(A[startY][startX]);
    Q.push_back( pos(startY,startX) );
    
    while(!Q.empty())
    {
        pos currentElem = Q.front();
        Q.pop_front();

        int currentX= currentElem.xpos;
        int currentY = currentElem.ypos;

        for(int dir =0 ; dir<4; dir++)
        {
            int nextX = currentX + dx[dir];
            int nextY = currentY + dy[dir];

            if( visit[nextY][nextX] == 0 && A[nextY][nextX]!= -1)
            {
                int difference = abs(A[currentY][currentX] -A[nextY][nextX]);
                if(difference>=L && difference<=R)
                {
                    visit[nextY][nextX] = unionNumber;
                    Q.push_back( pos(nextY,nextX) );
                    countAry[unionNumber].push_back(A[nextY][nextX]);
                    UnionExist=true;
                }
            }
        }
    }
    Q.clear();
}

void movePopulation(int unionNumber)
{
    //연합별 인구수 계산
    for( int index = 1; index< unionNumber ; index++)
    {
        int sum=0;
        for(int avgLoop =0 ; avgLoop < countAry[index].size() ;avgLoop++)
        {
            sum += countAry[index][avgLoop];
        }
        sum /= countAry[index].size();
        countAry[index].clear();
        countAry[index].push_back(sum);
    }

    for(int colum =1; colum<=N ; colum++)
    {
        for(int row=1 ; row<=N; row++)
        {
            int currentUnionNo = visit[colum][row];
            A[colum][row] = countAry[currentUnionNo][0];
        }
    }
    for( int index = 1; index< unionNumber ; index++)
    {
        countAry[index].clear();
    }
}


int main()
{
    scanf("%d %d %d",&N, &L, &R);
    initMapWithMinus();

    for(int colum =1; colum<=N ; colum++)
    {
        for(int row=1 ; row<=N; row++)
        {
            scanf("%d",&A[colum][row]);
        }
    }

    for(int maxLoop =0 ; maxLoop <2000 ; maxLoop ++)
    {
        int unionNumber=1;
        UnionExist=false;
        for(int colum =1; colum<=N ; colum++)
        {
            for(int row=1 ; row<=N; row++)
            {
                if(visit[colum][row]==0)
                {
                    findUnion(colum,row,unionNumber++);
                }
            }
        }
        if(UnionExist==false)
        {
            break;
        }
        movePopulation(unionNumber);
        initVisit();
        cnt++;
    }
    printf("%d", cnt);
}