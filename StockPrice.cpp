/*
  히스토그램이나, 빗물 문제처럼 stack 을 이용하여 n 안에 답을 찾는 문제라고
  판단하고 진행했다. 빗물문제와 유사(?) 한 방법으로 풀면 되는데
  아주쉽게 보고 접근했는데 생각보다 코드가 지저분한듯. 더 효율적으로 푼 사람이 많다.
  스택에 (시간,그당시 값) 을 저장하여 만일 이번에 넣을 값이 stack 의 top 보다 크다면
  스택에 바로 넣어주고, 이번에 넣을 값이 stack 의 top 보다 작다면 stack을 pop 해가면서
  자신보다 작은 값이 나올때 까지 answer array 에 (현재시간- 그당시시간)을 기록한다. 
  주식가격의 마지막에 도달하면 스택에 남은 값들은 모두 마지막 원소보다 작은 값이므로
  전부 pop 하면서 answer array 에(마지막시간-그당시시간)을 기록한다.
 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class node{
public:
  node(int _index, int _value): index(_index),value(_value) {};
  int index;
  int value;
};

bool isEmpty(vector<node>& stack){
    return stack.size() == 1? true : false;
}

vector<node> nodeStack;

vector<int> solution(vector<int> prices) {
    nodeStack.push_back(node(-1,-1));
    vector<int> answer;

    int index=0;
    int pricesLength = prices.size();
    answer.assign(pricesLength,0);

    for(index=0; index < pricesLength; index++){
        int currentPrice = prices[index];
        int stacktop = nodeStack.back().value;
 
		if(currentPrice > stacktop){
            nodeStack.push_back(node(index,currentPrice));
        } else {
            while(stacktop > currentPrice && !isEmpty(nodeStack)){
                answer[nodeStack.back().index] = index - nodeStack.back().index;
                nodeStack.pop_back();
                stacktop = nodeStack.back().value;
            } 
            nodeStack.push_back(node(index,currentPrice));
        }
    }

    int lastStackIndex = nodeStack.back().index;
    
	while(!isEmpty(nodeStack)){
        answer[nodeStack.back().index] = lastStackIndex - nodeStack.back().index;
        nodeStack.pop_back();
    }

    return answer;
}
