/*
  간단하게 큐로 푸는 문제.
  첫번째 기능이 완료되지 않으면 배포할 수 없기 때문에
  항상 지켜봐야할건 첫번째 기능이 100%를 넘었는지의 여부다.
  전체 progress 배열에 speeds 배열을 더해주고첫번째 값이 100을
  넘었다면, 그 이후에 100이하의 값이 나올때까지 speeds 와 progress
  배열을 popfront 해준다. pop 한 숫자만큼 결과 배열에 넣어주면 solve   
*/

const timerTick = (progress,speeds) => progress.map((e,i) => e+speeds[i]);

function solution(progresses, speeds) {
    var answer = [];
    let currentTaskQueue = progresses;
    let currentSpeeds = speeds;
    while(currentTaskQueue.length > 0 ){
        let currnetCompleteTask = 0;
        currentTaskQueue = timerTick(currentTaskQueue,currentSpeeds);
            if(currentTaskQueue[0] >= 100){
                while(currentTaskQueue[0] >= 100){
                    currentTaskQueue.shift();
                    currentSpeeds.shift();
                    currnetCompleteTask++;
            }
            answer.push(currnetCompleteTask);   
        }
    }

    return answer;
}
