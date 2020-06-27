const resultSet = new Set();

const findMatchCase = (id_array,target) => {
    const isMatch = (t1,t2) => {
        if (t1.length != t2.length) return false;
        for (let i in t1) {
           if((t1[i] != t2[i]) && (t1[i]!='*' && t2[i] !='*')){
               return false;
           }
        }
        return true;
    }
    
    return id_array.reduce((acc,elem)=>{
        if (isMatch(elem,target)) acc.push(elem)
        return acc
    },[])
}

const dfs= (caseArray,level,caseSet) => {
    if(level === caseArray.length) {
        return (level === caseSet.size) ? resultSet.add([...caseSet].sort().join('')): '';
    }
    
    for(let elem of caseArray[level]) {
        const next = new Set([...caseSet,elem])
        if(next.size !== caseSet.size){
            dfs(caseArray,level+1,next)   
        }
    }  
}

function solution(user_id, banned_id) {    
    const caseArray = banned_id.reduce((acc,e) => {
        acc.push( findMatchCase(user_id,e) )
        return acc;
    },[]);   
    
    dfs(caseArray,0,new Set())    
    return resultSet.size;
}
