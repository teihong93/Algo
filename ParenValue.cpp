#include <iostream>
#include <string>
#include <deque>

using namespace std;

typedef struct _node{
_node(char _type,int _value):type(_type),value(_value){}
char type;
int value;
}node;

deque<node> tokenStack;

int openParenMap(char p)
{
    switch (p) {
        case '(' : return 2;
        case '[' : return 3;
        default  : return 0;
    }
}

int closeParenMap(char p)
{
    switch (p) {
        case ')' : return 2;
        case ']' : return 3;
        default  : return 0;
    }
}

int main()
{
    string input="";
    cin>>input;
    for(int i=0; i<input.length();i++){
        if(openParenMap(input[i])) // if '(' or '['
        {
            tokenStack.push_back(node('p',input[i]));
        }
        else
        {
            if(tokenStack.empty()){cout<<0;return 0;}
            int currentSum=0;
            node currentTop = tokenStack.back();
            if(currentTop.type=='p')
            {
                if(openParenMap(currentTop.value) != closeParenMap(input[i])){cout<<0;return 0;}
                int currentWeight = openParenMap(tokenStack.back().value);
                tokenStack.pop_back();
                tokenStack.push_back(node('v',currentWeight));
            }
            else
            {
                int currentWeight = closeParenMap(input[i]);
                while(!tokenStack.empty() && currentWeight != openParenMap(tokenStack.back().value))
                {
                    if(tokenStack.empty() || tokenStack.back().type=='p'){cout<<0;return 0;}
                    currentSum += currentWeight*tokenStack.back().value;
                    tokenStack.pop_back();
                }
                if(tokenStack.empty()){cout<<0;return 0;}
                else
                {
                    tokenStack.pop_back();
                    tokenStack.push_back(node('v',currentSum));
                }
            }
        }
    }

    int sum=0;
    for(int i=0; i<tokenStack.size();i++)
    {
        if(tokenStack[i].type=='p'){cout<<0;return 0;}
        sum+=tokenStack[i].value;
    }
    cout<<sum;
}
