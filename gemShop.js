function solution(gems) {
    const caseSet = new Set(gems);
    const resultMap = new Map();
    let answer_s = 0;
    let answer_e = gems.length-1;
    let s=0;
    let e=0;
    
    for(let i in gems){
        if(resultMap.size < caseSet.size) {
            const currentGemCount = Number(resultMap.get(gems[i]));
            if ( currentGemCount > 0 ) {
              resultMap.set( gems[i] , 1 + currentGemCount );  
            } else {
                resultMap.set( gems[i] , Number(1))
            }
            e = i;
        }
        while(resultMap.size === caseSet.size) {
            const frontGemCount = Number(resultMap.get(gems[s]))
            if(e - s < answer_e - answer_s) {
            answer_s = s;
            answer_e = e;
            }

            if ( frontGemCount > 1 ) {
                resultMap.set(gems[s],frontGemCount - 1)
            } else {
                resultMap.delete(gems[s])
            }
            s++;
        }
    }    
    return [ Number(answer_s) + 1, Number(answer_e) + 1 ];
}
