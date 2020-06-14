package main

type Node struct {
    Pos int
    Visit int
    Dist int
}

func abs(num int) int {
    if num > 0 {
     return num   
    } else {
     return -num
    }
}

func change(name string, idx int) (int) {
    price1 := int('A') - int(name[idx])
    price2 := int('Z') + 1 - int(name[idx])
    if abs(price1) < abs(price2) {
        return abs(price1)
    } else  {
        return abs(price2)
    }
}

func moveLeft(idx int, size int) int {
    if( idx == 0 ) {
        return size -1
    } else {
        return idx -1
    }
}

func moveRight(idx int, size int) int {
    return (idx+1) % (size)
}

func moveTillNext(name string,currPos int,path []Node ,mf func(int, int) int) (int,int) {
    dist:=0
    pos:= currPos
    for {
        nextPos := mf(pos,len(name))
        target:= name[nextPos]
        dist ++;
        pos = nextPos

        if target!='A' && path[nextPos].Visit ==0 {
            break;
        } 
    }
    return dist,pos
}

func visitAll(path []Node) bool{
    
    for i:=0; i< len(path); i++ {
        if(path[i].Visit == 0) {
            return false
        }
    }
    return true
}

func visitA(path []Node,name string){   
    for i:=0; i< len(path); i++ {
        if(name[i] == 'A') {
            path[i].Visit = 1
            path[i].Dist = -1
            path[i].Pos = -1
        }
    }
}

func findPath(name string, path []Node, currPos int,level int,dist int){

    path[currPos].Visit = 1 // 방문처리 하고
    path[currPos].Dist = dist
    path[currPos].Pos = currPos
    if ( visitAll(path) ) {
        return     //전부 방문했으면 return 
    }
        
    leftDist,lPos := moveTillNext(name,currPos,path,moveLeft)
    rightDist,rPos := moveTillNext(name,currPos,path,moveRight)
        
    if leftDist >= rightDist {
        findPath(name,path,rPos, level+1,rightDist)
    } else {
        findPath(name,path,lPos, level+1,leftDist)
    }    
    
}

func solution(name string) int {
    
    sum := 0
    path := make([]Node,len(name))     // A 에는 미리 방문처리를 해둠
    visitA(path,name)     // 방문 순서를 정해줌 (find path)
    findPath(name,path,0,1,0)     // 순서대로 방문하면서 버튼값 누적함
    
    for i:=0; i< len(path); i++ {
        if(path[i].Pos != -1) {
            sum += path[i].Dist
            sum += change(name, path[i].Pos)
        }
    }
    return sum
}