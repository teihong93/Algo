/*
  stack 을 이용해서 해결하는 문제. ()이 레이져인데 닫힌 괄호가 왔을 때
  ) 이 막대기의 끝인지, 아니면 레이져인지를 잘 판단해야 문제를
  해결할 수 있다. 
  해결한 로직은 ( 가 오면 쇠막대기를 한겹 쌓고, ) 가 오면 쇠막대기를 한겹 풀어준다.
  만일 )가 레이져일 경우, 현재 쌓인 쇠막대기의 숫자만큼 answer 에 더해주고, ) 가
  쇠막대기의 끝일 경우 answer에 +1 해주고 쇠막대기를 한겹 풀어준다 (마지막 부분이 떨어지는것이니)
 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<char> stack;
int layerLevel = 0;

int solution(string arrangement) {
    int answer = 0;

    int arragneIndex=0;
    int arrangeLength = arrangement.length();
    for(arragneIndex = 0; arragneIndex < arrangeLength; arragneIndex++)
    {
        char currentArrange = arrangement[arragneIndex];
        if(currentArrange == '('){
            layerLevel++;
        }
        else {
            if(stack.back() == '('){
                layerLevel--;
                answer += layerLevel;
            } else {
                layerLevel--;
                answer++;
            }
        }
        stack.push_back(currentArrange);
    }

    return answer;
}
