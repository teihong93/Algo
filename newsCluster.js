/*
 좀더 간편하게 해결하는 방법이 있을것 같은데, 우아하지 않고
 무식하게 문제를 해결했다. 일단 2문자 단위로 토큰을 쪼개고 모두
 소문자로 변경한 후, 알파벳이 아니면 토큰에 넣지 않았다(정규 표현식으로 했다면
 더 깔끔했을것)
 그 후 모든 토큰 조합에 대한 count 테이블을 만든 후, 테이블의 key에 대한
 교집합과 합집합을 구해 교집합의 경우 테이블에서 작은 값을, 합칩합의
 경우 테이블에서 큰 값을 더하는 방식으로 문제를 해결하였다.
*/


const isAlpha = function(token){
    return (token>='a' && token<='z' || token>='A' && token<='Z' )?true:false;
}

function solution(str1, str2) {
    let answer=0;
    let str1Token=[];
    let table1={};
    let str2Token=[];
    let table2={};
    
    [...str1].forEach((elem,index)=>{
        if(index!==str1.length-1 && isAlpha(elem) && isAlpha(str1[index+1])){
            str1Token.push((elem+str1[index+1]).toLowerCase());
        }
    });
    [...str2].forEach((elem,index)=>{
        if(index!==str2.length-1 && isAlpha(elem) && isAlpha(str2[index+1])){
            str2Token.push((elem+str2[index+1]).toLowerCase());
        }
    });
    
    str1Token.forEach(elem=>{
        if(!table1[elem]) table1[elem]=0;
        table1[elem]=table1[elem]+1;
    });
    str2Token.forEach(elem=>{
        if(!table2[elem]) table2[elem]=0;
        table2[elem]=table2[elem]+1;
    });

    let intersection = Object.keys(table1).filter(x => Object.keys(table2).includes(x));
    let union = [...new Set(Object.keys(table1).concat(Object.keys(table2)))];
    
    const intersecCount = intersection.reduce((acc,elem)=>{
        let t1= table1[elem];
        let t2= table2[elem];
        if(t1 && t2) return acc+(Math.min(t1,t2));
        if(t1) return acc+t1;
        return acc+t2;
    },0);
    
    const unionCount = union.reduce((acc,elem)=>{
        let t1= table1[elem];
        let t2= table2[elem];
        if(t1 && t2) return acc+(Math.max(t1,t2));
        if(t1) return acc+t1;
        return acc+t2;
    },0);
    
    if(intersecCount===0 && unionCount===0) answer =1;
    else answer = (intersecCount/unionCount);
    return Math.floor(answer*65536);
}
