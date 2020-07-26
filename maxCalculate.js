const execOPer = {
    '+': (a,b)=> a+b,
    '-': (a,b)=> a-b,
    '*': (a,b)=> a*b
};

const isNumber = (char) => (char >= '0' && char <='9');
const abs = (i) => (i>0) ? i : -i;
let cMax = 0

const tokenize = (string) => {
    const resultArray = [];
    let chunk = "";
    for(let i=0; i<string.length; i++) {
        if( isNumber(string[i]) ){
            chunk += string[i];
        } else {
          resultArray.push(chunk);
          resultArray.push(string[i])  
          chunk = "";
        }
    }
    return [...resultArray,chunk]
}

const findCase = (tokens,tokenizedExpression,level) => {
    if (level === tokens.length) {
        let res = tokenizedExpression;
        tokens.sort( (a,b) => (a.priority < b.priority ? -1 : a.priority > b.priority ? 1 : 0) )
        for( let i=0; i<tokens.length; i++){
            res = calculate(tokens[i].oper,res)
        }

        res = res[0]
        
        cMax = ( abs(res) > cMax ) ? abs(res) : cMax 
        return cMax;
    }
    
    for( let i=0; i<tokens.length; i++){
        if( !tokens[i].visited ){
            tokens[i].visited = true;
            tokens[i].priority = (Number(level) + 1);
            findCase([...tokens],tokenizedExpression,level+1)
            tokens[i].visited = false;
            tokens[i].priority = (Number(level) - 1);
        }
    }
    
}

const calculate = (oper,expression) => {
    const resultArray = [];
    let exec = false;
    
    for(let i=0 ; i<expression.length ; i++) {
        if(exec){
            const operFunc = execOPer[oper]
            resultArray.push( operFunc(Number(resultArray.pop()),Number(expression[i])) );
            exec = false;
        } else {
            if (expression[i] === oper) {
                exec = true;
            } else {
                resultArray.push(expression[i])
            }   
        }
    }
    return resultArray;
}

const filterOperatpr = (tokenizedExpression) => {
    return new Set(
        tokenizedExpression.filter( e => (e === "+" ||e === "*" ||e === "-" ) )
    )
}

function solution(expression) {
    var answer = 0;
    const tokenizedExpression = tokenize(expression);
    const tokens = [...filterOperatpr(tokenizedExpression)]
    
    answer = findCase(tokens.map( e => ({
       "oper": e,
       "visited": false,
       "priority":0    
    })), tokenizedExpression, 0);
    
    return cMax;
}