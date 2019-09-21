/*
 * 2017 카카오 1차 알고리즘테스의 최고 난이도 문제입니다. 
 * 문제 자체가 어렵다기보다는요구사항이 생각보다 까다로운 관계로(시간시간과 끝 시간을 포함한다는점) 
 * 정답률이 낮았으리라 생각됩니다. 
 * 풀이 방식은 list 에 로그 정보를 [시작시간,끝시간] 에 대하여 ms 단위로 저장합니다. 
 * 이는 정수연산으로 만들어 부동소수점 연산의 부정확성을 줄이기 위함입니다. 
 * 그리고 모든 로그의 시작시간부터 끝 시간까지, 1초(정확히는 999ms) 단위로 해당 timeSlice안에 다른 요청이 처리되고 있는지
 * 확인합니다. 다른 요청이 처리되어있는지 알기 위해, 두가지 케이스로 나누었습니다.
 * 1. 현재 timeSlice에 시작하거나 끝난 요청이 있는가 
 * 2. 현재 timeSlice 시작 전에 시작되었고, timeSlice 이후에도 끝나지 않고 있는 요청이 있는가
 * 위 두케이스인 경우count 값을 1씩 증가시켜주었습니다. 
*/

function solution(lines) {
    let timeMap=[];
    let elem;
    for(elem of lines){
        let splitString = elem.split(" ")
        let S = splitString[1];
        let T = splitString[2];
        T=T.slice(0,-1);
        T=Number(T)*1000;
        let splitTime = S.split(":");
        let currnetSec = 
            (Number(splitTime[0])*3600
           +Number(splitTime[1])*60
           +Number(splitTime[2]))*1000;
        timeMap.push([currnetSec-T+1,currnetSec]);
    }
    //timeMap is [startTime,endTime] ms
    let target=0;
    let currentMax=0;
    for(elem of timeMap){
        let timeSlice=0;
        for(timeSlice = elem[0]-999 ; timeSlice<= elem[1]; timeSlice+=999){
            let currentCount=0;
            for(target of timeMap){
                if( (target[0]>=timeSlice && target[0]<=(timeSlice+999))
                    ||(target[1]>=timeSlice && target[1]<=(timeSlice+999))
                  ){
                    currentCount++;
                }else if(timeSlice>=target[0] && (timeSlice+1000)<target[1]){
                    currentCount++;
                }
                if(currentCount>currentMax){
                    currentMax = currentCount;
                }
            }
        }
    }
    return currentMax;
}
