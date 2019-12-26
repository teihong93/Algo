/*
  간단한 시뮬레이셔 문제다.
  풀면서 약간 cpu 스케줄링때 기억이 새록새록했다....
  풀이는 간단하다. 현재 총 무게 + 새 트럭의 무게가 하중을 넘지
  않는다면 runQueue 에 트럭을 하나 넣고 시간을 1초 보낸다.
  만일 무게의 합이 하중을 넘는다면 트럭을 보내지 않고 시간만 흐른다.
  마지막 트럭까지 다리에 올라왔다면, 그 트럭이 다리 끝에 도달할때 까지
  시간을 흘려보낸다.
 */

#include <string>
#include <vector>
#include <deque>
#include <iostream>

using namespace std;

class truck{
public:
    truck(int _weight, int _dist) : weight(_weight),dist(_dist){};
    int weight;
    int dist;
};

deque<truck> runQueue;
int timer;

void timeTick(deque<truck> &rq){
    int index = 0;
    for(index = 0 ; index < rq.size(); index++){
        rq[index].dist++;
    }
    timer++;
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int totalWeight = 0;

    int queueIndex = 0;
    int queueLength = truck_weights.size();
    for(queueIndex = 0 ; queueIndex < queueLength ; queueIndex++){
        int currentWeight = truck_weights[queueIndex];
        if(totalWeight + currentWeight <= weight){
            runQueue.push_back(truck(currentWeight,0));
            totalWeight += currentWeight;
        } else {
            queueIndex--;
        }
        timeTick(runQueue);
        if(runQueue.front().dist >= bridge_length){
            totalWeight -= runQueue.front().weight;
            runQueue.pop_front();
        }     
    }

    while(!runQueue.empty()){
        if(runQueue.front().dist >= bridge_length){
            totalWeight -= runQueue.front().weight;
            runQueue.pop_front();
        }  
        timeTick(runQueue);
    }

    return timer;
}

