#include <iostream>
#include <deque>
#include <string>

using namespace std;

int N;
string minValue = "9999999999";
string maxValue ="0";
deque<char> inEqualAry;
int visit[10] = {0,};

void findInEqualCase(int currentLevel, int currentNumber, string res)
{
    if(N == currentLevel)
    {
        if(res > maxValue) { maxValue = res; }
        if(res < minValue) { minValue = res; }
        return;
    }

    int recursiveIndex;
    if (inEqualAry[currentLevel] == '<'){
        for(recursiveIndex = currentNumber ; recursiveIndex< 10 ; recursiveIndex++)
        {
            if(!visit[recursiveIndex])
            {
                visit[recursiveIndex]=1;
                findInEqualCase(currentLevel+1,recursiveIndex,res+to_string(recursiveIndex));
                visit[recursiveIndex]=0;
            }
        }
    }
    else if (inEqualAry[currentLevel] == '>'){
        for(recursiveIndex = currentNumber ; recursiveIndex>= 0 ; recursiveIndex--)
        {
            if(!visit[recursiveIndex])
            {
                visit[recursiveIndex]=1;
                findInEqualCase(currentLevel+1,recursiveIndex,res+to_string(recursiveIndex));
                visit[recursiveIndex]=0;
            }
        }
    }
}


int main() {
    cin>>N;

    int inputIndex;
    for(inputIndex =0 ; inputIndex<N ; inputIndex++)
    {
        char temp;
        cin>>temp;
        inEqualAry.push_back(temp);
    }

    int dfsLoopIndex
    for(dfsLoopIndex=0; dfsLoopIndex<10; dfsLoopIndex++){
        visit[dfsLoopIndex]=1;
        findInEqualCase(0, dfsLoopIndex,to_string(dfsLoopIndex));
        visit[dfsLoopIndex]=0;
    }

    cout<<maxValue<<endl;
    cout<<minValue<<endl;
}