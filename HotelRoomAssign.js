const roomMap = new Map()
const answer = [];

const findParent = function(e){
    const parent = roomMap.get(e);
    if(roomMap.get(parent)){
        const p = findParent(parent);
        roomMap.set(parent,p)
        return p
    } 
    return e+1
}

const assignRoom = (answer,roomNo) => {
  roomMap.set(roomNo,roomNo+1);
  answer.push(roomNo);
} 

function solution(k, room_number) {
    room_number.forEach(e => {
        if(!roomMap.get(e)) assignRoom(answer,e)    
        else {
            const emptyRoom = findParent(e);
            assignRoom(answer,emptyRoom)
        }
    });
    return answer;
}
